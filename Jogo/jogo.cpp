#include <iostream>
#include <fstream>
#include <Windows.h>
#include <random>
#include <iomanip> // 'setw()' align columns
#include "../Gerador/gerador_funcoes.h"
#include "../Gerador/gerador_funcoes.cpp" // alternativa seria add gerador_funcoes.cpp ao proj Jogo.
using namespace std;
static int PontosJogador1 = 0, PontosJogador2 = 0;
static int Seed = 17; // seed do gerador

void ExibirCartasNaMao(Cartas* vetJog[], int tam);

void StarsPrint(int time = 100, char ch= '*') {
	cout << endl;
	for (int i = 0; i < 20; i++) {
		Sleep(time); 
		cout << ch;
	}
}


int main() {
	//SetConsoleCP(437); // default console for debug
	//SetConsoleOutputCP(437);

	const char* nomeJog1 = "Ash Kétchup";
	const char* nomeJog2 = "Garybaldo";

	const unsigned short comprarCartas = 5; // quantidade de cartas pra cada jogador
	unsigned short quantCartas;
	const char cabecalho[] = "BARALHO";
	char chTemp[10];

	ifstream fin;
	fin.open("../baralho.dat", ifstream::in | ifstream::binary);
	if (!fin.is_open()) {
		cout << "arquivo nao foi aberto.\n";
		std::exit(EXIT_FAILURE);
	}
		

	// leitura do cabeçalho
	fin.read((char*)&chTemp, sizeof(cabecalho));
	fin.read((char*)&quantCartas, sizeof(short));

	Cartas* vetBaralho = new Cartas[quantCartas]; // Vetor dinamico de cartas
	fin.read((char*)vetBaralho, sizeof(Cartas) * quantCartas); // ler vetor
	fin.close();

	//random_device seed; // gerador baseado em hardware
	default_random_engine rd(Seed); // const 10 é a seed do gerador
	uniform_int_distribution<int>numRd(0, quantCartas - 1); // range do numero d carta sorteada
	uniform_int_distribution<int>atributoRd(1, 4); // range do atributo select


	// -------------------------------------------------------------------------
	// ----------------------- Printar Desenho ---------------------------------
	//StarsPrint(50);
	//ExibirDesenho(100); // printar desenho

	SetConsoleCP(1252); // exibir acentos no console
	SetConsoleOutputCP(1252);
	
	for (int i = 0; i < 10; i++)
	{
		const char* tipo = TipoString(i);
		cout << endl << i << ": ";
		cout << VantagemDoTipo(tipo)[0] << " ";
		cout << VantagemDoTipo(tipo)[1] << " ";
		cout << "vantagem: " << CompararVantagemTipo(VantagemDoTipo(tipo), 2);
	}


	for (size_t i = 0; i < 12; i++)
	{
		cout << TipoString(i) << " -> " << TipoString(TipoString(i)) << endl;
	}
	for (size_t i = 0; i < 9; i++)
	{
		cout << CorDoTipo(i) << " " << TipoString(i) << " " << CorDoTipo(-1) << " ";
		Sleep(150);
	}

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
	ExibirCartasNaMao(cartasJogador1, comprarCartas);
	cout << endl << endl;
	system("pause"); system("cls");

	// rounds, uma vez cada jog., exibe atributos da carta e escolhe atrib
	bool turnoJogador1 = true;
	for (int i = 0; i < comprarCartas; i++)
	{
		cout << "\n*** Round " << i + 1 << " ***\n";
		cout << "Turno do jogador [";
		turnoJogador1 ? (cout << nomeJog1 << "]\n") : (cout << nomeJog2 << "]\n"); // print nome do jog
		
		// *adicionar cor do tipo*
		cout << "normal " << TipoString("Normal") << "eletrico " << TipoString("Elétrico") << endl;

		cout << endl << cartasJogador1[i]->nome << " X " << cartasJogador2[i]->nome << endl;
		

		cout << "\n[1] Ataque\n[2] Defesa\n[3] Especial\n[4] Agilidade" << endl;
		cout << "Escolha um atributo: [_]\b\b";
		int num;
		
		if (turnoJogador1) {
			// só entra no loop se o numero for invalido ou fora do range.
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
			cout << ">>Jogador " << nomeJog2 << " escolheu o atributo : [" << num << "] \n";
		}

		int atribJogador1, atribJogador2; // var do atributo escolhido
		switch (num)
		{
		case 1: atribJogador1 = cartasJogador1[i]->ataque; 
				atribJogador2 = cartasJogador2[i]->ataque; break;

		case 2: atribJogador1 = cartasJogador1[i]->defesa;
				atribJogador2 = cartasJogador2[i]->defesa; break;

		case 3: atribJogador1 = cartasJogador1[i]->especial;
				atribJogador2 = cartasJogador2[i]->especial; break;

		case 4: atribJogador1 = cartasJogador1[i]->agilidade;
				atribJogador2 = cartasJogador2[i]->agilidade; break;

		default: cout << "*ERRO ATRIBUTO SELECIONADO*\a"; break;
		}

		cout.setf(ios::left);  const int col = 12; // tamanho da coluna, setw() para cada palavra

		cout << "\n[" << setw(col) << nomeJog1 << "] " << setw(col) << cartasJogador1[i]->nome << " -> " << atribJogador1;
		cout << "\n[" << setw(col) << nomeJog2 << "] " << setw(col) << cartasJogador2[i]->nome << " -> " << atribJogador2;
		cout << endl << endl;
		cout.unsetf(ios::left);

		if (atribJogador1 != atribJogador2)
			atribJogador1 > atribJogador2 ? PontosJogador1++ : PontosJogador2++; // setar pontos
		else PontosJogador1++, PontosJogador2++; // empate

		cout << "Placar: " << nomeJog1 << " " << PontosJogador1 << " x " << PontosJogador2 << " " << nomeJog2;
		StarsPrint(50, '--'); cout << endl;
		system("pause");
		system("cls");
		turnoJogador1 = !turnoJogador1; // inverter turno de escolha
	}

	if (PontosJogador1 > PontosJogador2)
		cout << CorAzul << "\n*** VOCE VENCEU!! ***\n\a" << "\033[m";
	else if (PontosJogador1 == PontosJogador2)
		cout << "\n*** EMPATE ***\n\a";
	else cout << CorVermelho << "\n*** VOCE PERDEU!! HAHA ***\n\a" << "\033[m";
	
	return 0;
}

// esta recebendo um vetor de ponteiros, "Cartas** vetJog" ou chamar usando "*cartasJogador1"
void ExibirCartasNaMao(Cartas* vetJog[], int tam) {
	cout << endl << "Exibindo cartas na mao: \n";
	for (int i = 0; i < tam; i++)
	{
		cout << vetJog[i]->nome << " || ";
	}
	cout << endl;
}

/*
Jogador 1 : João
Jogador 2 : José
----------
*/