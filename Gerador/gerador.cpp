#include <iostream>
#include <fstream>
#include <Windows.h>
#include "gerador_funcoes.h"
//using namespace std;
using std::cout;
using std::cin;
using std::endl;


int main() {
	SetConsoleCP(1252); // exibir acentos no console
	SetConsoleOutputCP(1252);

	std::ifstream fin;
	std::ofstream fout;
	
	const char cabecalho[] = "BARALHO";
	unsigned short quantCartas = 0; // quantidade de cartas no vetor..
	const unsigned short TAM_BARALHO = 32;
	Cartas vetBaralho[TAM_BARALHO];
	

	fin.open("../baralho.dat", std::ifstream::in | std::ifstream::binary);
	if (!fin.is_open())
		cout << "arquivo nao foi aberto.\n";
	else {
		char chTemp[10];

		// leitura do cabeçalho
		fin.read((char*)&chTemp, sizeof(cabecalho));
		fin.read((char*)&quantCartas, sizeof(short));
		fin.read((char*)vetBaralho, sizeof(Cartas) * quantCartas); // ler vetor
		fin.close();

		cout << chTemp << " " << quantCartas; // debug
	}
	
	ExibirMenu(); // exibir menu e escolher opcao
	char ch;
	while (cin >> ch && ch != 'S' && ch != 's')
	{
		switch (toupper(ch)) // convert maiusculo
		{
		case 'C':
			//cout << "cadastro";
			vetBaralho[quantCartas] = Cadastrar();
			cout << vetBaralho[quantCartas].nome;
			quantCartas++;
			break;

		case 'I':
			Importar(vetBaralho, &quantCartas);
			break;

		case 'L':
			Listar(vetBaralho, quantCartas);
			break;

		case 'A':
			Alterar(vetBaralho, quantCartas);
			break;

		case 'E':
			Excluir(vetBaralho, quantCartas);
			quantCartas--;
			break;

		default: cout << "invalido"; break;
		}
		cout << "\nEscolha uma opcao: [ ]\b\b";; // reset menu
	}
	cout << endl << "Saindo do gerador.." << endl;

	//quantCartas = 0; // quantidade de cartas no vetor, definir depois..
	if (quantCartas > TAM_BARALHO)
		quantCartas = TAM_BARALHO;
	fout.open("../baralho.dat", std::ios::out | std::ios::trunc | std::ios::binary);
	fout.write((char*) &cabecalho, sizeof(cabecalho));
	fout.write((char*)&quantCartas, sizeof(short));
	fout.write((char*)vetBaralho, sizeof(Cartas) * quantCartas); // escrever vetor
	fout.close();

	return 0;
}

/*
//Cartas pikachu = { "Pikachu", 12, 15 };
*/