#include "icom_helpers.h"

const int N = 5;
const int M = 5;

struct celda
{
    int i, j;
};

int camino_optimo(int maz[N][M], celda c, int energia) {
	int e = energia + maz[c.i][c.j];
	// caso base
	if((c.i == N-1 && c.j == M-1) || e <= 0) {
		return e;
	}

	if(c.i == N-1) {
		return camino_optimo(maz, {c.i, c.j + 1}, e);
	}
	if(c.j == M-1) {
		return camino_optimo(maz, {c.i + 1, c.j}, e);
	}

	int derecha = camino_optimo(maz, {c.i + 1, c.j}, e);
	int abajo = camino_optimo(maz, {c.i, c.j + 1}, e);
	if(derecha > abajo) {
		return derecha;
	}
	return abajo;

} // ToDo

int main()
{
	int mazmorra[N][M]={ {-7, 4, 4,-1,-4},
		{-5, 1,-7, 2,-7},
		{-2,-9, 2,-6, 6},
		{ 7,-4,-2, 7, 2},
		{-9, 3,-3,-2,-8} };
	int energia = 10;
	int resultado_esperado = 7;

	cout << "La princesa comienza con energia = " << energia << endl;
	int energia_final = camino_optimo(mazmorra, {0, 0}, energia);

	if ((energia_final)<0)
		cout << "No se pudo encontrar un camino optimo" << endl;
	else
		cout << "camino optimo encontrado. Energia restante: " << energia_final << endl;

	if (energia_final==resultado_esperado)
		cout << "El resultado es CORRECTO" << endl;
	else
		cout << "El resultado es INCORRECTO"<< endl;

	return 0;
}


