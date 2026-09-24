#include "icom_helpers.h"
// manipulacion
int main(void)
{
    string s("Sean laureles los laureles");    // con inicialización
    string s2("laureles");

    size_t pos = s.find(s2);
    if(pos != string::npos)
        cout << s2 << " esta en " << pos << '\n';

    pos = s.find(s2, pos+1);
    if(pos != string::npos)
        cout << s2 << " esta nuevamente en " << pos << '\n';

    s.replace(s.find(s2), s2.length(), "eternos");
    cout << s << '\n';

    return 0;
}