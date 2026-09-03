#include <iostream>
#include <cmath>

///////////////////
// EJERICICIO 01 //
///////////////////
void ej_1() {
	int n, m;
	std::cout << "Ingresar M y N\n";
	std::cin >> m >> n;
	for(int i = 0; i <= m; i++) {
		for(int j = 0; j <= n; j++) {
			std::cout << i << j << ' ';
		}
		std::cout << '\n';
	}
}


///////////////////
// EJERICICIO 02 //
///////////////////
int acumular_multiplo(int i, int n) {
	if(i % n == 0) return i;
	return 0;
}

void ej_2() {
	int n = 1000;
	int acum2 = 0, acum3 = 0, acum4 = 0, acum5 = 0;
	for(int i = 1; i <= n; i++) {
		acum2 += acumular_multiplo(i, 2);
		acum3 += acumular_multiplo(i, 3);
		acum4 += acumular_multiplo(i, 4);
		acum5 += acumular_multiplo(i, 5);
	}
	std::cout << "acumulacion de multiplos hasta 1000\n";
	std::cout << "multiplos de 2: " << acum2 << '\n';
	std::cout << "multiplos de 3: " << acum3 << '\n';
	std::cout << "multiplos de 4: " << acum4 << '\n';
	std::cout << "multiplos de 5: " << acum5 << '\n';
}

///////////////////
// EJERICICIO 03 //
///////////////////
void ej_3() {
	int n = 999999;
	double aprox = 0;
	for(int i = 1; i <= n; i++) {
		if(i % 2) {
			aprox += 1/(2*double(i) - 1);
			continue;
		} 
		aprox -= 1/(2*double(i) - 1);
	}
	std::cout << "aprox de pi: " << (aprox * 4) << '\n';
}

///////////////////
// EJERICICIO 04 //
///////////////////

int suma(int N) {
	int s = 0;
	for(int i = 1; i <= N; i++) {
		s += i;
	}
	return s;
}
void ej_4() {
	int n;
	std::cout << "Ingresar N\n";
	std::cin >> n;
	std::cout << "Suma de N primeros naturales: " << suma(n) << '\n';
}

///////////////////
// EJERICICIO 05 //
///////////////////
double miSqrt(double a) {
	int n = 1000;
	double x_n = 1;
	for(int i = 1; i <= n; i++) {
		x_n = (x_n + a/x_n)/2;
	}
	return x_n;
}
void ej_5() {
	double a;
	std::cout << "Ingresar a\n";
	std::cin >> a;
	std::cout << "miSqrt(a): " << miSqrt(a) << '\n';
	std::cout << "sqrt(a): " << std::sqrt(a) << '\n';
}

///////////////////
// EJERICICIO 06 //
///////////////////
double calculaE() {
	int n = 1000; 
	double f = 1;
	double e = 1;
	for(int i = 1; i <= n; i++) {
		f *= double(i);
		e += 1/(f);
	}
	return e;
}
void ej_6() {
	std::cout << "Aprox e: " << calculaE() << '\n';
}

///////////////////
// EJERICICIO 07 //
///////////////////
void ej_7() {
	int n, x, b, r;
	char c;
	std::string s;
	char form[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	std::cout << "Ingresar numero n y base b \n";
	std::cin >> n >> b;
	if(b < 2 || b > 16) {
		std::cout << "Base debe estar entre 2 y 16" << '\n';
		return;
	}
	if(n == 0) {
		std::cout << n << " en base " << b << ": 0" << '\n';
		return;
	}
	x = n;
	while(x >= b) {
		r = x % b;
		x = x / b;
		c = form[r];
		s = c + s;
	}
	if(n) {
		c = form[x];
		s = c + s;
	}
	std::cout << n << " en base " << b << ": " << s << '\n';
}

///////////////////
// EJERICICIO 08 //
///////////////////
void ej_8() {
	float f1 = 1.126, f2 = -1.125, f3 = -0.001, fs = 0;
	double d1 = 1.126, d2 = -1.125, d3 = -0.001, ds = 0;

	for(int i = 1; i <= 0xFFFFFF; i++) {
		fs += f1 + f2 + f3;
		ds += d1 + d2 + d3;
	}

	std::cout << "con float Suma: " << fs << '\n';
	std::cout << "con double Suma: " << ds << '\n';
}

///////////////////
// EJERICICIO 09 //
///////////////////
struct RGB {
	unsigned char r;
	unsigned char g;
	unsigned char b;

	int composite_color() {
		int res = (r) | (g << 8) | (b << 16);
		return res;
	}
	bool set_from_composite(int color) {
		if((color >> 24) & 0xFF) { return false; }
		r = (color >> 0)  & 0xFF;
		g = (color >> 8)  & 0xFF;
		b = (color >> 16) & 0xFF;
		return true;
	}
	bool set_from_components(int R, int G, int B) {
		if(
			(R > 255 || R < 0) ||
			(G > 255 || G < 0) ||
			(B > 255 || B < 0) 
		) return false;
		r = R & 0xFF;
		g = G & 0xFF;
		b = B & 0xFF;
		return true;
	}
	void print() {
		std::cout << "R: " << int(r) << '\n';
		std::cout << "G: " << int(g) << '\n';
		std::cout << "B: " << int(b) << '\n';
	}
};
void ej_9() {
	int color, r, g, b;
	
	RGB rgb = {
		.r = 45,
		.g = 200,
		.b = 128,
	};
	rgb.print();
	std::cout << "composite: " << rgb.composite_color() << '\n';

	std::cout << "Ingresar r g b\n";
	std::cin >> r >> g >> b;

	rgb.set_from_components(r, g, b);
	rgb.print();
	std::cout << "composite: " << rgb.composite_color() << '\n';

	std::cout << "Ingresar color int\n";
	std::cin >> color;
	rgb.set_from_composite(color);

	rgb.print();
	std::cout << "composite: " << rgb.composite_color() << '\n';
}

///////////////////
// EJERICICIO 10 //
///////////////////
void ej_10() {
	int pos = 1, mult, num = 0;
	std::string s, vocals = "aeiou";
	std::cout << "Ingresar string\n";
	std::cin >> s;
	for(char c : s) {
		mult = 2;
		if(vocals.find(c) < vocals.length()) mult = 4;
		num += int(c) * mult * pos;
		pos++;
	}
	std::cout << "Numero verificador: " << num << '\n';
}

///////////////////
// EJERICICIO 11 //
///////////////////
void ej_11() {
	double pi = 3.0, pir = 3.14159265358979323846;

	double tolerancia;
	std::cout << "Ingrese la tolerancia: ";
	std::cin >> tolerancia;

	double termino, i = 1, n;
	do {
		n = 2 * i; 
		termino = 4 / (n * (n + 1) * (n + 2));

		if (int(i) % 2 == 0) {
			pi -= termino;  
		} else {
			pi += termino;  
		}
		i++;

	} while(termino > tolerancia);


	std::cout << "Pi: " << pi << '\n';
}

int main() {
	// ej_1();
	// ej_2();
	// ej_3();
	// ej_4();
	// ej_5();
	// ej_6();
	// ej_7();
	// ej_8();
	// ej_9();
	// ej_10();
	// ej_11();
	return 0;
}
