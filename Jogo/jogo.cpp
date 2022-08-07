#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

void StarsPrint(int time = 100, char ch= '*') {
	cout << endl;
	for (int i = 0; i < 20; i++)
	{
		Sleep(time); cout << ch;
	}
}

int main() {

	StarsPrint(50);
	cout << "\nSuper Trunfo Pokemon";
	StarsPrint();

	cout << "\nIniciar nova partida ? [S / N] ";
	char ch;
	while (cin >> ch && ch != 'S' && ch != 'N')
		cout << "\nIniciar nova partida ? [S / N] ";




	return 0;
}


/*
Jogador 1 : João
Jogador 2 : José
----------
*/