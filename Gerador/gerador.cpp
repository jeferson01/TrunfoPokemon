#include <iostream>
#include <fstream>
using namespace std;

struct Cartas
{
	char nome[12];
	char tipo[12]; // a definir
	enum TiposEnum { Fogo, Agua, Eletrico, Grama, Pedra, Voador, Normal };
	int ataque, defesa, especial, agilidade;
};

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

int main() {

	Cartas pikachu = {"Pikachu", "eletrico", 15};
	//cout << pikachu.nome << " " << pikachu.ataque << " " << pikachu.tipo;
	ExibirMenu();

	char ch;
	cin >> ch;
	switch (ch)
	{
	case 'C': cout << "cadastro"; break;
	case 'I': cout << "importar"; break;

	default: cout << "invalido"; break;
	}


	return 0;
}