#include <iostream>
#include <vector>

// tamano fijo, matriz nativa
const int N = 4;

struct casilla {
	int i, j;
};

// IMPLEMENTACIÓN
void caminos_pascal(int m[N][N], casilla c) {
	// siempre sumo uno cada vez que paso por una casilla
	m[c.i][c.j]++;
	if(c.i < N - 1) {
		// si no estoy en el borde derecho, me muevo a la derecha
		caminos_pascal(m, {c.i + 1, c.j});
	}
	if(c.j < N - 1) {
		// si no estoy en el borde de abajo, me muevo hacia abajo
		caminos_pascal(m, {c.i, c.j + 1});
	}
}


void print_matrix(int m[N][N]){
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main() {

	// inicializo matriz en 0;
	int m[N][N];
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			m[i][j] = 0;
		}
	}

	caminos_pascal(m, {0, 0});
	print_matrix(m);
	return 0;
}
