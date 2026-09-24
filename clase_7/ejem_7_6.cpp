#include "icom_helpers.h"
int main(void)
{
    ofstream oFile;         // crea la instancia de ofstream
    oFile.open("kk.dat");   // abre un archivo y lo asocia a oFile
                            // podria haber declarado ofstream oFile("kk.dat")     
    if(oFile.is_open()) {   // equivalente a if(oFile) { ...
        oFile << "Esto va a parar al file\n";
        oFile << "y esto\n" << "y esto tambien...\n";
        oFile.close();
    }
    ifstream iFile("kk.dat");
    if(iFile) {
        string line;
        
        while ( getline (iFile, line) )
            cout << line << '\n';
    }
    return 0;
}