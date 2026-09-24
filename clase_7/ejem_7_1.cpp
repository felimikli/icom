#include <iostream>

using namespace std;

int factorial(int n) {
    if( n == 0 )
        return 1;
    return n * factorial(n - 1);
}
int fb(int n) {
    if( n == 0 || n == 1)
        return n;
    return fb(n - 1) + fb(n - 2);
}
int main() 
{
    cout << "7! = " << factorial(7) << endl;
    cout << "fb(7) = " <<  fb(7) << endl;
    return 0;
}
