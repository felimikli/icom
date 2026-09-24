#include <stdio.h>
#include <memory.h>
#include <assert.h>

// Lista de casillas a las que el caballo puede moverse desde una posición.
// Un caballo puede tener como máximo 8 movimientos posibles.
struct Candidatos
{
    Candidatos()
    {
        // El constructor deja la lista inicialmente vacía.
        clear();
    }

    // Elimina todos los candidatos almacenados.
    void clear()
    {
        numCand = 0;
    }

    // Agrega una casilla a la lista de candidatos.
    void Agrega(int posX, int posY)
    {
        // Si esta condición falla, se intentaron agregar más de 8 movimientos.
        assert(numCand < MAX_CAND);
        values[numCand].x = posX;
        values[numCand].y = posY;
        numCand++;
    }

    static const int MAX_CAND = 8;
    int numCand;
    struct
    {
        int x;
        int y;
    } values[MAX_CAND];
};

class Tablero
{
public:
    // Inicializa todas las casillas como desocupadas.
    Tablero()
    {
        memset(cells, 0, sizeof(cells));
    }

    // Imprime el tablero mostrando el número de ficha de cada casilla.
    void ImprimeTablero()
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            for (int x = 0; x < BOARD_SIZE; x++)
                printf(" %02d", cells[y][x]);
            puts("");
        }
        puts("================================================================");
    }

    // Intenta completar un recorrido comenzando desde posX, posY.
    // 'ficha' representa el número que se colocará en la casilla actual.
    // La función utiliza backtracking: coloca una ficha, explora cada
    // alternativa posible y luego deshace el movimiento para probar otra.
    void IntentaLlenado(int posX, int posY, int ficha)
    {
        Candidatos cands;

        // Marca la casilla actual como visitada.
        PoneFicha(ficha, posX, posY);

        // Si se colocó la ficha 64, se completó un recorrido válido.
        if (ficha == BOARD_SIZE * BOARD_SIZE)
        {
            ImprimeTablero();

            // Deshace la última colocación antes de regresar al nivel anterior.
            SacaFicha(posX, posY);
            return;
        }

        // Obtiene todas las casillas libres alcanzables desde la posición actual.
        int n = CompletaCandidatos(posX, posY, &cands);

        // Explora recursivamente cada movimiento posible.
        for (int i = 0; i < n; i++)
            IntentaLlenado(cands.values[i].x, cands.values[i].y, ficha + 1);

        // Libera la casilla para que pueda usarse en otra rama de búsqueda.
        SacaFicha(posX, posY);
    }

    static const int BOARD_SIZE = 8;


private:
    // Coloca la ficha n en la posición posX, posY.
    void PoneFicha(int n, int posX, int posY)
    {
        // La posición debe estar dentro del tablero y desocupada.
        assert(posX >= 0 && posX < BOARD_SIZE && posY >= 0 && posY < BOARD_SIZE && cells[posY][posX] == 0);
        cells[posY][posX] = n;
    }

    // Retira la ficha que está en la posición posX, posY.
    void SacaFicha(int posX, int posY)
    {
        // La posición debe estar dentro del tablero y ocupada.
        assert(posX >= 0 && posX < BOARD_SIZE && posY >= 0 && posY < BOARD_SIZE && cells[posY][posX] != 0);
        cells[posY][posX] = 0;
    }

    // Indica si una posición está dentro del tablero y no fue visitada.
    bool EstaLibre(int posX, int posY)
    {
        return posX >= 0 && posX < BOARD_SIZE && posY >= 0 && posY < BOARD_SIZE && cells[posY][posX] == 0;
    }
    // Completa la lista de movimientos legales desde una posición y devuelve
    // la cantidad de candidatos encontrados.
    int CompletaCandidatos(int posX, int posY, Candidatos *pCand)
    {
        // Las ocho combinaciones posibles de movimiento de un caballo.
        static const int deltas[Candidatos::MAX_CAND][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};
        pCand->clear();

        // Conserva únicamente los movimientos que permanecen dentro del
        // tablero y llegan a una casilla todavía libre.
        for (int i = 0; i < Candidatos::MAX_CAND; i++)
        {
            if (EstaLibre(posX + deltas[i][0], posY + deltas[i][1]))
                pCand->Agrega(posX + deltas[i][0], posY + deltas[i][1]);
        }
        return pCand->numCand;
    }

    // cells[y][x] contiene 0 si la casilla está libre o el número de ficha
    // que indica en qué paso del recorrido fue visitada.
    int cells[BOARD_SIZE][BOARD_SIZE];
};

int main()
{
    Tablero tab;

    int primerFicha = 1;
    // Prueba todos los posibles puntos de partida.
    // La búsqueda es exhaustiva; se podrían aprovechar simetrías o inversiones para reducir
    // el trabajo, aunque eso requeriría tenerlas en cuenta al contar soluciones.
    for (int y = 0; y < Tablero::BOARD_SIZE; y++)
    {
        for (int x = 0; x < Tablero::BOARD_SIZE; x++)
        {
            printf("Intentando desde %d, %d\n", x, y);
            tab.IntentaLlenado(x, y, primerFicha);
        }
    }
}
