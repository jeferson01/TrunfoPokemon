#include <iostream>
#include <fstream>
#include <Windows.h>
#include <random>
#include "../Gerador/gerador_funcoes.h"
#include "../Gerador/gerador_funcoes.cpp" // alternativa seria add gerador_funcoes.cpp ao proj Jogo.
using namespace std;

void ExibirCartasNaMao(Cartas* vetJog[], int tam);

void StarsPrint(int time = 100, char ch= '*') {
	cout << endl;
	for (int i = 0; i < 20; i++) {
		Sleep(time); 
		cout << ch;
	}
}


int main() {
	const char* nomeJog1 = "Ash Ketchup";
	const char* nomeJog2 = "Garybaldo";

	const unsigned short comprarCartas = 4; // quantidade de cartas pra cada jogador
	unsigned short quantCartas;
	const char cabecalho[] = "BARALHO";
	char chTemp[10];


	ifstream fin;
	fin.open("../baralho.dat", ifstream::in | ifstream::binary);
	if (!fin.is_open())
		cout << "arquivo nao foi aberto.\n";

	// leitura do cabe�alho
	fin.read((char*)&chTemp, sizeof(cabecalho));
	fin.read((char*)&quantCartas, sizeof(short));

	Cartas* vetBaralho = new Cartas[quantCartas]; // Vetor dinamico de cartas
	fin.read((char*)vetBaralho, sizeof(Cartas) * quantCartas); // ler vetor
	fin.close();

	//random_device seed; // gerador baseado em hardware
	default_random_engine rd(16); // const 10 � a seed do gerador
	uniform_int_distribution<int>numRd(0, quantCartas - 1); // range do numero d carta sorteada
	uniform_int_distribution<int>atributoRd(1, 4); // range do atributo select

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
		cartasJogador1[i] = &vetBaralho[cartaRand]; // endere�o apontando p/ carta no vetor baralho
		cout << endl << cartaRand;
		cout << " " << cartasJogador1[i]->nome;
		
		cartaRand = numRd(rd);
		cartasJogador2[i] = &vetBaralho[cartaRand];
		cout << endl << cartaRand;
		cout << " " << cartasJogador2[i]->nome;
	}

	Listar(vetBaralho, quantCartas);
	//ExibirCartasNaMao(cartasJogador1, comprarCartas);

	// rounds, uma vez cada jog., exibe atributos da carta e escolhe atrib
	bool turnoJogador1 = true;
	for (int i = 0; i < comprarCartas; i++)
	{
		cout << "\n*** Round " << i + 1 << " ***\n";
		cout << "Turno do jogador [";
		turnoJogador1 ? (cout << nomeJog1 << "]\n") : (cout << nomeJog2 << "]\n"); // print nome do jog
		cout << cartasJogador1[i]->nome << " X " << cartasJogador2[i]->nome << endl;


		cout << "\n[1] Ataque\n[2] Defesa\n[3] Especial\n[4] Agilidade" << endl;
		cout << "Escolha um atributo: [_]\b\b";
		int num;
		
		if (turnoJogador1) {
			// s� entra no loop se o numero for invalido ou fora do range.
			while (!(cin >> num) || !(num >= 1 && num <= 4))
			{
				cin.clear(); // clear buffer
				cin.ignore();
				cout << "numero invalido, digite novamente: [_]\b\b";
			}
		}
		else {
			num = atributoRd(rd);
			Sleep(1500);
			cout << num << endl;
			system("pause");
			cout << ">>Jogador 2 escolheu o atributo: [" << num << "] \n";
			
		}

		turnoJogador1 = !turnoJogador1;
	}
	return 0;
}

// esta recebendo um vetor de ponteiros, "Cartas** vetJog" ou chamar usando "*cartasJogador1"
void ExibirCartasNaMao(Cartas* vetJog[], int tam) {
	cout << endl << "Exibindo cartas na mao: \n";
	for (int i = 0; i < tam; i++)
	{
		cout << vetJog[i]->nome << " || ";
	}
}

/*
Jogador 1 : Jo�o
Jogador 2 : Jos�
----------
*/