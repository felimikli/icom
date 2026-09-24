#include "icom_helpers.h"
// acceso a caracteres individuales
int main(void)
{
    string s("Hola Pirulo");

    for(size_t i = 0; i < s.length(); ++i) // recorrido indexado
        cout << s[i];
    cout << '\n';

    for(auto c : s) // recorrido con range-based for
        cout << c;
    cout << '\n';

    for(auto it = s.begin(); it != s.end(); ++it) // idem a través de un iterador
        cout << *it;
    cout << '\n';

    return 0;
}
