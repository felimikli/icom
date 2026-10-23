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
Resuelva nuevamente el ejercicio 9 de la práctica 8, utilizando ahora std::sort para ordenar un 
std::array de Ternas. Pruebe con distintos criterios de ordenamiento: de menor a mayor, de 
mayor a menor y por diferentes campos. 


SOLUCION EN PRACTICA 8 EJERCICIO TERNAS:

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
Escribir un programa que ordene un arreglo nativo de estructuras Terna por el campo value 
utilizando la función qsort()  e implementando una función de comparación adecuada. 
struct Terna {  
    int i; 
    int j; 
    int value;  
}; 
Prototipo de qsort() (busque la documentación de referencia en la WEB o en man pages):  
#include <cstdlib> 
qsort(void *base, size_t nmemb, size_t size, 
      int (*compar)(const void *, const void *) ); 
 
¿Qué función de comparación usaría si quiere que el ordenamiento sea por la distancia entre (i,j) 
y el origen? 
 
struct Terna {  
	int i; 
	int j; 
	int value;  
}; 


int comp(const void* a, const void* b) {
	// casteo los punteros a void a y b a ternas
	Terna t1 = *(Terna *)a;
	Terna t2 = *(Terna *)b;
	// comparo su valor
	return t1.value > t2.value;
}

int dist(const void* a, const void* b) {
	// casteo los punteros a void a y b a ternas
	Terna t1 = *(Terna *)a;
	Terna t2 = *(Terna *)b;
	// obtengo la distancia al cuadrado de cada terna al origen
	double dist_sq_1 = (t1.i * t1.i) + (t1.j * t1.j);
	double dist_sq_2 = (t2.i * t2.i) + (t2.j * t2.j);
	// comparo su distancia al cuadrado es lo mismo que comparar su distancia
	return dist_sq_1 > dist_sq_2;
}

