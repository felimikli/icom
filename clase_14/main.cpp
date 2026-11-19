#include <iostream>
#include <sstream>
#include <ctime>
#include <vector>
#include <string>
#include <cmath>
#include <array>
#include <algorithm>
#include <fstream>
#include <cstdlib> 
#include <cstdint> 
#include <cassert>

///////////////////
// EJERICICIO 01 //
///////////////////
/*
Crear una versión template de la función Fibonacci() para que retorne long, float, etc, en 
lugar de siempre ints. 
*/

template<class T>
T fibonacci(unsigned int n) {
	if(n < 2) return n;
	return fibonacci<T>(n - 1) + fibonacci<T>(n - 2);
}


void ej_1() 
{
	int f_i = fibonacci<int>(12);
	double f_d = fibonacci<double>(12);
	uint8_t f_u = fibonacci<uint8_t>(12);

	std::cout << "12 fibonacci:" << std::endl;
	std::cout << "int: " << f_i << " size: " << sizeof(f_i) << std::endl;
	std::cout << "double: " << f_d << " size: " << sizeof(f_d) << std::endl;
	std::cout << "uint8_t: " << (int) f_u << " size: " << sizeof(f_u) << std::endl;

}

///////////////////
// EJERICICIO 02 //
///////////////////
/*
Defina la clase template CoordenadaCartesiana3D que permita parametrizar el tipo con que se 
almacena cada coordenada. 
*/

template<class T>
class Vec3d {
	public:
		T x, y, z;
};

void ej_2() 
{
	Vec3d<int> punto_discreto = {1, 2, 3};
	Vec3d<float> punto_flotante = {0.3, 0.22, 1};

	std::cout << "coordenadas discretas (x, y, z): " << punto_discreto.x << ", " << punto_discreto.y << ", " << punto_discreto.z << std::endl;
	std::cout << "coordenadas flotantes (x, y, z): " << punto_flotante.x << ", " << punto_flotante.y << ", " << punto_flotante.z << std::endl;
}

///////////////////
// EJERICICIO 03 //
///////////////////
/*
*/

void ej_3() 
{
}

///////////////////
// EJERICICIO 04 //
///////////////////
/*
*/

void ej_4() 
{
}

///////////////////
// EJERICICIO 05 //
///////////////////
/*
*/

void ej_5() 
{
}


int main() {
	// descomentar el ejercicio que se quiera probar
	// ej_1();
	ej_2();
	// ej_3();
	// ej_4();
	// ej_5();
	return 0;
}
