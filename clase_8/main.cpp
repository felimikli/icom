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
Hacer un programa que defina arreglos nativos de 2 componentes de todos los tipos de variables 
que conoce (char, int, float, double) y de algunos UDT (Complex, Punto2D) e 
imprima la dirección de memoria de cada uno de los componentes de cada uno de los vectores. ¿Cuál 
es la distancia en bytes entre las componentes de cada vector? Comparar con lo que retorna el 
operador sizeof(). Hint: si al imprimir algún puntero (por ejemplo char *) se obtienen 
resultados no deseados, convertir la dirección a const void *. 
*/

struct Complex {
	double re, im;
	void print() {
		std::cout << "(" << re << " + i " << im << ")" << '\n';
	}
	double modulo() {
		return std::sqrt(re*re + im*im);
	}
	Complex operator+(Complex a) {
		Complex result = { re + a.re, im + a.im };
		return result;
	}
	Complex operator-(Complex a) {
		Complex result = { re - a.re, im - a.im };
		return result;
	}
	Complex operator*(Complex a) {
		Complex result = { (re * a.re) - (im * a.im), (im * a.re) + (re * a.im) };
		return result;
	}
	Complex operator/(Complex a) {
		Complex result = { ((re * a.re) + (im * a.im))/(a.re*a.re + a.im*a.im), ((im * a.re) - (re * a.im))/(a.re*a.re + a.im*a.im) };
		return result;
	}
};

struct Punto2D {
	float x, y;
};


void ej_1() 
{
	int n = 2;
	
	// los char los casteo a void* para imprimir, sino no anda bien
	// (el operador << es un asco) (C > C++)
	//
	// Para calcular la distancia, casteo a char* la direccion para poder restar en bytes
	// la distancia calculada coincide con sizeof!
	//
	//
	// en todos los casos, la distancia entre dos elementos de un arreglo
	// coincide con el sizeof del tipo del arreglo, pues todos los elementos
	// estan pegaditos uno al lado del otro en arreglos nativos
	// esto se denomina memoria contigua

	char arr_char[n];
	std::cout << "&char[0] = " << (void*) &arr_char[0] << std::endl;
	std::cout << "&char[1] = " << (void*) &arr_char[1] << std::endl;
	std::cout << "Distancia: " << (char*) &arr_char[1] - (char*) &arr_char[0] << std::endl;
	std::cout << "sizeof: " << sizeof(arr_char[0]) << std::endl;

	int arr_int[n];
	std::cout << "&int[0] = " << &arr_int[0] << std::endl;
	std::cout << "&int[1] = " << &arr_int[1] << std::endl;
	std::cout << "Distancia: " << (char*) &arr_int[1] - (char*) &arr_int[0] << std::endl;
	std::cout << "sizeof: " << sizeof(arr_int[0]) << std::endl;

	float arr_float[n];
	std::cout << "&float[0] = " << &arr_float[0] << std::endl;
	std::cout << "&float[1] = " << &arr_float[1] << std::endl;
	std::cout << "Distancia: " << (char*) &arr_float[1] - (char*) &arr_float[0] << std::endl;
	std::cout << "sizeof: " << sizeof(arr_float[0]) << std::endl;

	double arr_double[n];
	std::cout << "&double[0] = " << &arr_double[0] << std::endl;
	std::cout << "&double[1] = " << &arr_double[1] << std::endl;
	std::cout << "Distancia: " << (char*) &arr_double[1] - (char*) &arr_double[0] << std::endl;
	std::cout << "sizeof: " << sizeof(arr_double[0]) << std::endl;

	struct Complex arr_complex[n];
	std::cout << "&complex[0] = " << &arr_complex[0] << std::endl;
	std::cout << "&complex[1] = " << &arr_complex[1] << std::endl;
	std::cout << "Distancia: " << (char*) &arr_complex[1] - (char*) &arr_complex[0] << std::endl;
	std::cout << "sizeof: " << sizeof(arr_complex[0]) << std::endl;

	struct Punto2D arr_punto2d[n];
	std::cout << "&punto2d[0] = " << &arr_punto2d[0] << std::endl;
	std::cout << "&punto2d[1] = " << &arr_punto2d[1] << std::endl;
	std::cout << "Distancia: " << (char*) &arr_punto2d[1] - (char*) &arr_punto2d[0] << std::endl;
	std::cout << "sizeof: " << sizeof(arr_punto2d[0]) << std::endl;

}

///////////////////
// EJERICICIO 02 //
///////////////////
/*
¿Por qué el siguiente código no es saludable? Describa el problema. 
void fun() { 
    int a = 4;  
    int *pa; 
 
    *pa = a; 
} 


*/

