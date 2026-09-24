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
/*
   Un algoritmo para saber si un número es divisible por 7 consiste en multiplicar por 2 el dígito de 
   las unidades y el resultado se resta al número que forman las cifras restantes. Si el resultado es divisible 
   por siete, el número original lo es. Este proceso se repite hasta llegar a un número de un solo dígito 
   (puede ser negativo). El número original es divisible por siete si se obtiene -7, 0, o 7. Realice una función 
   que usando este algoritmo retorne verdadero o falso indicando la divisibilidad del argumento recibido. El 
   prototipo de la función deberá ser: 
   bool esDivisiblePor7(int nro);
   */


bool esDivisiblePor7(int nro) {
	if(nro < 10) {
	// "si tiene un digito el número original es divisible por siete si se obtiene -7, 0, o 7."
		return (nro == 7 || nro == 0 || nro == -7);
	}
	// Ejemplo nro = 3701
	// nro / 10 = 370	(division entera)
	// nro % 10 = 1		(unidad)
	// al resultado de la division entera se le resta dos veces la unidad como dice el enunciado
	return esDivisiblePor7((nro / 10) - 2*(nro % 10));
}

void ej_1() {
	// pruebas
	std::cout << "140: " << esDivisiblePor7(140) << std::endl;
	std::cout << "7: " << esDivisiblePor7(7) << std::endl;
	std::cout << "981: " << esDivisiblePor7(981) << std::endl;
	std::cout << "982: " << esDivisiblePor7(982) << std::endl;
	std::cout << "983: " << esDivisiblePor7(983) << std::endl;
	std::cout << "984: " << esDivisiblePor7(984) << std::endl;
	std::cout << "985: " << esDivisiblePor7(985) << std::endl;
	std::cout << "986: " << esDivisiblePor7(986) << std::endl;
	std::cout << "987: " << esDivisiblePor7(987) << std::endl;
	std::cout << "988: " << esDivisiblePor7(988) << std::endl;
	std::cout << "981371: " << esDivisiblePor7(981371) << std::endl;
}

///////////////////
// EJERICICIO 02 //
///////////////////
/*
   El algoritmo de Euclides permite calcular el máximo común divisor entre 2 números en forma muy 
   eficiente. Se basa en que si tenemos 2 números enteros A y B, con A >= B, el MCD entre A y B es 
   equivalente al MCD entre B y el resto de la división entera entre A y B ( MCD(A, B) == MCD(B, A%B) ).  
   (Hint: el MCD entre cualquier número X y cero es X).  
   Una relación muy sencilla entre el MCD y el MCM es:  
   MCM(a, b) = (a . b)  / MCD(a, b) 
   Realizar funciones que realicen el cálculo del MCD y del MCM de dos números. 
   */

int MCD(int a, int b) {
	// nunca deberia ingresarse b > a
	if(b > a) return -1;

	if(!b) { // caso base. si b = 0 => !b = True, entonces  si b = 0 retorno a porque
		 // el MCD entre cualquier número X y cero es X
		return a;
	}
	// algoritmo de euclides 
	// el MCD entre los a y b originales es igual al MCD entre b y a % b
	return MCD(b, a % b);
}

int MCM(int a, int b) {
	// enunciado
	return (a*b) / MCD(a, b);
}

void ej_2() {
	std::cout << "MCD(192, 222): " << MCD(222, 192) << std::endl;
	std::cout << "MCD(24, 12): " << MCD(24, 12) << std::endl;
	std::cout << "MCD(15, 33): " << MCD(33, 15) << std::endl;
	std::cout << "MCD(33, 25): " << MCD(33, 25) << std::endl;

	std::cout << "MCM(192, 222): " << MCM(222, 192) << std::endl;
	std::cout << "MCM(24, 12): " << MCM(24, 12) << std::endl;
	std::cout << "MCM(15, 33): " << MCM(33, 15) << std::endl;
	std::cout << "MCM(33, 25): " << MCM(33, 25) << std::endl;
}

///////////////////
// EJERICICIO 03 //
///////////////////

