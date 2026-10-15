#include <iostream>
#include <vector>

using namespace std;


void rotaVector(int *V, int N, int dist) {
	int aux[N];
	for(int i = 0; i < N; i++) {
		aux[i] = V[i];
	}
	for(int i = 0; i < N; i++) {
		int index = (i - dist) % N;
		if(index < 0) index += N;
		V[i] = aux[ index ];
	}
}

void cambiaCombinacion(int candado[3][10], int rotaciones[3]) {
	for(int i = 0; i < 3; i++)
		rotaVector(candado[i], 10, rotaciones[i]);
}

int main() {
	int V[5] = {1, 2, 3, 4, 5};
	rotaVector(V, 5, 3);
	for(int i = 0; i < 5; i++) {
		cout << V[i] << " ";
	}
	cout << endl;
	rotaVector(V, 5, 1);
	for(int i = 0; i < 5; i++) {
		cout << V[i] << " ";
	}
	cout << endl;
	rotaVector(V, 5, 1);
	for(int i = 0; i < 5; i++) {
		cout << V[i] << " ";
	}
	cout << endl;
	return 0;
}

