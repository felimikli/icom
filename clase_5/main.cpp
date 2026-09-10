#include "funcs.h"

///////////////////
// EJERICICIO 01 //
///////////////////
void ej_1() {
	std::srand(time(0));
	int k = 1000;
	const int n = 10;
	const int bins = RAND_MAX/n;

	int hist[n] = {0};

	std::vector<int> hist_vec;
	for(int i = 0; i < n; i++) {
		hist_vec.push_back(0);
	}

	std::array<int, n> hist_arr;
	hist_arr.fill(0);

	for(int i = 0; i < k; i++) {
		hist[rand()/bins]++;
	}

	for(int i = 0; i < n; i++) {
		std::cout << i+1 << ": " << hist[i] << ' ';
	}
	std::cout << std::endl;
}

///////////////////
// EJERICICIO 02 //
///////////////////

void LOC_ImprimeVector(int Vector[], int NumElementos) {
	for(int i = 0; i < NumElementos; i++) {
		std::cout << Vector[i] << ' ';
	}
	std::cout << std::endl;
}
void ej_2() {
	int n = 100;
	int arr[n];
	std::srand(time(0));
	for(int i = 0; i < n; i++) {
		arr[i] = rand();
	}

	LOC_ImprimeVector(arr, n);
}

///////////////////
// EJERICICIO 03 //
///////////////////

void LOC_IngresarVector(int Vector[], int NumElementos) {
	for(int i = 0; i < NumElementos; i++) {
		std::cin >> Vector[i];
	}
}
void ej_3() {
	int n = 4;
	int arr[n];
	LOC_IngresarVector(arr, n);
	LOC_ImprimeVector(arr, n);

}

///////////////////
// EJERICICIO 04 //
///////////////////
void LOC_OrdenaArrayNativo(int v[], int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n-i-1; j++) {
			if(v[j] > v[j+1]) {
				v[j]     = v[j] ^ v[j + 1];
				v[j + 1] = v[j] ^ v[j + 1];
				v[j]     = v[j] ^ v[j + 1];
				// int t;
				// t = v[j];
				// v[j] = v[j + 1];
				// v[j + 1] = t;
			}
		}
	}
}
void ej_4() {
	int n = 10;
	int arr[n];
	std::srand(time(0));
	for(int i = 0; i < n; i++) {
		arr[i] = rand()/10000000;
	}

	LOC_ImprimeVector(arr, n);
	LOC_OrdenaArrayNativo(arr, n);
	LOC_ImprimeVector(arr, n);
}

///////////////////
// EJERICICIO 05 //
///////////////////

void ej_5() {
	int n = 10;
	int arr[n];
	std::srand(time(0));

	IngresarVector(arr, n);
	ImprimeVector(arr, n);
	OrdenaArrayNativo(arr, n);
	ImprimeVector(arr, n);

}

///////////////////
// EJERICICIO 06 //
///////////////////


void sort_nativo(int n) {
	int arr[n];
	for(int i = 0; i < n; i++) {
		arr[i] = rand()/10000000;
	}
	OrdenaArrayNativo(arr, n);
}
//void sort_array(const int n) {
	//std::array<int, n> arr;
	//sort(arr.begin(), arr.end());
//}
void ej_6() {
	std::srand(time(0));
	int s;
	std::time_t t1, t2;
	int n = 10;
	for(int i = 0; i < n; i++) {
		s = (int) (((double)rand()/RAND_MAX) * 100000);
		std::cout << "Size: " << s << std::endl;
		std::cout << std::endl;
		t1 = std::time(nullptr);
		sort_nativo(s);
		t2 = std::time(nullptr);
		std::cout << "Time: " << std::difftime(t2, t1) << std::endl;
		std::cout << std::endl;
	}
}

///////////////////
// EJERICICIO 07 //
///////////////////

void InvierteArrayNativo(int v[], int n) {
	for(int i = 0; i < n/2; i++) {
		// swap v[i], v[(n-1) - i]: 
		v[i]         = v[i] ^ v[(n-1) - i];
		v[(n-1) - i] = v[i] ^ v[(n-1) - i];
		v[i]         = v[i] ^ v[(n-1) - i];
	}
}
 
void ej_7() {
	int n = 10;
	int arr[n];
	std::srand(time(0));
	for(int i = 0; i < n; i++) {
		arr[i] = (int) (((double)rand()/RAND_MAX) * 100);
	}
	ImprimeVector(arr, n);
	InvierteArrayNativo(arr, n);
	ImprimeVector(arr, n);
	
}

///////////////////
// EJERICICIO 08 //
///////////////////
double promedio(double datos[], int n) {
	double sum = 0;
	for(int i = 0; i < n; i++) {
		sum += datos[i];
	}
	return (sum/n);
}
double dstandard(double datos[], int n) {
	double mean = promedio(datos, n);
	double sum = 0;
	for(int i = 0; i < n; i++) {
		sum += (datos[i]-mean)*(datos[i]-mean);
	}
	return std::sqrt((sum/(n-1)));
}

