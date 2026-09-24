#include "icom_helpers.h"
int main(void)
{
    string s1;
    string s2("AAA");    // con inicialización
    string s3 = "BBB";   // ídem anterior
    string s4{"CCC"};    // ídem anterior
    string s5{s2};       // ídem anterior

    s1 = s2 + s3 + s4;   // concatenación

    if(s2 > s3)          // comparación
        cout << "estamos en problemas\n";
    if(s2 == s5)
        cout << "Menos mal!\n";
    
    cout << "s1: " << s1 << " largo: " << s1.length() << '\n';
    return 0;
}
