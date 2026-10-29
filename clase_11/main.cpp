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
Cree una jerarquía de “figuras”: una clase base llamada Figura y clases derivadas, Cuadrado, 
Circulo y Triangulo. En la clase base haga una función virtual dibujar() puro,  y 
sobrescríbala en las clases derivadas. Haga un arreglo nativo de punteros a Figura e inicialícelo con 
objetos creados dinámicamente en el heap (llamando al operador new), llame a dibujar() a 
través de punteros a la clase base para verificar el comportamiento de las funciones virtuales. Utilizar 
el keyword override en las funciones virtuales heredadas en Cuadrado, Circulo y 
Triangulo. 
*/


class Figura {
	public:
		// funcion virtual igualada a 0, 
		// Esto hace que no se pueda instanciar un
		// objeto tipo Figura, pues dibujar() 
		// no esta definida,
		// necesito una subclase que defina dibujar()
		virtual void dibujar() const = 0;
		virtual ~Figura() {};
};

class Cuadrado : public Figura {
	public:
		// defino dibujar() para el cuadrado
		void dibujar() const override {
			std::cout << "Dibujo de cuadrado" << std::endl;
		}
};

class Circulo : public Figura {
	public:
		// defino dibujar() para el circulo
		void dibujar() const override {
			std::cout << "Dibujo de circulo" << std::endl;
		}
};

class Triangulo : public Figura {
	public:
		// defino dibujar() para el triangulo
		void dibujar() const override {
			std::cout << "Dibujo de triangulo" << std::endl;
		}
};


void ej_1() 
{
	const int n = 3;
	// arreglo nativo de punteros a figura
	Figura* arr[n];

	// le asigno un puntero a cuadrado, uno a circulo y uno a triangulo
	arr[0] = new Cuadrado;
	arr[1] = new Circulo;
	arr[2] = new Triangulo;


	// llamo a dibujar() en cada elemento de mi array
	for(int i = 0; i < n; i++) {
		arr[i]->dibujar();
	}

	// Liberar memoria!!!
	for(int i = 0; i < n; i++) {
		delete arr[i];
	}
}

///////////////////
// EJERICICIO 02 //
///////////////////
/*
Modifique el ejercicio anterior para utilizar un vector<Figura *> en lugar de un arreglo nativo. 
Asegúrese que la memoria es liberada correctamente. 
*/

void ej_2() 
{
	const int n = 3;
	// vector de punteros a figura
	std::vector<Figura *> v(n);

	// le asigno un puntero a cuadrado, uno a circulo y uno a triangulo
	v[0] = new Cuadrado;
	v[1] = new Circulo;
	v[2] = new Triangulo;


	// llamo a dibujar() en cada elemento de mi vector
	for(int i = 0; i < n; i++) {
		v[i]->dibujar();
	}

	// Liberar memoria!!!
	for(auto f : v) {
		delete f;
	}
}

///////////////////
// EJERICICIO 03 //
///////////////////
/*
Modifique el ejercicio anterior definiendo el destructor como virtual y verifique que ocurre. 
*/

void ej_3() 
{
	/*
	comentar o descomentar la linea
		virtual ~Figura() {};
	
	y observar que pasa cuando se compila
	*/
}

///////////////////
// EJERICICIO 04 //
///////////////////
/*
Cree una clase Base que tenga un dato miembro, y una clase derivada Deriv de ésta que agrega 
otro dato miembro. Hacer que la clase Base tenga un destructor virtual, en el destructor de ambas 
clases anunciar un mensaje en pantalla (cout). Escriba una función no miembro, void f(Base 
b), que tome un objeto de la clase base por valor e imprima el tamaño del objeto utilizando 
sizeof(). En main() cree un objeto de la clase derivada, imprima su tamaño y llame a  función 
f. Explique qué ocurre. 
*/

class Base {
	int x;
	public:
	virtual ~Base() {
		std::cout << "Destruyendo Base" << std::endl;
	}
};

class Deriv : public Base {
	int y;
	public:
	~Deriv() {
		std::cout << "Destruyendo Deriv" << std::endl;
	}
};

void f(Base b) {
	std::cout << "Tamaño de b en función f: " << sizeof(b) << std::endl;
}

void ej_4() 
{
	Deriv d;
	std::cout << "Tamaño de Deriv d: " << sizeof(d) << std::endl;
	f(d);
}

