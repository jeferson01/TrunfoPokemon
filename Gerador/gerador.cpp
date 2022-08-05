#include <iostream>
#include <fstream>
using namespace std;

struct Cartas
{
	char nome[12];
	enum TiposEnum { Fogo, Agua, Eletrico, Grama, Pedra, Voador, Normal };
	int ataque, defesa, especial, agilidade;
	int tipo; // 

};

int main() {
	Cartas pikachu = {"Pikachu", 10, 15};
	cout << pikachu.nome << " " << pikachu.ataque << " " << pikachu.defesa;


	return 0;
}