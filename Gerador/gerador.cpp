#include <iostream>
#include <fstream>
#include "gerador_funcoes.h"
using namespace std;



int main() {
	ifstream fin;
	fin.open("baralho.dat", ifstream::in);
	if (!fin.is_open())
		cout << "arquivo nao foi aberto.\n";


	Cartas pikachu = {"Pikachu", 12, 15};
	Cartas vetBaralho[32];
	ExibirMenu();

	char ch;
	cin >> ch;
	switch (ch)
	{
	case 'C': 
		cout << "cadastro";
		vetBaralho[0] = Cadastrar();
		cout << vetBaralho[0].nome;
		
		break;
	case 'I': cout << "importar"; break;

	default: cout << "invalido"; break;
	}


	return 0;
}