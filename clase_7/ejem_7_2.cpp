#include <iostream>

using namespace std;

void hanoi(int n, int from, int to, int aux) {
    if( n == 1 ) {
        cout << "Mover de " << from << " a " << to << endl;
        return;
    }
    hanoi( n-1, from, aux, to);
    hanoi(   1, from, to, aux);
    hanoi( n-1, aux, to, from);
}

int main() {
    hanoi(3, 1, 3, 2);
    return 0;
}