///////////////////
// EJERICICIO 05 //
///////////////////
/*
En el esqueleto de código presente en expression.cpp se implementa una jerarquía como la 
que se muestra en el diagrama siguiente para representar expresiones algebraicas en forma analítica: 
 

Implemente los métodos faltantes y todo otro método que crea necesario. Pruebe el código con el 
main dado. En ese main, se está creando la expresión: 
sin(3𝑥+4)
2+3 cos( 𝑥
2+𝑥)  que puede verse gráficamente 
como: 
*/


// representa la base de una jerarquía de expresiones
class Exp {
	public:
		virtual ~Exp() {}

		// imprime la expresión en formato algebraico
		// virtual void print() = 0;
		void print() {
			std::cout << this->exp_str() << std::endl;
		};

		virtual std::string exp_str() = 0;

		// evalua la expresion especializada con var = X
		virtual double evaluate(double X) = 0;

		// calcula y retorna la expresión derivada
		virtual Exp *derivate() = 0;

		// clona la expresion
		virtual Exp *clone() = 0;

};

// representa expresiones constantes
class ConstExp : public Exp {    // constant
	public:
		ConstExp(double value_)
			: value(value_) { }

		std::string exp_str() {
			std::ostringstream ss;
			ss << value;
			return ss.str();
		};
		/*
		void print() {
			std::cout << this->exp_str() << std::endl;
		};
		*/

		double evaluate(double X) { 
			return value;
		}
		Exp *derivate() { 
			return (new ConstExp(0));
		}
		Exp *clone() {
			return (new ConstExp(value));
		}

	private:
		double value;
};

// representa expresiones binarias (+, -, *, /)
class BinaryExp : public Exp {    // PLUS, MINUS, MULT, DIV
	public:
		BinaryExp(Exp *e1_, Exp *e2_)
			: e1(e1_), e2(e2_) { }
		~BinaryExp() {
			delete e1;
			delete e2;
		}

	protected:
		Exp *e1;
		Exp *e2;
};

// representa expresiones unarias (sin, cos, tan)
class UnaryExp : public Exp {    // SIN, COS, TAN
	public:
		UnaryExp(Exp *e1_)
			: e1(e1_) { }
		~UnaryExp() {
			delete e1;
		}

	protected:
		Exp *e1;
};

// representa expresiones variables ( X )
class VariableExp : public Exp {    // VARIABLE
	public:
		std::string exp_str() {
			return std::string("X");
		};
		/*
		void print() {
			std::cout << this->exp_str() << std::endl;
		};
		*/

		double evaluate(double X) { 
			return X;
		}
		Exp *derivate()    { return (new ConstExp(1)); }
		Exp *clone()       { return (new VariableExp()); }
};

class PlusExp : public BinaryExp {
	public:
		PlusExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2){}

		std::string exp_str() {
			return "(" + e1->exp_str() + " + " + e2->exp_str() + ")";
		};
		/*
		void print() {
			std::cout << this->exp_str() << std::endl;
		};
		*/

		double evaluate(double X) {
			return e1->evaluate(X) + e2->evaluate(X);
		}
		Exp *derivate() { 
			return (new PlusExp(e1->derivate(), e2->derivate()));
		}
		Exp *clone() {
			return (new PlusExp(e1->clone(), e2->clone()));
		}
};

class MinusExp : public BinaryExp {
	public:
		MinusExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2){}

		std::string exp_str() {
			return "(" + e1->exp_str() + " - " + e2->exp_str() + ")";
		};
		/*
		void print() {
			std::cout << this->exp_str() << std::endl;
		};
		*/

		double evaluate(double X) {
			return e1->evaluate(X) - e2->evaluate(X);
		}
		Exp *derivate() { 
			return (new MinusExp(e1->derivate(), e2->derivate()));
		}
		Exp *clone() {
			return (new MinusExp(e1->clone(), e2->clone()));
		}
};

class MultExp : public BinaryExp {
	public:
		MultExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2){}

		std::string exp_str() {
			return /*"(" + */e1->exp_str() + "*" + e2->exp_str()/* + ")"*/;
		};
		/*
		void print() {
			std::cout << this->exp_str() << std::endl;
		};
		*/

		double evaluate(double X) {
			return e1->evaluate(X) * e2->evaluate(X);
		}
		Exp *derivate() { 
			return (new PlusExp(new MultExp(e1->derivate(), e2->clone()), new MultExp(e1->clone(), e2->derivate())));
		}
		Exp *clone() {
			return (new MultExp(e1->clone(), e2->clone()));
		}
};

