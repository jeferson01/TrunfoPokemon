#include <iostream>
#include <fstream>
#include <Windows.h>
#include <random>
#include <iomanip> // 'setw()' align columns
#include "../Gerador/gerador_funcoes.h"
#include "../Gerador/gerador_funcoes.cpp" // alternativa seria add gerador_funcoes.cpp ao proj Jogo.

using namespace std;
static int PontosJogador1 = 0, PontosJogador2 = 0;
static int Seed = 21; // seed do gerador
static const char* CorDef = CorDoTipo(-1);

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

	const char* nomeJog1 = "Ash K.";
	const char* nomeJog2 = "Gary";
	unsigned short tamNome; // tamanho do maior nome, usado para colunas setw()
	strlen(nomeJog1) > strlen(nomeJog2) ? tamNome = strlen(nomeJog1) : tamNome = strlen(nomeJog2);
	
	const float VantagemBonus = 0.25;
	const unsigned short comprarCartas = 7; // quantidade de cartas pra cada jogador
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
	ExibirDesenho(40); cout << endl;// printar desenho

	SetConsoleCP(1252); // exibir acentos no console
	SetConsoleOutputCP(1252);


	// -------------- Exibir tipos/cores --------------
	for (int i = 0; i < 9; i++)
	{
		cout << CorDoTipo(i) << " " << TipoString(i) << " " << CorDoTipo(-1) << " ";
		Sleep(150);
	}

	cout << "\nIniciar nova partida ? [S / N] ";
	//char ch;
	//while (cin >> ch && ch != 'S' && ch != 'N') // ***
		//cout << "\nIniciar nova partida ? [S / N] ";
	
	// comprar Cartas p/ cada jogador
	Cartas* cartasJogador1[comprarCartas]; // vetor de ponteiros 'Cartas*'
	Cartas* cartasJogador2[comprarCartas]; 
	for (int cartaRand, i = 0; i < comprarCartas; i++)
	{
		cartaRand = numRd(rd);
		cartasJogador1[i] = &vetBaralho[cartaRand]; // endereço apontando p/ carta no vetor baralho
		
		cartaRand = numRd(rd);
		cartasJogador2[i] = &vetBaralho[cartaRand];
	}

	//Listar(vetBaralho, quantCartas);
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
		
		// *adiciona cor do tipo do pokemon*
		int tipoPok1 = TipoString(cartasJogador1[i]->tipo); // set o numero do tipo
		int tipoPok2 = TipoString(cartasJogador2[i]->tipo);
		
		bool vantagemPok1 = CompararVantagemTipo(VantagemDoTipo(cartasJogador1[i]->tipo), tipoPok2);
		bool vantagemPok2 = CompararVantagemTipo(VantagemDoTipo(cartasJogador2[i]->tipo), tipoPok1);
		
		cout.setf(ios::boolalpha);
		cout << "\n vantagem do pok1: " << vantagemPok1 << " , pok2: " << vantagemPok2 << endl; // debug

		cout << endl << "\t";
		cout << CorDoTipo(tipoPok1) << "  " << CorDef << " " << cartasJogador1[i]->nome << " X "
			 << cartasJogador2[i]->nome << " " << CorDoTipo(tipoPok2) << "  " << CorDef << endl;
		

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

		// ** definir vantagem +xx% bonus no atributo.... **
		atribJogador1 += int(atribJogador1 * VantagemBonus * vantagemPok1);
		atribJogador2 += int(atribJogador2 * VantagemBonus * vantagemPok2);
		
		cout.setf(ios::left);  const int col = 12; // tamanho da coluna, setw() para cada palavra

		cout << "\n[" << setw(tamNome) << nomeJog1 << "] " << setw(col) << cartasJogador1[i]->nome << " -> " << setw(2) << atribJogador1;
		cout <<  " " << CorDoTipo(tipoPok1) << "  " << CorDef;
		if (vantagemPok1) cout << " bônus +" << int(VantagemBonus * 100) << "%";

		cout << "\n[" << setw(tamNome) << nomeJog2 << "] " << setw(col) << cartasJogador2[i]->nome << " -> " << setw(2) << atribJogador2;
		cout << " " << CorDoTipo(tipoPok2) << "  " << CorDef;
		if (vantagemPok2) cout << " bônus +" << int(VantagemBonus * 100) << "%";

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