void fun() { 
	    int a = 4;  
	    int *pa; 
	 
	    *pa = a;
} 

void ej_2() 
{
	fun();
	/*
	 * El codigo de la consigna no es saludable porque
	 * el puntero pa no esta inicializado
	 */
}

///////////////////
// EJERICICIO 03 //
///////////////////
/*
¿Por qué el siguiente código no es saludable? Describa el problema. 
int *getPtr() { 
    int a = 4; 
    return &a; 
} 

*/

int *getPtr() { 
	int a = 4; 
	return &a; 
} 

void ej_3() 
{
	int * i = getPtr();
	/*
	 * El codigo de la consigna no es saludable porque
	 * Inicializa una variable dentro de una funcion, 
	 * pero la memoria se libera una vez que la
	 * funcion retorna, entonces no es saludable
	 * retornar y usar esa parte de memoria
	 * fuera de la funcion
	 */
}

///////////////////
// EJERICICIO 04 //
///////////////////
/*
*/

void ej_4() 
{
	int v[5] = { 10, 20, 30, 40, 50 }; 
	int *p = v; 
	int *fin = v + 5; 

	// el puntero p al principio apunta a v, osea el primer elemento de v[5]
	// fin apunta a v + 5, es decir, uno mas que el ultimo elemento de v[5]
	// sumar uno a v equivale a "avanzar" un elemento en el array
	// para recorrer, printeo p y despues le sumo 1, si llegue a fin termino
	//
	while(p != fin) {
		std::cout << *p << std::endl;
		p++;
	}
}

///////////////////
// EJERICICIO 05 //
///////////////////
/*
    int x = 10; 
    int y = 20; 
 
    const int *p = &x; 
    int *const p2 = &x;  
 
Indicar cuáles de estas operaciones son válidas y cuáles no: 
    *p1 = 5; 
    p1 = &y; 
    *p2 = 5; 
    p2 = &y; 
*/

void ej_5() 
{
	int x = 10; 
	int y = 20; 

	const int * p1 = &x; 
	int * const p2 = &x;  


	// const int * corresponde a un puntero a una variable constante
	// es decir, la variable a la que apunta el puntero no se puede cambiar
	// pero si se puede cambiar A DONDE apunta el puntero
	//
	// int * const corresponde a un puntero que siempre apunta a la misma memoria
	// es decir, la variable a la que apunta el punter SI se puede cambiar
	// pero no se puede cambiar a donde apunta el puntero

	// *p1 = 5; // NO SE PUEDE
	p1 = &y; // SI
	*p2 = 5; // SI
	// p2 = &y; // NO SE PUEDE
}


///////////////////
// EJERICICIO 06 //
///////////////////
/*
6. ¿Qué hace el siguiente código? Ayuda: dibujar en papel el arreglo a, el arreglo pFilas y las 
relaciones entre sus elementos antes de ejecutar la asignación final.Compruebe su diagnóstico. 
void fun() { 
    int a[3][3] = { 0 }; 
    int *pFilas[3] = { &a[0][0], &a[1][0], &a[2][0] }; 
    pFilas[0][0] = pFilas[1][0] = pFilas[2][0] = 1; 
} 
*/

void fun_6() { 
	// Esta primera linea define una matriz de 3x3 inicializada con todos 0
	int a[3][3] = { 0 }; 



	// Esta linea define pFilas como un arreglo de 3 elementos, de punteros a int
	// y lo inicializa con los punteros al primer elemento de cada fila de a
	// &a[0][0] es la direccion de memoria del primer elemento de la primera fila de a
	// &a[1][0] es la direccion de memoria del primer elemento de la segunda fila de a
	// &a[2][0] es la direccion de memoria del primer elemento de la tercera fila de a
	// recordar que en pFilas hay tres DIRECCIONES DE MEMORIA, no elementos
	int * pFilas[3] = { &a[0][0], &a[1][0], &a[2][0] }; 


	// aqui inicializo, el primer elemento de cada fila en 1
	// pFilas[0] es &a[0][0], y lo interesante es que &a[0][0] = a[0]
	// porque a[0] es una arreglo de 3 ints, es decir una direccion de memoria!
	// entonces pFilas[0][0] = a[0][0]
	// esta linea inicializa en 1 la primera columna de a
	pFilas[0][0] = pFilas[1][0] = pFilas[2][0] = 1; 


	// imprimo a para comprobar
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}
} 

void ej_6() 
{
	fun_6();
}

