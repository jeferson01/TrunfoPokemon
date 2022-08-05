#include <iostream>
#include "gerador_funcoes.h"
using namespace std;

void ExibirMenu() {
	cout << "Gerador de Cartas\n"
		<< "------------------\n"
		<< "(C)adastrar\n"
		<< "(I)mportar\n"
		<< "(A)lterar\n"
		<< "(E)xcluir\n"
		<< "(L)istar\n"
		<< "(S)air\n";
	cout << "Escolha uma opcao [ ]\b\b";
}

Cartas Cadastrar() {
	Cartas cadastro;
	cout << "Cadastrar Carta\n"
		<< "---------------\n";
	//alinhamento colunas;
	const int ali = 12;

	cout.width(ali); cout << left << "Nome : ";
	cin >> cadastro.nome;
	cout.width(ali); cout << left << "Ataque : ";
	cin >> cadastro.ataque;
	cout.width(ali); cout << left << "Defesa : ";
	cin >> cadastro.defesa;
	cout.width(ali); cout << left << "Especial : ";
	cin >> cadastro.especial;
	cout.width(ali); cout << left << "Agilidade : ";
	cin >> cadastro.agilidade;
	return cadastro;
}