void ej_12() 
{
	// defino el arreglo de ternas
	Terna v[4] = {{0,0,-2}, {0, 1, 4}, {1, 3, 1}, {2, 1, 2}};


	for(int i = 0; i < 4; i++) {
		std::cout << "i, j, val: " << v[i].i << ", " << v[i].j << ", " << v[i].value << "   ";
	}
	std::cout << std::endl;

	// ordeno por value
	std::qsort(v, 4, sizeof(Terna), comp);

	// muestro
	for(int i = 0; i < 4; i++) {
		std::cout << "i, j, val: " << v[i].i << ", " << v[i].j << ", " << v[i].value << "   ";
	}
	std::cout << std::endl;

	// ordeno por distancia al origen
	std::qsort(v, 4, sizeof(Terna), dist);

	// muestro
	for(int i = 0; i < 4; i++) {
		std::cout << "i, j, val: " << v[i].i << ", " << v[i].j << ", " << v[i].value << "   ";
	}
	std::cout << std::endl;
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
*/


struct Terna {  
	int i; 
	int j; 
	int value;  
}; 


bool comp_val(const Terna &t1, const Terna &t2) {
	// comparo su valor
	return t1.value > t2.value;
}

bool comp_dist(const Terna &t1, const Terna &t2) {
	// obtengo la distancia al cuadrado de cada terna al origen
	double dist_sq_1 = (t1.i * t1.i) + (t1.j * t1.j);
	double dist_sq_2 = (t2.i * t2.i) + (t2.j * t2.j);
	// comparo su distancia al cuadrado es lo mismo que comparar su distancia
	return dist_sq_1 > dist_sq_2;
}

void print_terna_arr(std::array<Terna, 4> v) {
	for(size_t i = 0; i < v.size(); i++) {
		std::cout << "i, j, val: " << v[i].i << ", " << v[i].j << ", " << v[i].value << "   ";
	}
	std::cout << std::endl;
}

void ej_1() 
{
	std::array<Terna, 4> v = {(Terna){0,0,-2}, (Terna){0, 1, 4}, (Terna){1, 3, 1}, (Terna){2, 1, 2}};

	print_terna_arr(v);

	// ordeno por value
	std::sort(v.begin(), v.end(), comp_val);

	// muestro
	print_terna_arr(v);

	// ordeno por distancia al origen
	std::sort(v.begin(), v.end(), comp_dist);

	// muestro
	print_terna_arr(v);
}

///////////////////
// EJERICICIO 02 //
///////////////////
/*
Se desea implementar un functor Noiserer, que cuando es activado con un double como 
argumento retorne un valor que resulte de sumar ese argumento con una componente 
pseudoaleatoria. La componente pseudoaleatoria estará limitada entre 2 umbrales minV y maxV 
que serán indicados en la construcción del objeto functor. Verifique su funcionamiento utilizando el 
functor como función de transformación en la std::transform desde un vector<double> 
in a otro vector<doble> out, de tal forma que los elementos de out sean iguales a los de in, 
pero afectados con un Noiserer 
class Noiserer { 
    public: 
        Noiserer (double minV_, double maxV_); 
        double operator()(double v); 
    private: 
        double minV, maxV; 
}; 
*/
class Noiserer { 
	public: 
		Noiserer (double minV_, double maxV_) {
			// settear los valores limites
			minV = minV_;
			maxV = maxV_;
		}
		double operator()(double v) {
			int n = rand();
			// r es el rango
			double r = maxV - minV;
			// retorno el valor
			// mas el numero random, dividido por (RAND_MAX / r), es decir,
			// n queda entre 0 y (maxV - minV)
			// y le sumo minV para que quede entre
			// minV y maxV
			return v + (n/((double) RAND_MAX / r)) + minV;
		}
	private: 
		double minV, maxV; 
}; 

void ej_2() 
{
	std::srand(time(0));
	// inicializo con -1 y 1
	// al numero que le pase le va a agregar ruido de modulo 1
	Noiserer noise(-1, 1);	
	double n = 120;
	std::cout << "n: " << n << " -> " << noise(n) << std::endl;
	std::cout << "n: " << n << " -> " << noise(n) << std::endl;
	std::cout << "n: " << n << " -> " << noise(n) << std::endl;

	std::vector<double> in(20, 0);
	std::vector<double> out(20, 0);

	// transformar con Noiserer(-1, 1)
	// le agrega ruido de modulo 1 a cada elemento de in
	std::transform(in.begin(), in.end(), out.begin(), Noiserer(-1, 1));


	// mostrar
	for(auto e : in) {
		std::cout << e << ", ";
	}
	std::cout << std::endl;

	for(auto e : out) {
		std::cout << e << ", ";
	}
	std::cout << std::endl;

}

///////////////////
// EJERICICIO 03 //
///////////////////
/*
Dado el siguiente UDT: 
struct A { 
   int val; 
   A() {  
       val=0;  
       cout << "A default: "<<this << '\t' <<  val << endl; 
   } 
   A(int v) {  
       val=v;  
       cout<< " A con argumento: "<< this << '\t' <<  val << endl; 
   } 
   ~A() { 
      cout << "~A: "<< this << '\t' << val<<endl; 
   } 
}; 
¿Puede decir cuál es la diferencia entre las siguientes sentencias (antes de correr el programa)?: 
int main(){ 
   A *pa = new A(10); 
   A *pb = new A[10]; 
 
// destruccion de pa y pb 
 
   return 0; 
} 
¿Cómo destruiría pa y pb?  
*/


void ej_3() 
{
// La sentencia:
// A *pa = new A(10);
// aloca en el heap memoria correspondiente a un
// struct A, inicializado con val = 10
//
// Mientras que:
// A *pb = new A[10];
// aloca en el heap memoria correspondiente a
// 10 structs A,  inicializados con el constructor default val = 0;
//
// Para destruir:
//
// A *pa = new A(10);
// ->
// delete pa;
//
// A *pb = new A[10];
// ->
// delete [] pb;

}

///////////////////
// EJERICICIO 04 //
///////////////////
/*
En una matriz simétrica existe información redundante ya que el elemento (i,j) es igual al elemento 
(j,i). Se solicita implementar un UDT que permita manejar matrices simétricas evitando esa 
redundancia. La interfaz deseada para este UDT es: 
 
class SimMatrix { 
    public: 
        SimMatrix(size_t dim);  // define una matriz de dim x dim 
        SimMatrix(const SimMatrix &);  // copy-constructor 
        ~SimMatrix(); 
        void setElement(int i, int j, double val); 
        double getElement(int i, int j) const; 
        int getDim() const; 
    private: 
        vector<double> *values; 
        size_t dim; 
}; 
Implemente los métodos incluyendo el constructor y destructor. Compruebe su correcto 
funcionamiento. 
*/


class SimMatrix { 
	public: 
		SimMatrix(size_t dim) {  // define una matriz de dim x dim 
			// dimension de esta instancia es this->dim, le asigno el parametro dim
			this->dim = dim;
			// values apunta a muchos vectores (dim) alocados en el heap con new
			values = new std::vector<double>[dim];

			// cada vector es una fila, y como la matriz es simetrica,
			// se guarda solo el triangulo inf:
			// 0
			// 0 0
			// 0 0 0
			// 0 0 0 0
			// ...
			//
			// entonces los vectores tienen tamano i + 1,
			// donde i es el numero de fila
			//
			for(size_t i = 0; i < dim; i++) {
				values[i].resize(i + 1);
			}
		}
		/*
		SimMatrix(const SimMatrix &a) {  // copy-constructor 
			//asigno dimension igual a la de a
			dim = a.getDim();

			// lo mismo que antes, pero copiando valor por valor
			// obteniendo los valores de a con getElement
			values = new std::vector<double>[dim];
			for(size_t i = 0; i < dim; i++) {
				// j va desde 0 hasta i, no hasta dim!
				for(size_t j = 0; j <= i; j++) {
					values[i].push_back(a.getElement(i, j));
				}
			}

		}
		*/
		~SimMatrix() {
			// delete con corchetes porque se uso new ...[dim]
			delete [] values;
		}
		void setElement(int i, int j, double val) {
			if(i < j) {
				// si i < j, estoy en el triangulo superior
				// setteo el valor simetrico (j, i)
				setElement(j, i, val);
				return;
			}
			values[i][j] = val;
		}

		double getElement(int i, int j) const {
			if(i < j) {
				// si i < j, estoy en el triangulo superior
				// getteo el valor simetrico (j, i)
				return getElement(j, i);
			}
			return values[i][j];
		}
		int getDim() const {
			return dim;
		}
		void print() {
			// printeo
			for(size_t i = 0; i < dim; i++) {
				for(size_t j = 0; j < dim; j++) {
					std::cout << getElement(i, j) << ", ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			std::cout << std::endl;
		}
		SimMatrix &operator=(const SimMatrix &m) {

			if(this == &m) return *this;
			size_t aux_dim = m.getDim();
			// aloco un nuevo values auxiliar
			std::vector<double> * aux = new std::vector<double>[aux_dim];

			// lo mismo que antes, pero copiando valor por valor
			// obteniendo los valores de a con getElement
			for(size_t i = 0; i < aux_dim; i++) {
				// j va desde 0 hasta i, no hasta dim!
				for(size_t j = 0; j <= i; j++) {
					aux[i].push_back(m.getElement(i, j));
				}
			}

			// borro lo que tengo en esta matriz
			delete [] values;

			// le asigno a esta matriz el auxiliar
			dim = aux_dim;
			values = aux;

			// retorno esta matriz pues es la que cambie
			return *this;

		}

	private: 

		std::vector<double> * values; 
		size_t dim; 
}; 

void ej_4() 
{
	SimMatrix m(8);


	m.print();
	m.setElement(6, 7, 20);
	m.print();
	m.setElement(1, 2, 21);
	m.print();
	m.setElement(7, 6, 2);
	m.print();
}

///////////////////
// EJERICICIO 05 //
///////////////////
/*
Implemente la función sumaSimMatrix que sume matrices simétricas y retorne una nueva 
simMatrix representando el resultado: 
      SimMatrix *sumaSimMatrix(const SimMatrix &m1, const SimMatrix &m2); 
*/

SimMatrix * sumaSimMatrix(const SimMatrix &m1, const SimMatrix &m2) {
	// asumo que m1 y m2 tienen misma dimension
	// obtengo la dim
	int dim = m1.getDim();

	// Creo una nueva matriz, y la aloco en el heap para
	// poder retornar el puntero
	SimMatrix * res = new SimMatrix(dim);

	// lleno la matriz con la suma
	for(int i = 0; i < dim; i++) {
		for(int j = 0; j <= i; j++) {
			// la suma en la pos (i, j) es m1.getElement(i, j) + m2.getElement(i,j)
			(*res).setElement(i, j, m1.getElement(i, j) + m2.getElement(i, j));
		}
	}
	return res;

}


void ej_5() 
{
	// creo matriz m1 y m2 y les pongo algunos numeros
	// y las imprimo
	SimMatrix m1(8);

	m1.setElement(6, 7, 1);
	m1.setElement(1, 2, 7);
	m1.setElement(1, 3, 8);
	m1.setElement(1, 4, 2);

	m1.print();

	SimMatrix m2(8);

	m2.setElement(6, 7, 10);
	m2.setElement(1, 2, 10);
	m2.setElement(2, 3, 10);
	m2.setElement(2, 4, 10);

	m2.print();


	// guardo la suma en el puntero s y la imprimo
	SimMatrix * s = sumaSimMatrix(m1, m2);
	(*s).print();

	// Como sumaSimMatrix usa new, hay que deletear
	delete s;
}

///////////////////
// EJERICICIO 06 //
///////////////////
/*
En el ejercicio 4:  
a) ¿piensa que definir un copy-constructor es estrictamente necesario? Justifique. 
b) Si quisiera hacer la operación a = b, donde tanto a y b son instancias de SimMatrix, 
¿piensa que es necesario redefinir el operador asignación? Justifique y en caso de creerlo 
necesario, de una implementación que siga el siguiente prototipo. 
SimMatrix &operator=(const SimMatrix &m); 
*/

void ej_6() 
{
	// a) No es estrictamente necesario un copy-constructor, pero es util
	// sin un copy constructor, se tendria que manualmente crear una nueva
	// matriz, y copiar valor por valor de la matriz que se desea copiar.
	// 
	// Con el copy constructor se hace simplemente a = b y se copian
	//
	// b) si no se define un copy-constructor, hay que redefinir el
	// operador = para que a = b copie b en a valor a valor
	//
	// en la clase esta la implementacion de 
	// SimMatrix &operator=(const SimMatrix &m); 
	// y se comentó el copy-constructor

	// creo matrizes y pruebo usar =
	SimMatrix m1(4);

	m1.setElement(3, 2, 1);
	m1.setElement(1, 2, 7);
	m1.setElement(3, 3, 8);
	m1.setElement(1, 3, 2);

	std::cout << "Matriz 1:" << std::endl;
	m1.print();

	SimMatrix m2(8);

	m2.setElement(6, 7, 10);
	m2.setElement(1, 2, 10);
	m2.setElement(2, 3, 10);
	m2.setElement(2, 4, 10);

	std::cout << "Matriz 2:" << std::endl;
	m2.print();

	std::cout << "m2 = m1" << std::endl;
	m2 = m1;

	std::cout << "Matriz 2:" << std::endl;
	m2.print();

	SimMatrix m3(8);
	std::cout << "m1 = m3" << std::endl;
	m1 = m3;

	std::cout << "Matriz 1:" << std::endl;
	m1.print();

	std::cout << "Matriz 2:" << std::endl;
	m2.print();

	std::cout << "Matriz 3:" << std::endl;
	m3.print();

}

///////////////////
// EJERICICIO 07 //
///////////////////
/*
Con fines didácticos y de aprendizaje ((redundancia en el enunciado)) (y sin utilizar la librería String), implementar el UDT 
MyString para representar strings. El tipo tiene que ser implementado de tal forma de poder 
soportar el uso siguiente: 
 
MyString s1("hola mundo"); 
MyString s2(s1); 
MyString s3; 
 
s3 = s1 + s2; 
s3[4] = 'X'; 
char c = s3[2]; 
*/

// Le dedico este problema a mi queridisimo amigo de Mar del Plata
// Tomas Diz Nuts
class MyString {
	public:

		// constructor default
		MyString() {
			// creo un string que el char* sea ""
			// tiene tamaño 0 y su unico elemento es
			// el char 0 = '\0' (fin de string)
			s = new char[1];
			l = 0;
			s[0] = '\0';
		}

		// constructor de char *
		MyString(const char * s_) {
			// recorro s_ con k hasta llegar al final ('\0')
			size_t k = 0;
			while(s_[k] != '\0') {
				k++;
			}
			// la longitud l es este k
			l = k;

			// inicializo el char* con l + 1 para guardar el
			// character de fin '\0'
			s = new char[l + 1];
			for(size_t i = 0; i <= l; i++) {
				// copio valor a valor de s_, incluyendo '\0'
				s[i] = s_[i];
			}
		}

		// copy_constructor
		MyString(const MyString &s_) {
			// la longitud es la longitud de s_
			l = s_.l;

			//inicializo s
			s = new char[l + 1];
			for(size_t i = 0; i <= l; i++) {
				// copio valor a valor de s_, incluyendo '\0'
				s[i] = s_.s[i];
			}
		}

		~MyString() {
			delete [] s;
		}

		char &operator[](const size_t index) {
			// simplemente retorna el character 
			// en el indice index de s
			return s[index];
		}

		char operator[](const size_t index) const {
			// esto es lo mismo, pero no retorna 
			// referencia, retorna una constante
			//
			// retornar referencia sirve si se
			// quiere hacer:
			// string[3] = 'c';
			//
			// mientras que retornar un constante sirve para
			// char c = string[2];
			return s[index];
		}

		// operador =
		MyString operator=(const MyString &s_) {
			if(this == &s_) {
				return *this;
			}

			// a_l y a_s variables auxiliares
			size_t a_l = s_.l;
			char * a_s = new char[a_l + 1];
			for(size_t i = 0; i <= a_l; i++) {
				// copio en las auxiliares del parametro s_
				a_s[i] = s_.s[i];
			}

			// borro lo que tengo en s y remplazo por lo de
			// auxiliares (s_)
			delete [] s;
			l = a_l;
			s = a_s;
			return *this;
		}

		// quiero que s1 + s2 sea la concatenacion de s1 y s2
		MyString operator+(const MyString &s_) const {
			// la longitud de la concatenacion el la suma de las longitudes
			size_t a_l = s_.l + l;

			// a es un auxiliar con la longitud total
			char a[a_l + 1];

			// primero lleno a a hasta la longitud de s1 (l)
			// copiando los valores de s1
			for(size_t i = 0; i < l; i++) {
				a[i] = s[i];
			}

			// luego lleno a a desde la longitud de s1 (l)
			// hasta la longitud de s2 (s_.l)
			// copiando los valores de s2
			for(size_t i = 0; i <= s_.l; i++) {
				a[i + l] = s_.s[i];
			}
			return MyString(a);
				
		}

		size_t size() {
			return l;
		}
		void print() {
			for(size_t i = 0; i < l; i++) {
				std::cout << s[i];
			}
			std::cout << std::endl;
		}
	private:
		size_t l;
		char * s;
};

void ej_7() 
{
	MyString s1("hola mundo"); 
	s1.print();

	MyString s2(s1); 
	s2.print();

	MyString s3; 
	s3.print();

	s3 = s1 + s2; 
	s3.print();

	s3[4] = 'X'; 
	char c = s3[0]; 

	std::cout << "c: " << c << std::endl;


	// imprimo el string s3 para ver
	// tiene que ser la concatenacion
	// de s1 con s2,
	// donde s2 es igual a s1
	// con el quinto caracter = 'X'
	s3.print();
}

///////////////////
// EJERICICIO 08 //
///////////////////
/*
Se desea representar un polinomio a través de la entidad como la siguiente. Terminar de 
implementar el UDT. 
 
class Polinomio { 
    public: 
        // construye un polinomio con los coeficientes y grado dados que 
        // representa al polinomio: 
        // coefs[0] + coefs[1]*x + coefs[2]*x^2 + ... + coefs[n]*x^n 
        Polinomio(const double *coefs, int n); 
        Polinomio(const Polinomio &p); 
        ~Polinomio(); 
 
 
  Polinomio &operator=(const Polinomio &p); 
 
 
  Polinomio operator+(const Polinomio &p); 
 
  Polinomio operator*(const Polinomio &p); 
 
        double evaluate(double x); // evalua el polinomio en el valor x 
 
        Polinomio derivate();   // crea y retorna el polinomio derivado 
 
        // crea y retorna el polinomio integrado con constante 'c' 
        Polinomio integrate(double c); 
 
    private: 
        // puntero a coeficientes 
        double *coefs; 
 
  int     grado; 
}; 
Se solicita terminar de implementar el UDT. Evalúe la necesidad de implementar un constructor de 
copia, un operador de asignación y un destructor. En el caso de llegar a la conclusión de que hacen 
falta, impleméntelos. 
*/

class Polinomio { 
	public: 
		// construye un polinomio con los coeficientes y grado dados que 
		// representa al polinomio: 
		// coefs[0] + coefs[1]*x + coefs[2]*x^2 + ... + coefs[n]*x^n 
		Polinomio(const double * coefs_, int n) {
			grado = n;
			// recordar que hay grado + 1 coeficientes
			// grado 3 -> c_0 + c_1X + c_2X^2 + c_3X^3
			//
			// asigno la memoria a los coefs
			coefs = new double[grado + 1];
			for(int i = 0; i < grado + 1; i++) {
				// copio valor a valor
				coefs[i] = coefs_[i];
			}
		}
		// copy-constructor
		Polinomio(const Polinomio &p) {
			// asigno grado
			grado = p.grado;

			// asigno memoria
			coefs = new double[grado + 1];
			for(int i = 0; i < grado + 1; i++) {
				// copio valor a valor
				coefs[i] = p.coefs[i];
			}

		}
		~Polinomio() {
			delete [] coefs;
		}


		// operador =
		// asignar p1 = p2
		Polinomio &operator=(const Polinomio &p) {
			// si p2 es igual a este, ya esta
			if(this == &p) {
				return *this;
			}

			// a_g  y a_coefs son auxilares
			// donde copio el polinomio que recibo p2
			//
			int a_g = p.grado;
			double * a_coefs = new double[a_g + 1];
			for(int i = 0; i < a_g + 1; i++) {
				a_coefs[i] = p.coefs[i];
			}

			// borro lo que tengo en p1 y guardo lo que tengo 
			// en las auxiliares que copie recien
			delete [] coefs;
			grado = a_g;
			coefs = a_coefs;
			
			// retorno p1 (this)
			return *this;
		}


		// operador +
		// p3 = p1 + p2
		Polinomio operator+(const Polinomio &p) {
			// el grado de la suma es el maximo 
			// de los grados de p1 y p2
			int g_sum = std::max(grado, p.grado);
			int g_min = std::min(grado, p.grado);

			// c_sum contiene la suma de los coeficientes
			double * c_sum = new double[g_sum + 1];
			for(int i = 0; i < g_sum + 1; i++) {
				// si el exponente es menor al menor grado
				// c_sum va a tener la suma de los coeficientes
				if(i < g_min + 1) {
					c_sum[i] = coefs[i] + p.coefs[i];	
				}
				// sino, alguno de los polinomios ya no tiene mas
				// coeficientes, entonces no puedo hacer coefs[i]
				// solo puedo hacer coefs[i] del que tiene mayor grado
				else if(grado == g_min) {
					c_sum[i] = p.coefs[i];	
				}
				else {
					c_sum[i] = coefs[i];	
				}
			}
			return Polinomio(c_sum, g_sum);
		}

		// operador *
		// p3 = p1 * p2
		// multiplicacion
		Polinomio operator*(const Polinomio &p) {
			// el grado de la multiplicacion es la suma de los grados
			int g_mult = grado + p.grado;
			double * c_mult = new double[g_mult + 1];

			// recorro p1 coeficiente a coeficinte
			for(int i = 0; i < grado + 1; i++) {
				// por cada coeficiente de p1, recorro
				// p2 coef a coef
				for(int j = 0; j < p.grado + 1; j++) {
					// multiplico los coeficientes
					// y el exponente es la suma de 
					// los exponentes
					//
					// (3.1*X^3) * (2*X^5) =
					// = 6.2*X^8
					c_mult[i + j] = coefs[i] * p.coefs[j];
				}
			}
			// si no entendes este algoritmo, proba multiplicar
			// dos polinomios a mano y vas a ver que es eso

			return Polinomio(c_mult, g_mult);
		}

		double evaluate(double x) { // evalua el polinomio en el valor x 
			// valor de la evaluacion empieza siendo 0
			double val = 0;

			// exponente representa la parte
			// X^i de cada termino
			// por eso empieza siendo 1,
			// cuando i = 0
			double exp = 1;
			for(int i = 0; i < grado + 1; i++) {
				// el valor es (X^i) * C_i;
				val += exp * coefs[i];

				// en cada iteracion multiplico exp por x
				// de manera que en la i-ésima iteracion
				// exp = X^i
				exp *= x;
			}
			return val;
		}

		// crea y retorna el polinomio derivado 
		Polinomio derivate() {
			// el grado del derivado es 1 menor al grado original
			int g_der = grado - 1;

			double * c_der = new double[g_der + 1];
			for(int i = 0; i < g_der + 1; i++) {
				// el coeficiente i-ésimo del derivado
				// es c_i = c_(i+1) * (i+1)
				//
				//
				// der(4*X^3) = (c_3 = 4)
				// = 4 * 3 * X^2 = 12 * X^2
				// 
				// el coeficiente c_2 es c_3 * 3
				//
				c_der[i] = (i + 1) * coefs[i + 1];
			}
			return Polinomio(c_der, g_der);
		}

		// crea y retorna el polinomio integrado con constante 'c' 
		Polinomio integrate(double c) {
			// el grado del integrado es 1 mayor al grado original
			int g_int = grado + 1;

			double * c_int = new double[g_int + 1];

			// el coeficiente independiente es la constante c
			// que se manda como parametro
			c_int[0] = c;

			for(int i = 1; i < g_int + 1; i++) {
				// el coeficiente i-ésimo del integrado
				// es c_i = c_(i-1) / i
				//
				//
				// int(4*X^3) = (c_3 = 4)
				// = 4/3 * X^4
				// 
				// el coeficiente c_4 es c_3/3
				//
				c_int[i] = coefs[i - 1] / i;
			}
			return Polinomio(c_int, g_int);
		}


		// imprimir el polinomio lindo
		// no hace falta entender esto
		void print() {
			for(int i = 0; i < grado + 1; i++) {
				if(coefs[i] == 0) {
					continue;
				}
				if(i == grado) {
					if(i == 0) {
						std::cout << coefs[0];
					}
					else if(i == 1) {
						std::cout << coefs[1] << "X";
					}
					else {
						std::cout << coefs[i] << "X^" << i;
					}
					break;
				}
				if(i == 0) {
					std::cout << coefs[0] << " + ";
					continue;
				}
				if(i == 1) {
					std::cout << coefs[1] << "X + ";
					continue;
				}
				std::cout << coefs[i] << "x^" << i << " + ";
			}
			std::cout << std::endl;
		}

	private: 
		// puntero a coeficientes 
		double *coefs; 
		int     grado; 
}; 

void ej_8() 
{
	// creo algunos polinomios para probar
	Polinomio p1((double[]){1, 9, 2, 0, 1, 0, 4}, 6);
	Polinomio p2((double[]){3, 2, 1}, 2);
	Polinomio p3((double[]){10, 5}, 1);
	Polinomio p4((double[]){2, 3, 1, 0, 1, 4}, 5);

	std::cout << "p1: " << std::endl;
	p1.print();
	std::cout << std::endl;

	std::cout << "p2: " << std::endl;
	p2.print();
	std::cout << std::endl;

	std::cout << "p3: " << std::endl;
	p3.print();
	std::cout << std::endl;

	std::cout << "p4: " << std::endl;
	p4.print();
	std::cout << std::endl;

	// algunos mas para probar la suma, multiplicacion
	// derivada e integrada
	Polinomio p5 = p2 + p3;
	Polinomio p6 = p1 * p4;
	Polinomio p7 = p2.derivate();
	Polinomio p8 = p3.integrate(1);

	std::cout << "p5 = p2 + p3: " << std::endl;
	p5.print();
	std::cout << std::endl;

	std::cout << "p6 = p1 * p4: " << std::endl;
	p6.print();
	std::cout << std::endl;

	std::cout << "p7 = p2 derivada: " << std::endl;
	p7.print();
	std::cout << std::endl;

	std::cout << "p8 = p3 integrada: " << std::endl;
	p8.print();
	std::cout << std::endl;

	double val = p8.evaluate(1);
	std::cout << "p8 evaluado en 1: " << std::endl;
	std::cout << val << std::endl;
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
	// ej_8();
	return 0;
}
