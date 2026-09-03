#include <iostream>
#include <vector>
#include <cmath>

///////////////////
// EJERICICIO 01 //
///////////////////

double dist(double x, double y) {
	return std::sqrt(x*x + y*y);
}
void ej_1() {
	std::srand(time(0));
	int n = 10000000, n1 = 0;
	double x, y;
	
	for(int i = 0; i < n; i++) {
		x = (((double)rand()*2)/ RAND_MAX) - 1;
		y = (((double)rand()*2)/ RAND_MAX) - 1;
		if(dist(x, y) <= 1) n1++;
	}
	double pi = 4 * ((double)n1/n);
	std::cout << "PI: " << pi << '\n';
}

///////////////////
// EJERICICIO 02 //
///////////////////

enum Direction {
	L, R, D, U, LU, RU, LD, RD, NONE, NUM_DIRS
};

struct Entity {
	int x, y;
	int pasos_actuales = 0;
	int pasos_intermedios;
	void set_pos(int px, int py) {
		x = px;
		y = py;
	}
	void move(Direction d) {
		pasos_actuales++;
		if(pasos_actuales == pasos_intermedios) {
			pasos_actuales = 0;
			print();
		}
		switch(d) {
			case L: x--; break;
			case R: x++; break;
			case D: y--; break;
			case U: y++; break;
			case LU: x--; y++; break;
			case RU: x++; y++; break;
			case LD: x--; y--; break;
			case RD: x++; y--; break;
			case NONE: break;
			default: break;
		}
	}
	double dist(int px, int py) {
		return std::sqrt((x-px)*(x-px) + (y-py)*(y-py));
	}
	double experimento(int N){
		for(int i = 0; i < N; i++) {
			move( (Direction) (rand() % NUM_DIRS) );
		}
		return dist(0, 0);
	}
	double experimentos(int N, int M){
		double dist_sum = 0;
		for(int n = 0; n < M; n++) {
			x = 0;
			y = 0;
			experimento(N);
			dist_sum += dist(0, 0);
		}
		return (dist_sum / M);
	}
	void print() {
		std::cout << "X: " << x << "  Y: " << y << "  Dist.: " << dist(0, 0) << '\n';
	}
};

void ej_2() {
	std::srand(time(0));
	
	int N = 1000, M = 100;

	Entity e = {
		.x = 0,
		.y = 0,
		.pasos_intermedios = 10000000,
	};

	std::cout << "N = " << N << " M = " << M << '\n';
	std::cout << "Experimento(N): " << e.experimento(N) << '\n';
	std::cout << "Experimentos(M, N): " << e.experimentos(N, M) << '\n';

	std::vector<double> distancias;
	for(int i = 1; i <= 100; i++) {
		distancias.push_back(e.experimentos(1000 * i, M));
	}
	int k = 1;
	for(double d : distancias) {
		std::cout << "N = " << k*1000 << ", DIST = " << d << '\n';
		k++;
	}
}

///////////////////
// EJERICICIO 03 //
///////////////////
void ej_3() {
	std::srand(time(0));
	double t, h;
	int N = 10000000;
	double A = 0;
	for(int i = 0; i < N; i++) {
		h = ((double)rand()) / RAND_MAX;
		t = (double)rand();
		if(sin(t) > h) {
			A++;
		}
	}
	std::cout << "A = " << A << ", PI = " <<  N / A << '\n';
}

///////////////////
// EJERICICIO 04 //
///////////////////
void ej_4() {
	int nc = 0, nw = 0, nl = 0;
	char c;

	do {
		c = std::cin.get();
		nc++;
		switch(c) {
			case '\n':
				nw++; nl++;
				break;
			case '\t':
				nw++;
				break;
			case ' ':
				nw++;
				break;
			default: break;
		}
	} while(c != EOF);
	std::cout << "nc, nw, nl\n" << nc << " " << nw << " " << nl << '\n';
}

///////////////////
// EJERICICIO 05 //
///////////////////
void ej_5() {
	char c;
	do {
		c = std::cin.get();
		if(c >= 'a' && c <= 'z') {
			std::cout.put(c + ('A' - 'a'));
		}
	} while(c != EOF);
}

///////////////////
// EJERICICIO 06 //
///////////////////
void ej_6() {
	char c;
	int depth = 0;
	do {
		c = std::cin.get();
		switch(c) {
			case '(':
				depth++;
				break;
			case ')':
				if(!depth) std::cout.put(c);
				depth = std::max(0, depth - 1);
				break;
			default:
				if(!depth)
					std::cout.put(c);
		}

	} while(c != EOF);
}

///////////////////
// EJERICICIO 07 //
///////////////////


//funcion que recibe 2 char por copia y devuelve un bool indicando si los char recibidos son iguales (true) o no (false)
// TODO : Resolver esta funcion de 3 formas distintas
bool esIgual(char c1, char c2) {
	return c1 == c2;
}

bool esIgual2(char c1, char c2) {
	return c1 - c2 == 0;
}

bool esIgual3(char c1, char c2) {
	bool res;
	if(c1 == c2) {
		res = true;
	} else {
		res = false;
	}
	return res;
}

//funcion que recibe 2 char por copia, y, usando la funcion esIgual(char, char), imprime en pantalla si los caracteres son iguales o distintos. La funcion no devuelve nada (void)
void fijarse(char c1, char c2)
{
	std::cout << "Los caracteres son: " << (esIgual(c1,c2) ? "IGUALES" : "DISTINTOS") << std::endl;
}


void ej_7() {
	
	char caracter_1,caracter_2;
	
	std::cout << "Ingrese un caracter: ";
	std::cin >> caracter_1;
	
	std::cout << std::endl << "Ingrese otro caracter: ";
	std::cin >> caracter_2;
	
	fijarse(caracter_1, caracter_2);	
}

int main() {
	// ej_1();
	// ej_2();
	// ej_3();
	// ej_4();
	// ej_5();
	// ej_6();
	// ej_7();
	return 0;
}