///////////////////
// EJERICICIO 07 //
///////////////////
/*
Implementar la función CompareStrings() que compare strings nativos asciibéticamente, 
devolviendo 0 si los strings son iguales, un valor positivo si el primero es mayor y un valor negativo 
si el segundo es mayor. Utilizar el prototipo: 
 
int CompareStrings(const char *str1, const char *str2); 
 
Sin utilizar strcmp(). 
*/

int CompareStrings(const char *str1, const char *str2) {

	// guardo en s1 y s2 las direcciones
	// para poder ir avanzando en los strings
	const char * s1 = str1;
	const char * s2 = str2;

	while(true) {
		// si el caracter en la dir s1 es distinto al de s2
		if(*s1 != *s2) {
			// retorno la diferencia en ascii,
			// si el de s1 es menor,
			// entonces str1 es menor asciibeticamente y el numero es negativo
			// si el de s2 es menor, retorno positivo
			return (int) (*s1 - *s2);
		}
		// si estoy aca, es porque son iguales hasta ahora, entonces retorno 0, si llegue al final de los strings
		if(*s1 == '\0') {
			return 0;
		}
		// avanzo en los strings
		s1++;
		s2++;
	}
}

void ej_7() 
{
	const char * s1 = "Abel";
	const char * s2 = "Abeliano";
	const char * s3 = "Aboli";
	std::cout << CompareStrings(s1, s2) << std::endl;
	std::cout << CompareStrings(s2, s1) << std::endl;
	std::cout << CompareStrings(s1, s1) << std::endl;
	std::cout << CompareStrings(s1, s3) << std::endl;
}

///////////////////
// EJERICICIO 08 //
///////////////////
/*
Implementar la función TransponeNN() que reciba una matriz cuadrada como puntero al primer 
elemento de la matriz y la trasponga sobre sí misma. Utilizar el prototipo: 
void TransponeNN(double *matriz, int n); 
Ejemplo de uso: 
double m[10][10]; 
... 
TransponeNN(&m[0][0], 10); 
*/

void TransponeNN(double * matriz, int n) {
	double aux;
	// recorro la matriz
	for(int i = 0; i < n - 1; i++) {
		for(int j = i + 1; j < n; j++) {

			// *(matriz + (n*i) + j) = m[i][j]
			// desde puntero del primer elemento
			// si sumo 1 avanzo una columna, o me muevo uno a la derecha
			// mientras que si sumo n
			// avanzo n elementos, a la derecha, pero cuando llega al final
			// de una fila, pasa a la de abajo, entonces avanzar n elementos
			// a la derecha es lo mismo que moverse 1 para abajo
			// o avanzar una fila
			//
			// 0, 0, 0, 0, 0, 0
			// 0, 1, 0, 0, 0, 0
			// 0, 0, 0, 0, 0, 0
			// 0, 0, 0, 0, 0, 0
			//
			// digamos que estoy en el 1, si le sumo 1 a la direccion de memoria
			//
			// 0, 0, 0, 0, 0, 0
			// 0, 0, 1, 0, 0, 0
			// 0, 0, 0, 0, 0, 0
			// 0, 0, 0, 0, 0, 0
			//
			// si ahora le sumo 3
			//
			// 0, 0, 0, 0, 0, 0
			// 0, 0, 0, 0, 0, 1
			// 0, 0, 0, 0, 0, 0
			// 0, 0, 0, 0, 0, 0
			//
			// si ahora le sumo 1, "loopeo" a la fila de abajo
			//
			// 0, 0, 0, 0, 0, 0
			// 0, 0, 0, 0, 0, 0
			// 1, 0, 0, 0, 0, 0
			// 0, 0, 0, 0, 0, 0
			//
			//
			// esto es porque la memoria de la matriz es contigua, 
			// es decir, es un arreglo de arreglos, pero uno al lado del otro
			// entonces si estoy en el final de un arreglo,
			// y le sumo uno a la direccion,
			// voy a estar en el primer elemento del siguiente arreglo
			//

			aux = *(matriz + (n * i) + j);
			*(matriz + (n * i) + j) = *(matriz + (n * j) + i);
			*(matriz + (n * j) + i) = aux;
		}
	}
}

void ej_8() 
{
	const int n = 10;
	double m[n][n];
	// lleno la matriz y muestro
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			m[i][j] = (double) j;
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}

	TransponeNN(&m[0][0], n);
	std::cout << std::endl;
	std::cout << std::endl;

	// muestro la transpuesta
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

///////////////////
// EJERICICIO 09 //
///////////////////
/*
Defina un UDT que no contenga atributos, solo funciones miembros. Instancie el tipo y compruebe 
que, si bien no tiene atributos, tiene memoria asociada. ¿Cómo lo justifica? 
*/

