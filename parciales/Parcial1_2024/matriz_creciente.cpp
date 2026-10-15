#include <iostream>
#include <vector>


using namespace std;

// Función para reemplazar los ceros
void reemplazar_ceros(vector<vector<int>>& matriz) {
	for(int i = matriz.size() - 2; i > 0; i--) {
		for(int j = matriz[i].size() - 2; j > 0; j--) {
			if(!matriz[i][j]) {
				matriz[i][j] = min(matriz[i+1][j], matriz[i][j+1]) - 1;
			}
		}
	}

} //TODO

// Funcion que dada una matriz (rellenada) retorna true si es creciente y false si no lo es
bool es_creciente(vector<vector<int>>& matriz) {
	for(int i = 0; i < matriz.size(); i++) {
		for(int j = 1; j < matriz[i].size(); j++) {
			if(matriz[i][j] <= matriz[i][j-1]) return false;
		}
	}
	for(int j = 0; j < matriz[0].size(); j++) {
		for(int i = 1; i < matriz.size(); i++) {
			if(matriz[i][j] <= matriz[i-1][j]) return false;
		}
	}
	return true;

} //TODO

// Ayuda: Funcion que imprime la matriz.
void print_matriz(vector<vector<int>>& matriz){
	for(auto vec: matriz){
		for(auto elem: vec){
			cout << elem << " ";
		}
		cout << endl;
	}
}

// Función que recibe una matriz con ceros, los reemplaza y verifica si la matriz es creciente. Si lo es, devuelve la suma de sus elementos. En caso contrario, devuelve -1
int solucion(vector<vector<int>>& matriz){
	reemplazar_ceros(matriz);
	if(!es_creciente(matriz)) return -1;

	int sum = 0;
	for(int i = 0; i < matriz.size(); i++) {
		for(int j = 0; j < matriz[i].size(); j++) {
			if(matriz[i][j] < 1) return -1;
			sum += matriz[i][j];
		}
	}
	return sum;
} //TODO


int main() {
	// Ejemplo de entrada
	vector<vector<int>> a = {
		{1, 2, 3},
		{3, 0, 4},
		{4, 5, 6},
	};

	vector<vector<int>> b = {
		{1, 3, 5, 6, 7},
		{3, 0, 7, 0, 9},
		{5, 0, 0, 0, 10},
		{8, 9, 10, 11, 12}
	};

	if (solucion(a) == -1 && solucion(b) == 144) {
		cout << "Muy bien!" << endl;
	} else {
		cout << "Muy mal" << endl;
	}

	return 0;
}
