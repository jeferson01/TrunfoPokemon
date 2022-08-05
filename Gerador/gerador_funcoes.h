#pragma once
struct Cartas
{
	char nome[12];
	int ataque, defesa, especial, agilidade;

	enum TiposEnum { Fogo, Agua, Eletrico, Grama, Pedra, Voador, Normal };
	char tipo[12]; // a definir
};

void ExibirMenu();
Cartas Cadastrar();