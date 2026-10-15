#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <cmath>
#include <array>
#include <algorithm>
#include <fstream>
#include <cstdlib> 

///////////////////
// EJERICICIO 01 //
///////////////////
/*
Haga un bloque try/catch y en su cuerpo llame a una función funA, a su vez funA llama a
funB. Declare tanto en funA como en funB instancias de un UDT que anuncien su construcción
y destrucción. Haga finalmente que funB haga el throw de una excepción. ¿Qué puede observar
con respecto a las instancias creadas? Coloque múltiples catch para tipos distintos y verifique el
correcto funcionamiento cuando dispara excepciones de distinto tipo desde funA. ¿Qué pasa si
dispara una exception de un tipo no “catcheado”? Verifique el comportamiento del catch(...).
*/

struct T {
	T() {
		std::cout << "FUI CREADO" << std::endl;
	}
	~T() {
		std::cout << "FUI DESTRUIDO" << std::endl;
	}
};

void funB() {
	T t;
	// throweo error tipo entero, va a subir hasta ej_1
	throw 20;
}

void funA() {
	T t;
	// si throweo 'c' tipo char, no se llama a funB
	// throw 'c';
	// si throweo "hola" va a ser tipo desconocido
	// throw "hola";
	funB();
	// nunca se va a throwear "error" porque funB ya throwea
	throw "error";
}

void ej_1() 
{
	try {
		funA();
	}
	catch(int e) {
		std::cout << "Falla tipo entero: " << e << std::endl;
	}
	catch(char e) {
		std::cout << "Falla tipo char: " << e << std::endl;
	}
	catch(...) {
		std::cout << "Falla tipo desconocido" << std::endl;
	}
}

///////////////////
// EJERICICIO 02 //
///////////////////
/*
Dado std::vector<std::string> datos = {"12", "abc", "99999999999", "7"};, recorra el vector
convirtiendo cada elemento con std::stoi. Sume los válidos y, para cada inválido, imprima un
mensaje distinto según sea std::invalid_argument o std::out_of_range. El programa no debe
terminar ante el primer error.
*/

void ej_2() 
{
	std::vector<std::string> datos = {"12", "abc", "99999999999", "7"};
	

	for(int i = 0; i < datos.size(); i++) {
		try {
			stoi(datos[i]);
		}
		catch(std::invalid_argument) {
			std::cout << "invalid_argument en posicion: " << i << std::endl;
			continue;
		}
		catch(std::out_of_range) {
			std::cout << "out_of_range en posicion: " << i << std::endl;
			break;
		}
	}

}

///////////////////
// EJERICICIO 03 //
///////////////////
/*
Indique cuáles de las líneas (a) a (d) no compilan y explique por qué.
*/

class Cuenta {
	// cuando se usa class
	// antes de public:, todo es privado
	double saldo = 0;
	void registrar(double m) {  /*guarda en un historial*/  }
public:
	void depositar(double m) { saldo += m; registrar(m); }
	double getSaldo() const { return saldo; }
};



void ej_3() 
{
	// (a) compila pues depositar es un metodo publico que se puede 
	// acceder desde afuera
	//
	// (b) no compila porque saldo es un atributo privado de la clase
	// no se puede modificar desde afuera
	//
	// (c) tampoco compila pues registrar() es un metodo privado
	//
	// (d) compila pues getSaldo() es publico
	Cuenta c;
	c.depositar(100); // (a)
	// c.saldo = 500; // (b)
	// c.registrar(10); // (c)
	double s = c.getSaldo(); // (d)
}

///////////////////
// EJERICICIO 04 //
///////////////////
/*
Escriba una clase Temperatura que guarde el valor en grados Celsius en un miembro
privado. Debe tener:
	bool setCelsius(double c): rechaza valores menores a -273.15 devolviendo false
	sin modificar el objeto.
	double getCelsius() const y double getFahrenheit() const.
Responda: ¿qué problema aparecería si el atributo fuera público?
*/

class Temperatura {
	double t;
public:
	bool setCelsius(double c) {
		// si t fuera publico, no abria 
		// forma de hacer este if
		// enforando la condicion desada
		// y se podria llegar a un estado
		// donde t es menor a -273.15
		if(c < -273.15) {
			return false;
		}
		t = c;
		return true;
	}
	double getCelsius() const {
		return t;
	}
	double getFahrenheit() const {
		return (t * 1.8) + 32;
	}
};

void ej_4() 
{
	Temperatura amb;
	amb.setCelsius(20.3);
	std::cout << amb.getCelsius() << std::endl;

	amb.setCelsius(-500);
	std::cout << amb.getCelsius() << std::endl;

	std::cout << amb.getFahrenheit() << std::endl;
}

///////////////////
// EJERICICIO 05 //
///////////////////
/*
Compruebe que una clase con constructores privados no puede (por ahora) instanciarse.
*/

class Priv {
	Priv() {
		std::cout << "soy un constructor privado" << std::endl;
	}
};

void ej_5() 
{
	//Priv p; // NO COMPILA! comprobando que clase con constructores privados no se puede instanciar
}



int main() {
	// descomentar el ejercicio que se quiera probar
	// ej_1();
	// ej_2();
	// ej_3();
	// ej_4();
	ej_5();
	return 0;
}
