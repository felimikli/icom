// Problema X: Números Malvados
// Se denomina número malvado a aquellos números enteros no negativos que tienen una cantidad par de bits
//  en 1 en su representación binaria.  Se solicita:
//     a)	implementar una función que retorne los primeros n números malvados (ordenados de menor a mayor).
//         La función deberá respetar el siguiente prototipo:
//         vector<unsigned int> generarMalvados(unsigned int n);
//     b)	implementar un main() que lea del archivo mavados.txt los primeros 100 números malvados y 
//         los compare con los que genera su función.


// #include "icom_helpers.h"

// Implemente cualquier otra funcion que considere necesaria/util
#include <vector>
#include <fstream>
#include <iostream>

// funcion para generar los primeros n numeros malvados
std::vector<unsigned int> generarMalvados(unsigned int n) {
	// ToDo
	// m es cantidad de malvados
	unsigned int i = 0, m = 0;
	std::vector<unsigned int> v;
	while(m < n) {
		// b es cantidad de 1s binarios
		int b = 0;
		for(int s = 0; s < int(sizeof(unsigned int) * 8); s++) {
			// voy shifteando el numero i, y extrayendo el bit menos significativo.
			// le sumo a b el bit menos significativo
			b += (i >> s) & (unsigned int) 1;
		}
		if(b % 2 == 0) {
			// si b es par, es malvado
			m++;
			v.push_back(i);
		}
		i++;
	}
	return v;
}   

int main() {
	//ToDo
	// f es la variable del archivo
	std::ifstream f("malvados.txt");
	// v es el vector donde voy a generar los malvados con mi funcion
	// m es el vector donde voy a cargar los malvados del archivo
	std::vector<unsigned int> v, m;
	// x es variable auxiliar para extraer del archivo
	unsigned int x;

	v = generarMalvados(100);

	for(int i = 0; i < 100; i++) {
		f >> x;
		m.push_back(x);
	}

	if(v == m) {
		std::cout << "Son iguales!!" << std::endl;
		return 0;
	}
	std::cout << "Son distintos ):" << std::endl;
	return -1;
}