void ImprimeDoubleVector(double Vector[], int NumElementos) {
	for(int i = 0; i < NumElementos; i++) {
		std::cout << Vector[i] << ' ';
	}
	std::cout << std::endl;
}

void ej_8() {
	int n = 10;
	double arr[n];
	std::srand(time(0));
	for(int i = 0; i < n; i++) {
		arr[i] = (((double)rand()/RAND_MAX) * 100);
	}
	ImprimeDoubleVector(arr, n);
	double mean = promedio(arr, n);
	double desv = dstandard(arr, n);
	std::cout << "mean: " << mean << std::endl << "std: " << desv << std::endl;
}

///////////////////
// EJERICICIO 09 //
///////////////////

struct Punto2D {  
	double x;  
	double y;  

}; 

double dist_sq(Punto2D p1, Punto2D p2) {
	return ((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

struct Triangulo { 
	Punto2D vertices[3]; 
	enum ClaseLado   { EQUILATERO, ISOCELES, ESCALENO }; 
	enum ClaseAngulo { ACUTANGULO, RECTANGULO, OBTUSANGULO }; 

	ClaseLado clasificaPorLado() {
		double a, b, c;
		a = dist_sq(vertices[0], vertices[1]);
		b = dist_sq(vertices[0], vertices[2]);
		c = dist_sq(vertices[1], vertices[2]);
		if(a == b || a == c) {
			if(b == c) {
				return (ClaseLado)EQUILATERO;
			}
			return (ClaseLado)ISOCELES;
		}
		return (ClaseLado)ESCALENO;

	}
	ClaseAngulo clasificaPorAngulo() {
		double m, s, a, b, c;
		a = dist_sq(vertices[0], vertices[1]);
		b = dist_sq(vertices[0], vertices[2]);
		c = dist_sq(vertices[1], vertices[2]);

		s = a + b + c;
		m = std::max(std::max(a, b), c);

		if(s >= 2*m) {
			if(s == 2*m) {
				return (ClaseAngulo) RECTANGULO;
			}
			return (ClaseAngulo) ACUTANGULO;
		}
		return (ClaseAngulo) OBTUSANGULO;
	}
}; 

void ej_9() {
	Punto2D p1, p2, p3;
	std::cout << "x1, y1, x2, y2, x3, y3: " << std::endl;
	std::cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
	
	Triangulo t = {.vertices = {p1, p2, p3}};
	std::cout << "0: Equilatero\n1: Isoceles\n2: Escaleno" << std::endl;
	std::cout << std::endl;
	std::cout << "0: Acutangulo\n1: Rectangulo\n2: Obtusangulo" << std::endl;
	std::cout << std::endl;
	std::cout << "Triangulo es: " << t.clasificaPorLado() << " y " << t.clasificaPorAngulo() << std::endl;
}

///////////////////
// EJERICICIO 10 //
///////////////////

bool same_bday(int dias[], int n) {
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			if(dias[i] == dias[j]) return true;
		}
	}
	return false;
}

double prob_same_bday(int num, int clase_size) {
	double sum = 0;
	for(int i = 0; i < num; i++) {
		int clase[clase_size] = {0};
		for(int j = 0; j < clase_size; j++) {
			clase[j] = (int) ((((double)rand())/RAND_MAX) * 365);
		}
		sum += same_bday(clase, clase_size);
	}
	return (sum / num);
}

void ej_10() {
	std::srand(time(0));
	int g = 10000;
	for(int i = 10; i < 70; i += 10) {
		std::cout << "probabilidad con tamaño de clase = " << i << ": " << prob_same_bday(g, i)*100 << "%" << std::endl;
	}
}

///////////////////
// EJERICICIO 11 //
///////////////////

//funcion que recibe 1 vector<char> por referencia y devuelve un bool indicando si los char recibidos son iguales (true) o no (false)
bool esIgual(std::vector<char> &c){ //TODO : Resolver esta funcion de 3 formas distintas
	return c.at(0) == c.at(1);
}

bool esIgual2(std::vector<char> &c){
	if(c.at(0) - c.at(1)) return false;
	return true;
}
//funcion que recibe 1 vector<char> por copia, y, usando la funcion esIgual(vector<char> &), imprime en pantalla si los caracteres son iguales o distintos. La funcion no devuelve nada (void)
void fijarse(std::vector<char> c){ //TODO : Resolver esta funcion de 2 formas distintas
	std::string res = "diferentes";
	if(esIgual(c)) {
		res = "iguales";
	}
	std::cout << "Los caracteres ingresados son " << res << std::endl;
}

void ej_11(){
	char c_aux;
	std::vector<char> caracteres;
	
	std::cout << "Ingrese un caracter: ";
	std::cin >> c_aux;
	caracteres.push_back(c_aux);	
	
	std::cout << std::endl << "Ingrese otro caracter: ";
	std::cin >> c_aux;
	caracteres.push_back(c_aux);

	fijarse(caracteres);
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
	ej_10();
	// ej_11();
	return 0;
}
