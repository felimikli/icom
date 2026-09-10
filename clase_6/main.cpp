#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <cmath>
#include <array>
#include <algorithm>
#include <fstream>


///////////////////
// EJERICICIO 01 //
///////////////////

#define STACK_MAX 2094730
void ej_1() {
	int arr[STACK_MAX];
	for(int i = 0; i < STACK_MAX; i++) {
		std::cout << arr[i] << std::endl;
	}
	return;
}

///////////////////
// EJERICICIO 02 //
///////////////////



int factorial(int n) {
	int inicial = 1;
	static int num_guardado = 1;
	static int fac_guardado = 1;
	if(n >= num_guardado && num_guardado != 1) {
		inicial = num_guardado;
	} else {
		num_guardado = 1;
		fac_guardado = 1;
	}
	for(int i = inicial; i < n; i++) {
		num_guardado++;
		fac_guardado *= num_guardado;
	}
	return fac_guardado;
}

void ej_2() {

	std::cout << "factorial de 11: " << factorial(11) << std::endl;
	std::cout << "factorial de 1:  " << factorial(1) << std::endl;
	std::cout << "factorial de 2:  " << factorial(2) << std::endl;
	std::cout << "factorial de 4:  " << factorial(4) << std::endl;
	std::cout << "factorial de 10: " << factorial(10) << std::endl;
	std::cout << "factorial de 5:  " << factorial(5) << std::endl;
	return;
}

///////////////////
// EJERICICIO 03 //
///////////////////


struct A {
	int a;
	A() {
		a = 1;
		std::cout << "Soy A y fui instanciado!" << std::endl;
	}
};
struct B {
	A a;
	B() {
		std::cout << "Soy B y fui instanciado!" << std::endl;
	}
};

void ej_3() {
	int n = 5;
	B arr_b[n];
	for(int i = 0; i < n; i++) {
		std::cout << arr_b[i].a.a << std::endl;
	}
	return;
}

///////////////////
// EJERICICIO 04 //
///////////////////


struct A_4 {
	A_4() {
		std::cout << "Soy A_4 y fui instanciado!" << std::endl;
	}
	~A_4() {
		std::cout << "Soy A_4 y fui destruido!" << std::endl;
	}
};
struct B_4 {
	A_4 a;
	B_4() {
		std::cout << "Soy B_4 y fui instanciado!" << std::endl;
	}
	~B_4() {
		std::cout << "Soy B_4 y fui destruido!" << std::endl;
	}
};

void ej_4() {
	B_4 arr_b[5];
	return;
}

///////////////////
// EJERICICIO 05 //
///////////////////


struct Sin_constructor {
	int a;
	Sin_constructor() {
		std::cout << "constructor por defecto" << std::endl;
	}
	Sin_constructor(int a_) {
		a = a_;
		std::cout << "instanciado chat" << std::endl;
	}
};

void ej_5() {
	Sin_constructor s;
	Sin_constructor r(3);
	return;
}

///////////////////
// EJERICICIO 06 //
///////////////////

struct A_6 {
	int a;
	int b;
	A_6() {
		a = 0;
		b = 23;
		std::cout << "Soy A_6 y fui instanciado!" << std::endl;
	}
	~A_6() {
		std::cout << "Soy A_6 y fui destruido!" << std::endl;
	}
};

void ej_6() {
	A_6 a;
	std::cout << "a.a: " << a.a << "a.b: " << a.b << std::endl;
	a.a = 10;
	a.b = 12;
	std::cout << "a.a: " << a.a << "a.b: " << a.b << std::endl;
	A_6 b = a;
	std::cout << "b.a: " << b.a << "b.b: " << b.b << std::endl;
	return;
}

///////////////////
// EJERICICIO 07 //
///////////////////

struct A_7 {
	int a;
	int b;
	A_7() {
		a = 0;
		b = 23;
		std::cout << "Soy A_7 y fui instanciado!" << std::endl;
	}
	A_7(const A_7 &x) {
		a = x.a;
		b = x.b;
		std::cout << "Haciendo una copia..." << std::endl;
	}
	~A_7() {
		std::cout << "Soy A_7 y fui destruido!" << std::endl;
	}
	void print() {
		std::cout << ".a: " << a << "  .b: " << b << std::endl;
	}
};

void b7(A_7 x) {
	std::cout << "x: ";
	x.print();
	return;
}

A_7 c7() {
	A_7 a;
	return a;
}

void ej_7() {
	A_7 a;
	std::cout << "a: ";
	a.print();

	a.a = 1;
	a.b = 1;
	std::cout << "a: ";
	a.print();

	A_7 b = a;
	std::cout << "b: ";
	b.print();

	b7(b);

	A_7 c = c7();
	std::cout << "c: ";
	c.print();

	return;
}

///////////////////
// EJERICICIO 08 //
///////////////////

struct A_8 {
	int a;
	int b;
	A_8() {
		a = 0;
		b = 23;
		std::cout << "Soy A_8 y fui instanciado!" << std::endl;
	}
	A_8(const A_8 &x) {
		a = x.a;
		b = x.b;
		std::cout << "Haciendo una copia..." << std::endl;
	}
	~A_8() {
		std::cout << "Soy A_8 y fui destruido!" << std::endl;
	}
	void print() {
		std::cout << ".a: " << a << "  .b: " << b << std::endl;
	}
};

