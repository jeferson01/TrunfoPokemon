#pragma once
#define CorVermelho "\033[31m"
#define CorAzul "\033[34m"

struct Cartas
{
	char nome[12];
	int ataque, defesa, especial, agilidade;

	char tipo[12]; // a definir
};


void ExibirMenu();
void ExibirDesenho(int = 50);
Cartas Cadastrar();

void Importar(const char*, Cartas*, unsigned short*);
void Listar(Cartas*, int);
void Alterar(Cartas*, int);
void Excluir(Cartas*, int);

const char* CorDoTipo(int);
const char* TipoString (const int);
int TipoString(const char* );

int* VantagemDoTipo(const char* tipoStr);
bool CompararVantagemTipo(const int*, const int);