class Funcs {
	void imprimir_hola() {
		std::cout << "hola" << std::endl;
	}
};

void ej_9() 
{
	// La variable tiene que tener memoria asociada
	// porque por definicion, una variable tiene identidad
	// es decir, tiene que ser posible diferenciar
	// dos variables aunque sean del tipo Funcs.
	// Por esto deben tener  memoria asociada, sino no se podrian diferenciar
	Funcs f;
	std::cout << sizeof(f) << std::endl;
}

///////////////////
// EJERICICIO 10 //
///////////////////
/*
Escriba un programa que defina un arreglo nativo de 5 punteros a función del tipo: 
using FunPtr = void (*)(); 
 
Instancie el arreglo para que apunte a 5 funciones distintas que lo que hagan es anunciarse con su 
nombre. Active las funciones dentro de un loop generando un número al azar X y activando la función 
que está en la posición X % 5 del vector de funciones. 
*/

using FunPtr = void (*)(); 

void func1() {
	std::cout << "soy func1" << std::endl;
}
void func2() {
	std::cout << "soy func2" << std::endl;
}
void func3() {
	std::cout << "soy func3" << std::endl;
}
void func4() {
	std::cout << "soy func4" << std::endl;
}
void func5() {
	std::cout << "soy func5" << std::endl;
}

void ej_10() 
{ 
	const int n = 5;
	// defino e inicializo el vector con las funciones
	FunPtr v[n] = {func1, func2, func3, func4, func5};

	std::srand(time(0));

	for(int i = 0; i < n; i++) {
		// consigo el rand y le hago % 5. esto me da 
		// un valor entre 0 y 4,
		// llamo a la funcion en ese indice
		v[rand() % 5]();
	}
} 

///////////////////
// EJERICICIO 11 //
///////////////////
/*
Implemente la función integra que calcule la integral definida por la función fun utilizando el 
método de trapecios con una tolerancia epsilon. Este método consiste en dividir el intervalo [a,b] 
en subintervalos y aproximar la función en cada uno de ellos por una recta. Defina un criterio 
iterativo para ir cambiando la cantidad de subintervalos hasta lograr la convergencia. Prototipos: 
using fun_ptr_t = double (*)(double); 
double integra(double a, double b, fun_ptr_t fun, double 
epsilon); 
*/
using fun_ptr_t = double (*)(double); 

double area_trapecio_rect(double a, double b, double c, double d) {
	// b - a es la base
	// (c + d) /2 es la altura del rectangulo efectivo
	return ((b - a) * ((c + d)/2));
}

double integra(double a, double b, fun_ptr_t fun, double epsilon) {
	// x y xe son los dos puntos, diferenciados por epsilon,
	// entre los cuales se calcula el area del trapecio
	double x = a;
	double xe;
	double sum = 0;
	// mientras x este a distancia mayor que epsilon de b
	while(x < b - epsilon) {
		xe = x + epsilon;
		// se calcula el area del trapecio y se suma a sum
		sum += area_trapecio_rect(x, xe, fun(xe), fun(x));
		x = xe;
	}
	// finalmente, se suma el area entre el ultimo x y b
	sum += area_trapecio_rect(x, b, fun(b), fun(x));
	// esta suma coincide con la integral!!!
	return sum;
}


double coseno(double x) {
	return (double) cos(x);
}

double criterio(double a, double b, fun_ptr_t fun, double res) {
	// criterio retorna el epsilon para la resolucion deseada res
	// criterio, achico epsilon hasta que la diferencia entre dos areas
	// iteraciones consecutivas sea menor a una resolucion deseada
	double epsilon = 1;
	double delta = 1;
	while(delta > res) {
		// el delta es la diferencia entre dos achicamientos de epsilon
		delta = fabs(integra(a, b, fun, epsilon/2) - integra(a, b, fun, epsilon));
		epsilon /= 2;
	}
	return epsilon;
}

void ej_11() 
{
	std::cout << integra(0, M_PI/2, coseno, 0.1) << std::endl;
	std::cout << integra(0, M_PI/2, coseno, 0.01) << std::endl;

	double res = 0.00001;
	double epsilon = criterio(0, M_PI/2, coseno, res);
	std::cout << integra(0, M_PI/2, coseno, epsilon) << std::endl;
}

///////////////////
// EJERICICIO 12 //
///////////////////
/*
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
 
*/
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

int main() {
	// descomentar el ejercicio que se quiera probar
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
	return 0;
}