class DivExp : public BinaryExp {
	public:
		DivExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2){}

		std::string exp_str() {
			return /*"(" + */e1->exp_str() + "/" + e2->exp_str()/* + ")"*/;
		};
		/*
		void print() {
			std::cout << this->exp_str() << std::endl;
		};
		*/

		double evaluate(double X) { 
			double val_denom = e2->evaluate(X);
			if(val_denom == 0) {
				throw "zero division";
			}
			return e1->evaluate(X) / val_denom;
		}
		Exp *derivate() { 
			/*
			double val_denom = e2->evaluate();
			if(val_denom == 0) {
				throw "zero division"
			}
			*/

			return (new DivExp(new MinusExp(new MultExp(e1->derivate(), e2->clone()), new MultExp(e1->clone(), e2->derivate())), new MultExp(e2->clone(), e2->clone())));
		}
		Exp *clone() { return (new DivExp(e1->clone(), e2->clone())); }
};

class SinExp : public UnaryExp {
	public:
		SinExp(Exp *e1) : UnaryExp(e1){}

		std::string exp_str() {
			return "sin(" + e1->exp_str() + ")";
		};
		/*
		void print() {
			std::cout << this->exp_str() << std::endl;
		};
		*/

		double evaluate(double X) {
			return std::sin(e1->evaluate(X));
		}
		Exp *derivate();
		Exp *clone() {
			return (new SinExp(e1->clone()));
		}
};

class CosExp : public UnaryExp {
	public:
		CosExp(Exp *e1) : UnaryExp(e1){}

		std::string exp_str() {
			return "cos(" + e1->exp_str() + ")";
		};
		/*
		void print() {
			std::cout << this->exp_str() << std::endl;
		};
		*/

		double evaluate(double X) {
			return std::cos(e1->evaluate(X));
		}
		Exp *derivate() { 
			return (new MultExp(new MultExp(new ConstExp(-1), new SinExp(e1->clone())), e1->derivate()));
		}
		Exp *clone() {
			return (new CosExp(e1->clone()));
		}
};

inline Exp* SinExp::derivate() {
	return (new MultExp(new CosExp(e1->clone()), e1->derivate()));
}

class TanExp : public UnaryExp {
	public:
		TanExp(Exp *e1) : UnaryExp(e1){}

		std::string exp_str() {
			return "tan(" + e1->exp_str() + ")";
		};
		/*
		void print() {
			std::cout << this->exp_str() << std::endl;
		};
		*/

		double evaluate(double X) {
			return std::tan(e1->evaluate(X));
		}
		Exp *derivate() { 
			return (new MultExp(new DivExp(new ConstExp(1), new MultExp(new CosExp(e1->clone()), new CosExp(e1->clone()))), e1->derivate()));
		}
		Exp *clone() {
			return (new TanExp(e1->clone()));
		}
};


void ej_5()
{
	Exp *expr = new DivExp(
			new SinExp(                        // numerador
				new PlusExp(
					new MultExp(
						new ConstExp(3),
						new VariableExp()),
					new ConstExp(4))),
			new PlusExp(                       // denominador
				new ConstExp(2),
				new MultExp(
					new ConstExp(3),
					new CosExp(
						new DivExp(
							new VariableExp(),
							new PlusExp(
								new ConstExp(2),
								new VariableExp()))))));



	expr->print();

	double val = expr->evaluate(3.14);

	std::cout << "la Exp evaluada en 3.14 vale: " << val << std::endl;
	Exp *deriv = expr->derivate();

	deriv->print();

	delete deriv;
	delete expr;

	return;
}




///////////////////
// EJERICICIO 06 //
///////////////////
/*
Una pila (stack en inglés) es una estructura de datos que permite almacenar y recuperar datos, siendo 
la semántica de acceso a sus elementos del tipo LIFO (del inglés Last In, First Out, «último en entrar, 
primero en salir»). Esta estructura es de uso frecuente en el área de informática debido a su 
simplicidad y capacidad de dar respuesta a numerosos problemas.  
Para el manejo de los datos cuenta con dos operaciones básicas: push, que coloca un nuevo objeto 
en la pila, y su operación inversa, pop, que retira el último elemento apilado. Puede existir además 
una operación para chequear si el stack está o no vacío. 
En cada momento sólo se tiene acceso a la parte superior de la pila, es decir, al último objeto apilado 
(denominado TOS: Top of Stack en inglés). La operación retirar (pop) permite obtener este 
elemento, que es retirado de la pila permitiendo el acceso al anterior (apilado con anterioridad), que 
pasa a ser el último, el nuevo TOS. 
Se solicita implementar el UDT Stack para almacenar caracteres con su interface básica: 
class Stack { 
    public: 
        void push(char c);     // coloca un nuevo carácter en la pila 
        char pop();            // retira el elemento al tope del stack 
        bool isEmpty() const; // retorna indicando si el stack está vacío  
    private: 
        // ... 
        // ... 
}; 
*/

