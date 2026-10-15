#include "icom_helpers.h"

const int N = 5;
const int M = 5;

struct celda
{
    int i, j;
};

int camino_optimo(int maz[N][M], celda c, int energia)
{
    // el camino no puede salirse de la mazmorra
    if (c.i < 0 || c.i >= N || c.j < 0 || c.j >= M)
        return -1;

    // actualizo la energia
    energia += maz[c.i][c.j];
    // la princesa no se puede morir
    if (energia  <= 0)
        return -1;

    // llegue hasta el caballero termina la recursion
    if (c.i == N - 1 && c.j == M - 1)
        return energia;

    // caso general
    // pruebo llegar por abajo
    celda c_abajo = {c.i + 1, c.j};
    int energia_abajo = camino_optimo(maz, c_abajo, energia);

    // pruebo llegar por la derecha
    celda c_derecha = {c.i, c.j + 1};
    int energia_derecha = camino_optimo(maz, c_derecha, energia);

    // si ninguno de los dos caminos es viable...
    if(energia_derecha <0 && energia_abajo<0)
        return -1;

    // hay al menos un camino posta me quedo con el de mayor energia restante
    if (energia_abajo > energia_derecha)
        return energia_abajo;
    else
        return energia_derecha;

}

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
        cout << "El resultado es INCORRECTO" <<endl;

    return 0;
}

