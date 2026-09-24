#include "icom_helpers.h"
// Lee datos desde "datos.dat", los ordena y los escribe en "datos_ord.dat"
int main(void)
{
    ifstream iFile("datos.dat"); 
    if(iFile.is_open()) {
        vector<int> datos;
        int d;
        while(iFile >> d)
            datos.push_back(d);
        iFile.close();

        sort(datos.begin(), datos.end());

        ofstream oFile("datos_ord.dat");
        for(int d: datos)
            oFile << d << '\n';
    }
    return 0;
}
