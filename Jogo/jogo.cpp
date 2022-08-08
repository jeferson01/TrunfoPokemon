#include <iostream>
#include <fstream>
#include <Windows.h>
#include <random>
#include "../Gerador/gerador_funcoes.h"
#include "../Gerador/gerador_funcoes.cpp" // alternativa seria add gerador_funcoes.cpp ao proj Jogo.
using namespace std;

void ExibirCartasNaMao(Cartas* vetJog, int tam);

void StarsPrint(int time = 100, char ch= '*') {
	cout << endl;
	for (int i = 0; i < 20; i++)
	{
		Sleep(time); cout << ch;
	}
}



int main() {
	const unsigned short comprarCartas = 4; // quantidade de cartas pra cada jogador
	unsigned short quantCartas;
	const char cabecalho[] = "BARALHO";
	char chTemp[10];

	ifstream fin;
	fin.open("../baralho.dat", ifstream::in | ifstream::binary);
	if (!fin.is_open())
		cout << "arquivo nao foi aberto.\n";

	// leitura do cabeçalho
	fin.read((char*)&chTemp, sizeof(cabecalho));
	fin.read((char*)&quantCartas, sizeof(short));

	Cartas* vetBaralho = new Cartas[quantCartas]; // Vetor dinamico de cartas
	fin.read((char*)vetBaralho, sizeof(Cartas) * quantCartas); // ler vetor
	fin.close();

	//random_device seed; // gerador baseado em hardware
	default_random_engine rd(12); // const 10 é a seed do gerador
	uniform_int_distribution<int>numRd(0, quantCartas - 1); // range do numero

	for (int i = 0; i < 100; i++)
		cout << numRd(rd) << " ";

	StarsPrint(30);
	cout << "\nSuper Trunfo Pokemon";
	StarsPrint(60);

	cout << "\nIniciar nova partida ? [S / N] ";
	char ch;
	//while (cin >> ch && ch != 'S' && ch != 'N') // ***
		//cout << "\nIniciar nova partida ? [S / N] ";
	
	// comprar Cartas p/ cada jogador
	Cartas* cartasJogador1[comprarCartas]; // vetor de ponteiros 'Cartas*'
	Cartas* cartasJogador2[comprarCartas]; 
	for (int cartaRand, i = 0; i < comprarCartas; i++)
	{
		cartaRand = numRd(rd);
		cartasJogador1[i] = &vetBaralho[cartaRand]; // endereço apontando p/ carta no vetor baralho
		cout << endl << cartaRand;
		cout << " " << cartasJogador1[i]->nome;
		
		cartaRand = numRd(rd);
		cartasJogador2[i] = &vetBaralho[cartaRand];
		cout << endl << cartaRand;
		cout << " " << cartasJogador2[i]->nome;
	}


	Listar(vetBaralho, quantCartas);
	return 0;
}

void ExibirCartasNaMao(Cartas* vetJog, int tam) {


}

/*
Jogador 1 : João
Jogador 2 : José
----------
*/