#include <iostream>
#include <algorithm>

using namespace std;
bool isAnagram(const std::string &s1, const std::string &s2)
{
    // eliminamos todo lo que no sea un caracter y pasamos a mayusculas
    std::string ss1, ss2;
    for (auto c : s1)
    {
        if (c >= 'a' && c <= 'z')
            c = c - 'a' + 'A';
        if (c >= 'A' && c <= 'Z')
            ss1.push_back(c);
    }

    for (auto c : s2)
    {
        if (c >= 'a' && c <= 'z')
            c = c - 'a' + 'A';
        if (c >= 'A' && c <= 'Z')
            ss2.push_back(c);
    }

    std::sort(ss1.begin(), ss1.end());
    std::sort(ss2.begin(), ss2.end());
    return ss1 == ss2;
}

int main()
{
    std::string s1 = "I am Lord Voldemort";
    std::string s2 = "Tom Marvolo Riddle";
    cout << isAnagram(s1, s2) << endl;
    return 0;
}