/*
   Se desea averiguar de cuántas formas posibles se puede llenar un 
   rectángulo de 2xn casilleros utilizando fichas de dominó (de 2x1). En la figura se 
   ve que para n = 1 hay una sola forma, para n = 2 hay 2 formas, para n = 3 hay 3 
   formas y para n = 4 hay 5 formas. 
   Escribir un programa que calcule la cantidad de formas de llenar con dominós un 
   rectángulo de 2xn casilleros.  
   Hint:  Descomponga el problema en combinaciones que empiecen con una ficha 
   vertical y combinaciones que empiecen con fichas horizontales. 
   */

int llenados(int n) {
	if(n <= 1)  {
		// caso base: si el rectangulo es de 1 o 0, tiene 1 solo ordenamiento
		return 1;
	}
	// si empiezo con uno en vertical, queda un rectangulo de n - 1 por llenar
	int vert = llenados(n-1);
	// si empiezo con uno en horizontal, queda un rectangulo de n - 2 por llenar
	int hori = llenados(n-2);
	return vert + hori;
}

void ej_3() {
	//pruebas
	for(int i = 1; i < 20; i++) {
		std::cout << "n = " << i << ": " << llenados(i) << std::endl;
	}
}

///////////////////
// EJERICICIO 04 //
///////////////////
/*
   Implementar una función que resuelva el problema de las torres de Hanoi de N discos. Encontrar 
   la cantidad de movimientos que hay que realizar para resolver el problema en función de N. Suponga que 
   cuenta con una máquina capaz de mover 1 millón de discos por segundo.  ¿Qué tiempo le llevaría resolver 
   el problema original de 99 discos? 
   */

int hanoi(int n, int from, int to, int aux) {
	if(n == 1) {
		// se mueve de from a to 
		// por cada movimiento retorno 1
		return 1;
	}
	// retorno la cantidad total de movimientos (suma)
	return hanoi(n - 1, from, aux, to) + hanoi(1, from, to, aux) + hanoi(n - 1, aux, to, from);
}


//Si solo me interesan la cantidad de movimientos, no me interesa el from to y aux
int hanoi_simplificado(int n) {
	if(n == 1) {
		// se mueve de from a to 
		// por cada movimiento retorno 1
		return 1;
	}
	// retorno la cantidad total de movimientos (suma)
	return hanoi_simplificado(n - 1) + hanoi_simplificado(1) + hanoi_simplificado(n - 1);
}

void ej_4() {
	for(int i = 1; i < 20; i++) {
		std::cout << "discos = " << i << "<=> movimientos: " << hanoi(i, 1, 3, 2) << std::endl;
	}
	// se obsevra que la cantidad de movimientos es 2^N - 1
	// si tengo una computadora que hace 10^6 mov por seg, y 99 discos
	double seg = (std::pow(2, 99) - 1) / 1000000;
	std::cout << "99 discos a 1000000 movimientos por segundo tardaria: " << seg << " segundos" << std::endl;
}

///////////////////
// EJERICICIO 05 //
///////////////////
/*
   Dada una matriz M[MX][MY] que representa el valor de cada píxel de un rectángulo de MX x MY, 
   y asumiendo que todo el rectángulo tiene el mismo color C, excepto una curva cerrada de color C1, se 
   desea hacer una función que, partiendo de un punto interior a la curva cerrada, pueda pintar todo el interior 
   con el color C1. 
   Se solicita implementar la función: 
   void FloodFill(int M[MX][MY], int X, int Y, int C1); 
   Que recibe la matriz de píxeles M, (MX x MY elementos), las coordenadas de un punto (X,Y) interior a la 
   curva cerrada, y el color del contorno C1 (con el cual deberá llenar su interior). 
   */

// tamano de la matriz
#define MX 40
#define MY 30

void FloodFill(int M[MX][MY], int X, int Y, int C1) {
	if(M[X][Y] == C1) {
		// caso base, si la celda ya esta pintada, no hago nada y retorno
		return;
	}
	// si no esta pintada, la pinto
	M[X][Y] = C1;
	// y luego paso a pintar a las celdas adyacentes (derecha, izq, arriba, abajo)
	FloodFill(M, std::min(X+1, MX-1),	Y,			C1);
	FloodFill(M, std::max(X-1, 0),		Y,			C1);
	FloodFill(M, X,				std::min(Y+1, MY-1),	C1);
	FloodFill(M, X,				std::max(Y-1, 0),	C1);
	return;
}


