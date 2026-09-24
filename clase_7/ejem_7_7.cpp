#include "icom_helpers.h"
// genera un archivo con NUM_DATOS números aleatorios entre 0 y 999

const int NUM_DATOS = 500;

int main(void)
{
    ofstream oFile("datos.dat"); 
    if(oFile.is_open()) {

        srand(time(0));

        for(int i = 0; i < NUM_DATOS; ++i)
            oFile << (rand()%1000) << '\n';

        oFile.close();
    }
    return 0;
}
