#include <iostream>
#include <cmath>


struct Complejo {
	double re, im;
	void print() {
		std::cout << "(" << re << " + i " << im << ")" << '\n';
	}
	double modulo() {
		return std::sqrt(re*re + im*im);
	}
	Complejo operator+(Complejo a) {
		Complejo result = { re + a.re, im + a.im };
		return result;
	}
	Complejo operator-(Complejo a) {
		Complejo result = { re - a.re, im - a.im };
		return result;
	}
	Complejo operator*(Complejo a) {
		Complejo result = { (re * a.re) - (im * a.im), (im * a.re) + (re * a.im) };
		return result;
	}
	Complejo operator/(Complejo a) {
		Complejo result = { ((re * a.re) + (im * a.im))/(a.re*a.re + a.im*a.im), ((im * a.re) - (re * a.im))/(a.re*a.re + a.im*a.im) };
		return result;
	}
};

struct Punto3D_t {
	double x, y, z;
	void print()  {
		std::cout << "(" << x << ", " << y << ", " << z << ")" << '\n';
	}
	double dist(Punto3D_t p) {
		return std::sqrt((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y) + (z - p.z)*(z - p.z));
	}
};

unsigned int rgb_int(unsigned int r, unsigned int g, unsigned int b) {
	unsigned int res = (r) | (g << 8) | (b << 16);
	return res;
}

void rgb_comp(unsigned int e, unsigned int arr[]) {
	arr[0] = (e >> 0)  & 255;
	arr[1] = (e >> 8)  & 255;
	arr[2] = (e >> 16) & 255;
}

float evaluar_poli(int n, float coef[], float x) {
	float res = 0;
	for(int i = 0; i <= n; i++) {
		res += coef[i] * std::pow(x, i);
	}
	return res;
}

int main() {

	int w = 24; // 11000
	int z = 33;
	int n = 4;
	int mask = (1 << n) - 1; // 01111
	int mask_parity = 1; // x & mask_parity = 0 cuando es par, 1 cuando es impar


	std::cout << (w & mask) << '\n';  // 01000 = 8
	std::cout << (w & ~mask) << '\n'; // 10000 = 16
	std::cout << (w | mask) << '\n';  // 11111 = 31
	std::cout << (w & mask_parity) << '\n';
	std::cout << (z & mask_parity) << '\n';

	// leer valor entero
	int x;
	std::cout << "Ingresar un numero entero: " << '\n';
	std::cin >> x;
	std::cout << x << '\n';

	// es par?
	if(x & mask_parity) {
		std::cout << "El numero ingresado es Impar" << '\n';
	} else {
		std::cout << "El numero ingresado es Par" << '\n';
	}

	int x1, x2;
	std::cout << "Ingresar dos numeros enteros: " << '\n';
	std::cin >> x1 >> x2;
	std::cout << x1 << ' ' << x2 << '\n';

	// son multiplos?
	if(!(x1 % x2) | !(x2 % x1)) {
		std::cout << "Los numeros son multiplos" << '\n';
	} else {
		std::cout << "Los numeros NO son multiplos" << '\n';
	}

	//
	std::cout << "H\nol\ta M\bund\ro" << '\n';
	//
	std::cout << "Testing...";
	std::cout << "....1";
	std::cout << "...2";
	std::cout << "..3";
	std::cout << '\n';

	//
	char c, d;
	c = 'd';
	d = c;
	std::cout << "d = " << d << '\n';

	// 8
	int grad = 3;
	float coef[grad + 1] = {6, 0, -5, 3};
	float xp;
	std::cout << "ingresar valor a evaluar" << '\n';
	std::cin >> xp;
	std::cout << evaluar_poli(grad, coef, xp) << '\n';

	// 9
	double var;

	std::cout << &var << '\n';

	// 10
	double x_10 = 1.9;
	int y_10;
	y_10 = x_10;
	x_10 = y_10;
	std::cout << "x_10: " << x_10 << '\n';
	std::cout << "y_10: " << y_10 << '\n';

	// 11
	unsigned int r, g, b, e;
	std::cout << "ingresar r, g, b" << '\n';
	std::cin >> r >> g >> b;

	std::cout << "entero empaquetado: " << rgb_int(r, g, b) << '\n';

	std::cout << "r: " << r << '\n';
	std::cout << "g: " << g << '\n';
	std::cout << "b: " << b << '\n';
	
	
	std::cout << "ingresar entero empaquetado" << '\n';
	std::cin >> e;

	unsigned int comp[3];
	rgb_comp(e, comp);
	std::cout << "r: " << comp[0] << '\n';
	std::cout << "g: " << comp[1] << '\n';
	std::cout << "b: " << comp[2] << '\n';

	// 12
	
	Complejo z1, z2;
	
	std::cout << "ingresar dos numeros complejos (parte real espacio parte imaginaria dos veces)" << '\n';
	std::cin >> z1.re >> z1.im >> z2.re >> z2.im;

	Complejo suma = z1 + z2;
	Complejo resta = z1 - z2;
	Complejo mult = z1 * z2;
	Complejo div = z1 / z2;

	std::cout << "Suma: " << '\n';
	suma.print();
	std::cout << "Resta: " << '\n';
	resta.print();
	std::cout << "Multiplicacion: " << '\n';
	mult.print();
	std::cout << "Division: " << '\n';
	div.print();

	// 13
	Punto3D_t p1, p2;
	std::cout << "ingresar dos puntos 3D (x1 y1 z1 y x2 y2 z2)" << '\n';
	std::cin >> p1.x >> p1.y >> p1.z >> p2.x >> p2.y >> p2.z;
	
	double dist = p1.dist(p2);
	std::cout << "Distancia entre los puntos: " << dist << '\n';
	return 0;
}
