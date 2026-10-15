#include <iostream>

using namespace std;


void print_binary_rec(int n)
{
    if(n == 0 || n == 1)
    {
        cout << n;
        return;
    }
    print_binary_rec(n>>1);
    cout << (n & 1);
}

void print_binary(int n)
{
    int bits = sizeof(n) << 3;
    for(int i = bits - 1; i >= 0; i--)
    {
        if((n & (1 << i)) != 0)
            cout << '1';
        else
            cout << '0';
    }
}

int main()
{
    print_binary(513);
    cout << endl;
    print_binary_rec(65535);

    return 0;
}