void a8(A_8 &a) {
	std::cout << "estoy en la funcion" << std::endl;
	a.print();
}

void ej_8() {
	A_8 a;
	a.print();
	a8(a);
}

///////////////////
// EJERICICIO 09 //
///////////////////

struct T {
	int n;
	T() {
		n = 0;
		std::cout << "Soy t" << n << " y fui instanciado por defecto!" << std::endl;
	}
	T(int n_) {
		n = n_;
		std::cout << "Soy t" << n << " y fui instanciado!" << std::endl;
	}
	~T() {
		std::cout << "Soy t" << n << " y fui destruido!" << std::endl;
	}
	void print() {
		std::cout << "Soy t" << n << "!!!" << std::endl;
	}
};

void ej_9() {
	T t0(0), t1(1), t2(2), t3(3), t4(4), t5(5), t6(6), t7(7), t8(8), t9(9);
	std::vector<T> v {t0, t1, t2, t3, t4, t5, t6, t7, t8, t9};
	for(std::size_t i = 0; i < v.size(); i++) {
		v[i].print();
	}
	v.resize(3);
	for(std::size_t i = 0; i < v.size(); i++) {
		v[i].print();
	}
	v.resize(10);
	for(std::size_t i = 0; i < v.size(); i++) {
		v[i].print();
	}
}

///////////////////
// EJERICICIO 10 //
///////////////////
struct A_10 {
	A_10() {
		std::cout << "Soy A_10 y fui instanciado!" << std::endl;
	}
	A_10(const A_10 &x) {
		std::cout << "Haciendo una copia en A_10..." << std::endl;
	}
	~A_10() {
		std::cout << "Soy A_10 y fui destruido!" << std::endl;
	}
};
struct B_10 {
	A_10 a;
	B_10() {
		std::cout << "Soy B_10 y fui instanciado!" << std::endl;
	}
	~B_10() {
		std::cout << "Soy B_10 y fui destruido!" << std::endl;
	}
};

void ej_10() {
	B_10 b;
	B_10 b2 = b;
}

///////////////////
// EJERICICIO 11 //
///////////////////

class Contenedor11 {
	public:
		Contenedor11(char c1, char c2) {
			caracteres.push_back(c1);
			caracteres.push_back(c2);
		} //TODO

		bool esIgual()
		{
			return (caracteres.at(0)==caracteres.at(1));
		} 

		void fijarse()
		{
			std::cout << "Los caracteres son: " << (esIgual() ? "IGUALES" : "DISTINTOS") << std::endl;
		}	

	private:
		std::vector<char> caracteres; 

};

void ej_11(){
	char c1, c2;
	std::cout << "ingresar dos chars: "  << std::endl;
	std::cin >> c1 >> c2;
	Contenedor11 c(c1, c2);

	c.fijarse();
	return;
}

///////////////////
// EJERICICIO 12 //
///////////////////


class Contenedor {
	public:
		Contenedor() 

		{
			std::string c_aux;

			while (true)
			{
				std::cout << "Ingrese un string de 8 caracteres: ";
				std::cin >> c_aux;
				if (c_aux.length()==8)
				{
					cartas.push_back(c_aux);
					break;
				}
				else
					std::cout << "Dije 8 caracteres!" << std::endl;
			}		

			while (true)
			{
				std::cout << "Ingrese otro string de 8 caracteres: ";
				std::cin >> c_aux;
				if (c_aux.length()==8)
				{
					cartas.push_back(c_aux);
					break;
				}
				else
					std::cout << "Dije 8 caracteres!" << std::endl;
			}
		}

		//funcion que se fija si al menos un caracter de cada una de las 2 cartas coincide con al menos un caracter de la otra. Si existe una coincidencia, evuelve true, sino false.
		bool coincidencia(){
			for(char c : cartas.at(0)) {
				if(cartas.at(1).find(c) != std::string::npos) {
					return true;
				}
			}
			return false;
		} //TODO

		void fijarse()
		{
			std::cout << "Las cartas coinciden en algun caracter? " << (coincidencia() ? "SI" : "NO") << std::endl;
		}	

	private:
		std::vector<std::string> cartas; 

};

void ej_12(){
	Contenedor c;
	c.fijarse();

	return;
}

///////////////////
// EJERICICIO 13 //
///////////////////

class Mazo
{
	public:
		// Construye una instancia de Mazo leyendo las 'cartas' a partir la
		// informacion leida en el archivo 'mazo.txt'.
		// El archivo cuenta con un string por renglon, con los simbolos de la
		// carta
		Mazo(const std::string &fname) {
			std::ifstream mazo(fname);
			std::string carta;
			cartas.push_back("");
			while(std::getline(mazo, carta)) {
				cartas.push_back(carta);
			}
		}// TODO

		//Funcion que imprime el mazo
		void print() {
			for(std::string carta : cartas) {
				for (char ch : carta) {
					std::cout << ch;
				}
				std::cout << std::endl;
			}
		}//TODO

	private:
		// representacion de todas las cartas
		std::vector<std::string> cartas;

};

void ej_13(){
	Mazo m("mazo.txt");
	m.print();

	return;
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
	// ej_12();
	ej_13();
	return 0;
}
