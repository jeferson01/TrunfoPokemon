#include <iostream>
#include <fstream>
#include "gerador_funcoes.h"
#include "gerador.h"
using namespace std;


int main() {
	ifstream fin;
	ofstream fout;
	
	Cartas vetBaralho[32];
	unsigned short quantCartas; // quantidade de cartas no vetor..

	fin.open("../baralho.dat", ifstream::in | ifstream::binary);
	if (!fin.is_open())
		cout << "arquivo nao foi aberto.\n";

	const char cabecalho[] = "BARALHO";
	char chTemp[10];

	// leitura do cabeçalho
	fin.read((char*) &chTemp, sizeof(cabecalho));
	fin.read((char*) &quantCartas, sizeof(short));
	fin.read((char*) vetBaralho, sizeof(Cartas)* quantCartas); // ler vetor
	cout << chTemp << " " << quantCartas;
	fin.close();

	ExibirMenu();

	char ch;
	cin >> ch;
	switch (toupper(ch)) // convert maiusculo
	{
	case 'C': 
		//cout << "cadastro";
		vetBaralho[quantCartas] = Cadastrar();
		cout << vetBaralho[quantCartas].nome;
		quantCartas++;
	
		
		break;
	case 'I': Importar("maiscartas.txt", vetBaralho, &quantCartas); break;

	case 'L':
		Listar(vetBaralho, quantCartas); break;

	default: cout << "invalido"; break;
	}

	fout.open("../baralho.dat", ios::out | ios::trunc | ios::binary);
	//quantCartas = 0; // quantidade de cartas no vetor, definir depois..
	fout.write((char*) &cabecalho, sizeof(cabecalho));
	fout.write((char*)&quantCartas, sizeof(short));
	fout.write((char*)vetBaralho, sizeof(Cartas) * quantCartas); // escrever vetor
	fout.close();


	return 0;
}

/*
//Cartas pikachu = { "Pikachu", 12, 15 };
*/