class Stack_6 { 
	public: 
		// coloca un nuevo carácter en la pila 
		void push(char c) {
			data.push_back(c);
		}
		char pop() {            // retira el elemento al tope del stack 
			if(this->isEmpty()) return '\0';
			char ret = data[data.size() - 1];
			data.pop_back();
			return ret;
		}
		bool isEmpty() const { // retorna indicando si el stack está vacío  
			return !data.size();
		}
	private: 
		std::vector<char> data;
}; 

void ej_6() 
{
	Stack_6 st;
	std::cout << "pusheo: a, b, c" << std::endl;

	st.push('a');
	st.push('b');
	st.push('c');

	while(!st.isEmpty()) {
		std::cout << "pop! " << st.pop() << std::endl;
	}
}

///////////////////
// EJERICICIO 07 //
///////////////////
/*
Redefina la clase Stack para que funcione como una interfaz pura (clase abstracta) para el manejo 
de una pila de caracteres. La interfaz debe declarar únicamente métodos virtuales puros e incluir un 
destructor virtual: 
class Stack { 
    public: 
        virtual void push(char c) = 0; 
        virtual char pop() = 0; 
        virtual bool isEmpty() const = 0; 
        virtual ~Stack() { } 
}; 
Implemente una clase derivada concreta que herede de Stack utilizando alguna estructura de 
almacenamiento interna. Por ejemplo: ArrayStack implementa la pila mediante un contenedor 
contiguo interno (como std::vector<char> o un arreglo dinámico). 
Bonus: Implementar LinkedListStack mediante una lista simplemente enlazada interna de 
nodos dinámicos (Node *). 
*/

class Stack { 
	public: 
		virtual void push(char c) = 0; 
		virtual char pop() = 0; 
		virtual bool isEmpty() const = 0; 
		virtual ~Stack() { } 
}; 

class ArrayStack : public Stack {
	public: 
		// coloca un nuevo carácter en la pila 
		void push(char c) override {
			data.push_back(c);
		}
		char pop() override {            // retira el elemento al tope del stack 
			if(this->isEmpty()) return '\0';
			char ret = data[data.size() - 1];
			data.pop_back();
			return ret;
		}
		bool isEmpty() const override { // retorna indicando si el stack está vacío  
			return !data.size();
		}
	private:
		std::vector<char> data;
};

class Node {
	public:
		Node* next;
		char value;
		Node(char c) {
			next = nullptr;
			value = c;
		}
};

class LinkedListStack : public Stack {
	public:
		LinkedListStack() {
			top = nullptr;
			count = 0;
		}
		void push(char c) override {
			Node* temp = new Node(c);
			temp->next = top;
			top = temp;

			count++;
		}
		char pop() override {
			if (top == nullptr) {
				std::cout << "Stack Underflow" << std::endl;
				return -1;
			}
			Node* temp = top;
			top = top->next;
			int val = temp->value;

			count--;
			delete temp;
			return val;
		}
		bool isEmpty() const override {
			return !count;
		}
	private:
		Node* top;
		int count;
};


void ej_7() 
{
	ArrayStack st;
	std::cout << "pusheo: a, b, c" << std::endl;

	st.push('a');
	st.push('b');
	st.push('c');

	while(!st.isEmpty()) {
		std::cout << "pop! " << st.pop() << std::endl;
	}

	LinkedListStack ll_st;
	std::cout << "Al stack de linked list pusheo: x, y, z" << std::endl;

	ll_st.push('x');
	ll_st.push('y');
	ll_st.push('z');

	while(!ll_st.isEmpty()) {
		std::cout << "pop! " << ll_st.pop() << std::endl;
	}
}



int main() {
	// descomentar el ejercicio que se quiera probar
	// ej_1();
	// ej_2();
	// ej_3();
	// ej_4();
	// ej_5();
	// ej_6();
	ej_7();
	return 0;
}
