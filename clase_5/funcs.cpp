#include "funcs.h"


void ImprimeVector(int Vector[], int NumElementos) {
	for(int i = 0; i < NumElementos; i++) {
		std::cout << Vector[i] << ' ';
	}
	std::cout << std::endl;
}

void IngresarVector(int Vector[], int NumElementos) {
	for(int i = 0; i < NumElementos; i++) {
		std::cin >> Vector[i];
	}
}
void OrdenaArrayNativo(int v[], int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n-i-1; j++) {
			if(v[j] > v[j+1]) {
				v[j]     = v[j] ^ v[j + 1];
				v[j + 1] = v[j] ^ v[j + 1];
				v[j]     = v[j] ^ v[j + 1];
				// int t;
				// t = v[j];
				// v[j] = v[j + 1];
				// v[j + 1] = t;
			}
		}
	}
}

