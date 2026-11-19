#include "../icom_helpers.h"

/*
 1. Crear una versión template de la función Fibonacci() para que retorne long, float, etc, en
lugar de siempre ints.
*/

template<class Num>
Num Fibonacci(int n){
	if(n < 0){
		cout << "Error Fibonacchi\n";
		return -1;
	}
	if(n == 0) return (Num) 0;
	if(n == 1) return (Num) 1;

	return (Fibonacci<Num>(n-1) + Fibonacci<Num>(n-2));
}

void ej1(void){
	cout << "\n\nEJERCICIO 2\n\n";
	size_t l = sizeof(Fibonacci<int>(2));
	size_t d = sizeof(Fibonacci<double>(4));

	cout << d << " " << l << endl;


}

/*
 2. Defina la clase template CoordenadaCartesiana3D que permita parametrizar el tipo con que se
almacena cada coordenada.
*/

template<class Num>
class C3D{
	private: 
		Num x;
		Num y;
		Num z;
	public:
		C3D(Num x_, Num y_, Num z_){
			x = x_; y= y_; z = z_;
		}
		void print(void){
			cout << "x: " << x << " y: " << y << " z: " << z << endl;	
		}
};

void ej2(void){
	cout << "\n\nEJERCICIO 2\n\n";

	C3D<float> f(2.3,3.4,4.6);
	C3D<int> i(2,3,4);

	f.print(); i.print();
	
	return;	
}

/*
 3. Crear una clase template vector<T> mínima, capaz de almacenar instancias de T. Genera una
especialización que esté optimizado para un vector de bool (para que cada bool ocupe un bit).
*/


template<class T>
class Vec{
	private:
		int sz;
		T *data;
	public:
		Vec(){
			sz = 0;
			data = nullptr;
		}
		~Vec(){
			delete [] data;
		}
};

struct BitRef{
	unsigned char * pBytes;
	int pos;

	void operator=(bool val){
		int res = pos; //corrimiento

		if(val){
			unsigned char mask = 1 << pos;
			*pBytes = *pBytes | mask;
		}

		if(!val){
			unsigned char mask = ~(1 << pos);
			*pBytes = *pBytes & mask;
		}
	}
};
template<> class Vec<bool> {
	private: 
		int sz;
		unsigned char *data;
		int sz_arr; //tamaño del arreglo
	public:



		Vec(int i){

			sz = i;
			sz_arr = i / 8;

			data = new  unsigned char[sz_arr];
		}

		bool operator[](const size_t i) const{ //Se asume que se da bien el i
			int el = i / 8; //posicion del caracter
			int res = i % 8; //corrimiento
			unsigned char c = data[el];
	
			unsigned char mask = 1 << res;
			return c & mask;

	
		}

		void set_elem(int i, bool val){
			int el = i / 8; //posicion del caracter
			int res = i % 8; //corrimiento

			if(val){
				unsigned char mask = 1 << res;
				data[el] = data[el] | mask;
			}

			if(!val){
				unsigned char mask = ~(1 << res);
				data[el] = data[el] & mask;
			}
		}
	
	


		

		
};
void ej3(void){
	cout << "\n\nEJERCICIO 3\n\n";
	
		

}

/*
 4. Implementar una función template que reciba un arreglo de elementos de tipo T y su cantidad de
elementos, y retorne el mayor elemento del arreglo.
template<typename T>
T maximo(const T datos[], int n);
a. Probar la función con arreglos de int, double y string.
b. Analizar qué operaciones debe soportar el tipo T para que la función pueda compilarse.}
c. Definir una clase Persona que contenga nombre y edad, e implementar el operador < para
comparar personas por edad. Verificar que la función maximo también pueda utilizarse con
objetos de esta clase.
*/

template<typename T>
T maximo(const T datos[], int n){
	T max = datos[0];

	for(int i = 1; i < n; i ++){
		if(datos[i] > max){
			max = datos[i];	
		}
	}

	return max;
}

/*
5. Implementar una clase template Buffer<T, N> que permita almacenar N elementos de tipo T,
donde tanto el tipo como la cantidad de elementos sean parámetros del template.
template<typename T, int N>
class Buffer {
T datos[N];
public:
T& operator[](int i);
const T& operator[](int i) const;
int size() const;
};
a.Implementar los métodos declarados.
b.Incorporar verificación de límites en el operador [].
c.Crear instancias Buffer<int, 10>, Buffer<double, 5> y Buffer<string, 3>.
d.Investigar qué ocurre cuando se intenta crear Buffer<int, n> siendo n una variable cuyo
valor se determina durante la ejecución.
*/

template<typename T, int N>
class Buffer {
	T datos[N];
	public:
		T& operator[](int i){
			if(i >= N){
				cout << "ERROR\n";
				throw 1;
			}
			return &datos[N];
		}
		const T& operator[](int i) const{
			if(i >= N){
				cout << "ERROR\n";
				throw 1;
			}
			return datos[N];
		}
		int size() const{
			return N;
		}
};

int main(void){
	//ej1();
	//ej2();
	ej3();

	return 0;
}
