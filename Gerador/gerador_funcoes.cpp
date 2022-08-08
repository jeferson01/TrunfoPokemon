#include <iostream>
#include <fstream>
#include "gerador_funcoes.h"
using namespace std;

void ExibirMenu() {
	cout << endl;
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

void Importar(const char* nomeArq, Cartas* vet, unsigned short* tam) {
	cout << "\nImportar Cartas"
		 << "\n---------------"; 
	cout << "\nArquivo: " << nomeArq << endl;

	ifstream fin;
	fin.open(nomeArq, ios::in);
	if (!fin.is_open())
		cout << nomeArq << " nao foi aberto!";

	Cartas novaCarta;
	char nome[12];
	int tempInt;

	cout << "\nImportando:" << endl;
	while (fin >> nome)
	{
		strcpy_s(novaCarta.nome, sizeof(nome), nome);
		fin >> tempInt;
		novaCarta.ataque = tempInt;
		fin >> tempInt;
		novaCarta.defesa = tempInt;
		fin >> tempInt;
		novaCarta.especial = tempInt;
		fin >> tempInt;
		novaCarta.agilidade = tempInt;
		
		vet[*tam] = novaCarta;
		(*tam)++; // tamanho do vetor +1
		cout << novaCarta.nome << " " << novaCarta.ataque << " " << novaCarta.defesa << " "
			 << novaCarta.especial << " " << novaCarta.agilidade << endl;
	} 
	fin.close();
}

void Listar(Cartas* vet, int tam) {
	cout << "\nCartas no Baralho\n"
		<< "-----------------\n";
	for (int i = 0; i < tam; i++)
	{
		cout << "#" << i + 1 << " ";
		cout << vet[i].nome << " "
			<< vet[i].ataque << " "
			<< vet[i].defesa << " "
			<< vet[i].especial << " "
			<< vet[i].agilidade << " " << endl;
		//cout << vet[i].tipo << " "; // adicionar tipo depois
	}
}

void Alterar(Cartas* vet, int tam) {
	cout << "\nAtualizar Cartas"
		 << "\n----------------\n";
	for (int i = 0; i < tam; i++)
		cout << i + 1 << ") " << vet[i].nome << endl; // listar vetor

	int escolha;
	cout << "Digite o numero da carta: [ ]\b\b";
	cin >> escolha;
	escolha--; // posicao no vetor -> -1
	cout << "Alterando Carta " << vet[escolha].nome << ":" << endl;
	
	const int ali = 12;
	cout.width(ali); cout << left << "Nome : " << vet[escolha].nome << " -> ";
	cin >> vet[escolha].nome;
	cout.width(ali); cout << left << "Ataque : " << vet[escolha].ataque << " -> ";
	cin >> vet[escolha].ataque;
	cout.width(ali); cout << left << "Defesa : " << vet[escolha].defesa << " -> ";
	cin >> vet[escolha].defesa;
	cout.width(ali); cout << left << "Especial : " << vet[escolha].especial << " -> ";
	cin >> vet[escolha].especial;
	cout.width(ali); cout << left << "Agilidade : " << vet[escolha].agilidade << " -> ";
	cin >> vet[escolha].agilidade;
	cout << "\nCarta numero (" << escolha + 1 << ") foi alterada." << endl;
}

void Excluir(Cartas* vet, int tam) {
	cout << "\nExcluir Carta"
		 << "\n-------------\n";
	for (int i = 0; i < tam; i++)
		cout << i + 1 << ") " << vet[i].nome << endl;

	int escolha;
	cout << "Digite o numero da carta: [ ]\b\b";
	cin >> escolha;

	// jogar o vetor pra tras, na posicao excluida
	for (int i = escolha - 1; i < tam - 1; i++) // tamanho menos ultimo elem.
	{
		vet[i] = vet[i + 1]; // copia o prox. elemento
	}
	cout << "\nCarta numero (" << escolha << ") foi excluida." << endl;
}

/*
Atualizar Cartas
----------------
1) Messi
2) Ronaldo
3) Kak�
4) Neymar
Digite o n�mero da carta: [2] 
Alterando Carta Ronaldo: 
Nome : Ronaldo*/

