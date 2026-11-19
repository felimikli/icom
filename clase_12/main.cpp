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
#include <cassert>

///////////////////
// EJERICICIO 01 //
///////////////////
/*
Se desea representar un polígono con una interfaz simple para poder conocer algunas propiedades del 
mismo. La representación e interfaz deseada es la siguiente. Se solicita completar la implementación del 
UDT. 
 
struct Punto2D { 
    double X; 
    double Y; 
}; 
 
class Poligono { 
    public: 
        // construye un poligono cerrado con los vertices dados 
        Poligono(const vector<Punto2D> &vertices); 
 
        // retorna el perimetro del poligono 
        double perimetro() const; 
 
        // retorna el area del poligono 
        double area() const; 
 
    private: 
        vector<Punto2D> vertices; 
}; 
 
Evalúe la necesidad de implementar un constructor de copia, uno de asignación y un destructor. En el caso 
de llegar a la conclusión de que hacen falta, impleméntelos. 
*/


struct Punto2D { 
	double x; 
	double y; 
}; 

double dist(Punto2D p1, Punto2D p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

class Poligono { 
	public: 
		// construye un poligono cerrado con los vertices dados 
		Poligono(const std::vector<Punto2D> &vertices_) {
			vertices = vertices_;
		}

		// retorna el perimetro del poligono 
		double perimetro() const {
			size_t n = vertices.size();
			double per = 0;
			for(size_t i = 0; i < n; i++) {
				per += dist(vertices[i], vertices[(i + 1) % n]);
			}
			return per;
		}

		// retorna el area del poligono 
		// https://en.wikipedia.org/wiki/Shoelace_formula
		// formula de area teniendo vertices
		double area() const {
			double area = 0;
			size_t n = vertices.size();
			for(size_t i = 0; i < n; i++) {
				Punto2D p1 = vertices[i];
				Punto2D p2 = vertices[(i + 1) % n];

				area += (p1.y + p2.y)*(p1.x - p2.x);
			}
			return area / 2;
		}

		void print() { 
			int i = 0;
			for(auto p : vertices) { 
				std::cout << "p" << i << ": (" << p.x << ", " << p.y << ")" << std::endl;
				i++;
			}
		}

	private: 
		std::vector<Punto2D> vertices; 
}; 

void ej_1() 
{
	const std::vector<Punto2D> ver1 = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};	
	Poligono cuadrado(ver1);
	cuadrado.print();
	std::cout << "Perimetro: " << cuadrado.perimetro() << std::endl;
	std::cout << "Area: " << cuadrado.area() << std::endl;

	const std::vector<Punto2D> ver2 = {{0, 0}, {1, 0}, {0.5, 1}};	
	Poligono triangulo(ver2);
	triangulo.print();
	std::cout << "Perimetro: " << triangulo.perimetro() << std::endl;
	std::cout << "Area: " << triangulo.area() << std::endl;
}

///////////////////
// EJERICICIO 02 //
///////////////////
/*
Sistema de Simulación (problema de diseño): Un diagrama de simulación como el que se muestra en 
la siguiente figura se compone de bloques (todos con distinto nombre) que están conectados entre sí a 
través de señales. 
 
A su vez, algunos bloques (subsystem o subsistema) pueden contener un diagrama, como es el caso del 
bloque Pendulum del diagrama anterior cuyo contenido se muestra en la figura siguiente. En estos casos, 
los nombres de los bloques internos llevan como prefijo el nombre del bloque que los contiene (por 
ejemplo, Pendulum/Mux). 

El sistema de simulación determina el orden en que se ejecutarán todos los bloques, y en un 
esquema de tiempo discretizado, para cada paso de tiempo los ejecuta en ese orden. Para cada 
bloque se calculan las salidas (si las hubiera), se ingresan las entradas (si las hubiera) y se actualiza 
el estado (si lo hubiera). Se solicita diseñar (sin implementar) las clases necesarias para representar 
todos los componentes de un sistema de simulación. 
*/


class Block {
	public:
		Block(Block** in_, size_t in_num) {
			in = new Block*[in_num];
			size_in = in_num;
			for(int i = 0; i < in_num; i++) {
				in[i] = in_[i];
			}

		}
		~Block() {
			delete [] in;
		}

		virtual double out() = 0;
		

	protected:
		Block** in;
		size_t size_in;
};

class Sum : public Block {
	public:
		double out() override {
			double sum = 0;
			for(int i = 0; i < size_in; i++) {
				sum += in[i].out();
			}
			return sum;
		}
	private:
		
}

void ej_2() 
{
}

///////////////////
// EJERICICIO 03 //
///////////////////
/*
*/

void ej_3() 
{
}


int main() {
	// descomentar el ejercicio que se quiera probar
	// ej_1();
	ej_2();
	// ej_3();
	return 0;
}