void ej_5() {
	std::ifstream grid("./grid.txt");
	char c;
	int M[MX][MY];
	int i = 0, j = 0;
	int C1 = 1;
	int C = 0;
	int t;


	// cargo la matriz desde el archivo ./grid.txt
	if(!grid.is_open()){
		return;
	}
	while(grid.get(c)) {
		if(c == ',') {
			// si encuentro una coma, paso de columna
			j++;
			continue;
		}
		if(c == '\n') {
			// si nueva linea, columna vuelve a cero y paso de fila
			i++;
			j = 0;
			continue;
		}
		// ascii to integer
		t = atoi(&c);
		if(t == C || t == C1) {
			// t tiene que ser alguno de los dos colores
			M[i][j] = t;
		}
	}

	// muestro la matriz
	for(int i = 0; i < MX; i++) {
		for(int j = 0; j < MY; j++) {
			std::cout << M[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	FloodFill(M, 21, 15, C1);

	// muestro la matriz llenada
	for(int i = 0; i < MX; i++) {
		for(int j = 0; j < MY; j++) {
			std::cout << M[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

///////////////////
// EJERICICIO 06 //
///////////////////
/*
   Implemente la función Replace que reemplace en el string nativo s todas las apariciones del 
   carácter viejo por el carácter nuevo.  
   Prototipo: 

   void Replace(char s[], char nuevo, char viejo); 
   */

void Replace(char s[], char nuevo, char viejo) {
	// for sin condicion de finalizacion
	for(int i = 0;; i++) {
		// fin del string
		if(s[i] == '\0') return;
		// reemplazo
		if(s[i] == viejo) s[i] = nuevo;
	}
}
void ej_6() {
	char test1[] = "Hola senor, eres un nono";
	std::cout << "test1: " << test1 << std::endl;
	Replace(test1, 'z', 'n');
	std::cout << "test1: " << test1 << std::endl;
	std::cout << std::endl;

	char test2[] = "el es muy chad";
	std::cout << "test2: " << test2 << std::endl;
	Replace(test2, 'u', 'a');
	std::cout << "test2: " << test2 << std::endl;
	std::cout << std::endl;

	char test3[] = "momo";
	std::cout << "test3: " << test3 << std::endl;
	Replace(test3, 'e', 'o');
	std::cout << "test3: " << test3 << std::endl;
	std::cout << std::endl;
}

///////////////////
// EJERICICIO 07 //
///////////////////
/*
   Implementar la función StrStr que reciba dos strings nativos y busque sobre el primero de ellos 
   por la ocurrencia del segundo.  
   Prototipo: 

   int StrStr(char s1[], char s2[]); 
   Como retorno, StrStr deberá retornar el índice del elemento sobre s1 donde comienza la ocurrencia de 
   s2. Si s2 no aparece en s1, la función deberá retornar -1. 
   Ejemplos: 

   StrStr("JUAN ESTA CASADO CON MARIA", "ASADO") retornará 11. 


   StrStr("ABCDE", "BCE") retornará -1. 
   */


int StrStr(const char s1[], const char s2[]){
	// recorro el string
	for(int i = 0;;i++){
		// si llego al final salgo
		if(s1[i] == '\0') break;
		// si encuentro un caracter que coincide con el comienzo de mi segundo string
		if(s1[i] == s2[0]) {
			// recorro ahora el otro string comparando los dos strings
			for(int j = 1;; j++) {
				//si llego al final del segundo string, es que esta contenido en s1
				if(s2[j] == '\0') return i;
				// si tienen alguna discrepancia, vuelvo a recorrer
				if(s2[j] != s1[i + j]) break;
			}
		}
	}
	return -1;
}

void ej_7() {
	std::cout << StrStr("JUAN ESTA CASADO CON MARIA", "ASADO") << std::endl;
	std::cout << StrStr("ABCDE", "BCE") << std::endl;
}

///////////////////
// EJERICICIO 08 //
///////////////////
/*
   Implementar la función StrStr del ejercicio anterior pero utilizando std::string.  
   Prototipo: 

   int StrStr(const string &s1, const string &s2); 
   Hint: s1.find(s2) 
   */
int StrStr2(const std::string &s1, const std::string &s2) {
	// uso la funcion de C++
	return s1.find(s2);
}
void ej_8() {
	const std::string s1 = "JUAN ESTA CASADO CON MARIA";
	const std::string s2 = "ASADO";
	const std::string s3 = "ABCDE";
	const std::string s4 = "BCE";

	std::cout << StrStr2(s1, s2) << std::endl;
	std::cout << StrStr2(s3, s4) << std::endl;
}

///////////////////
// EJERICICIO 09 //
///////////////////
/*
   Hacer un programa que lea un archivo con 2 columnas de valores en punto flotante representando 
   puntos (x,y) y diga para que x el valor de y es máximo. (peaks.dat). 
   */

void ej_9() {
	std::ifstream file("./peaks.dat");
	std::vector<double> xs;
	std::vector<double> ys;
	double u;
	if(!file.is_open()) {
		return;
	}
	// leo el archivo linea a linea, guardo los x en xs y los y en ys
	while(file >> u) {
		/*  x         y
		 * 2.009 12099.093
		 * 3.001 13999.038
		 * 4.000 10882.091
		 * 4.029 15092.001
		 */
		xs.push_back(u);
		file >> u;
		ys.push_back(u);
	}
	// al principio digo que el maximo esta en el indice 0
	int max_index = 0;
	// recorro  ys y si encuentro alguno mayor a y[max_indice], cambio max_indice al indice de ese valor
	// de esta manera, en max_indice queda el indice del valor de y maximo
	for(int i = 0; i < ys.size(); i++) {
		if(ys[i] > ys[max_index]) max_index = i;
	}
	// como ys y xs se cargaron paralelamente, x e y estan relacionados mediante un mismo indice
	double max_x = xs[max_index];
	double max_y = ys[max_index];
	std::cout << "x con y máximo: " << max_x << ", " << max_y << std::endl;
}
///////////////////
// EJERICICIO 10 //
///////////////////
/*
Se desea realizar un programa que pueda leer palabras desde el dispositivo estándar de entrada 
(cin) y arme estadísticas acerca de las palabras distintas y cantidad de veces que se repite cada una. 
Como resultado, el programa deberá imprimir cada palabra con las veces que ésta se repite. Para ello se 
diseñan las siguientes estructuras: 
 
struct StatWords { 
    struct StatRecord{ 
 
  
        string word; 
        // palabra en si 
        unsigned int repCnt;     // cantidad de repeticiones  
    }; 
    vector<StatRecord> records; 
 
    void addWord(const string &word); // agrega una palabra. 
                                 // si ya está presente en records 
                                 //     -> incrementa su repCnt 
                                 // si no 
                                 //     -> agrega un registro nuevo en records 
     
    void print();  
 
  // imprime las palabras y cuantas veces se 
                                 // repite 
}; 
Se solicita implementar los métodos addWord y print. Un posible programa para chequear el 
programa podría ser: 
int main() 
{ 
    StatWords stats; 
    string w; 
 
    while (cin >> w) 
        stats.addWord(w); 
 
    stats.print(); 
    return 0; 
} 
Probar el programa ejecutándolo y redirigiendo el dispositivo standard de entrada desde un archivo. 
*/

struct StatWords { 
	struct StatRecord{ 
		std::string word; 
		// palabra en si 
		unsigned int repCnt;     // cantidad de repeticiones  
	}; 
	std::vector<StatRecord> records; 

	void addWord(const std::string &word) {
		// recorro las palabras que ya tengo,
		// si esta la nueva solo le sumo uno a su cuenta
		for(int i = 0; i < records.size(); i++) {
			if(records[i].word == word) {
				records[i].repCnt++;
				return;
			}
		}
		// si no encontre nada, llegue hasta aca
		// asi que agrego la palabra al records
		records.push_back(StatRecord(word, 1));
	}
		// agrega una palabra. 
		// si ya está presente en records 
		//     -> incrementa su repCnt 
		// si no 
		//     -> agrega un registro nuevo en records 

	void print() {
		// trivial
		for(StatRecord s : records) {
			std::cout << s.word << ": " << s.repCnt << std::endl;
		}
	}

		// imprime las palabras y cuantas veces se 
                                 // repite 
}; 


void ej_10() 
{ 
    StatWords stats; 
    std::string w; 
 
    while (std::cin >> w) 
        stats.addWord(w); 
 
    stats.print(); 
} 
///////////////////
// EJERICICIO 11 //
///////////////////
/*
Como modificaría el ejemplo visto en clases de la función QuickSort para que realice un ordenamiento in 
situ (en el mimo array, sin crear nuevos arreglos). Mida la performance de versión vista en clase, con  este 
ordenamiento in situ y con stl::sort. 


void ordenarVector(vector<int> &b)
{
	if (b.size() <= 1)
		return;
	vector<int> menores;
	vector<int> mayores;
	int pivot = b[0];
	for (int i = 1; i < b.size(); i++)
		if (b[i] > pivot)
			mayores.push_back(b[i]);
		else
			menores.push_back(b[i]);
	ordenarVector(menores);
	ordenarVector(mayores);

	int j = 0;
	for (int &elem : menores)
		b[j++] = elem;

	b[j++] = pivot;

	for (int &elem : mayores)
		b[j++] = elem;
}
*/


void print_vector(std::vector<int> &v) {
	for(int i : v) {
		std::cout << i << ", ";
	}
	std::cout << std::endl;
}


// como no quiero hacer copias de vectores, paso los indices en la funcion, y ordeno el vector entre los indices low y high
void __ordenarVector(std::vector<int> &b, int low, int high)
{
	// caso base, si el indice inicial (low) es igual al final (high), el "vector" a ordenar es de 1 elemento, ya esta ordenado
	if(low == high){
		return;
	}

	// elijo un pivot ( el  primero)
	int pivot = b[low];
	// n va a medir cuantas veces muevo un numero a la izq
	// del pivot, entonces tambien mide la posición del pivot
	int n = low;

	int i;
	int t;

	// recorro el vector entre low y high
	for(int i = low; i < high; i++) {
		// en cada iteracion, comparo el vector en i con el pivot
		t = b[i];
		if(t < pivot) {
			// si es menor al pivot, lo borro y lo agrego al principio
			// es decir, lo muevo al principio (low)
			b.erase(b.begin() + i);
			b.insert(b.begin() + low, t);
			// si muevo al principio, el pivote se mueve uno a la derecha
			n++;
		}
	}


	// ahora tengo (menores, pivot, mayores)
	// donde menores son valores menores a pivot, y mayores mayores a pivot
	// ordeno menores y ordeno mayores
	__ordenarVector(b, low, n);
	__ordenarVector(b, n + 1, high);
}

// TODO esta implementacion sigue sin ser optima pues erase e insert son  ineficientes
// se recomienda al lector modificarla para usar std::swap() (buscar en la referencia) para ordenar de manera más eficiente

// una interfaz mas linda, asi puedo ordenar todo sin especificar que ordeno desde 0 y b.size(), 
void ordenarVector(std::vector<int> &b) {
	__ordenarVector(b, 0, b.size());
}

void ej_11() {
	std::vector<int> v1 = {5, 1, 7, 2, 8, 9, 3, 4, 6, 0};
	print_vector(v1);
	ordenarVector(v1);
	print_vector(v1);

	std::vector<int> v2 = {5, 1, 7, 2, 8, 9, 3, 4, 6, 0, 12908, 3, 38, 2, 19, 398, 1093, 39, 10, 39, 9, 9, 9, 0, 1, 1, -20139, -3, 4};
	print_vector(v2);
	ordenarVector(v2);
	print_vector(v2);
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
	return 0;
}
