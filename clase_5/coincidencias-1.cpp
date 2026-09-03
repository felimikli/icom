#include <iostream>
#include <vector>

using namespace std;

//funcion que recibe 1 vector<char> por referencia y devuelve un bool indicando si los char recibidos son iguales (true) o no (false)
bool esIgual(vector<char> &c); //TODO : Resolver esta funcion de 3 formas distintas

//funcion que recibe 1 vector<char> por copia, y, usando la funcion esIgual(vector<char> &), imprime en pantalla si los caracteres son iguales o distintos. La funcion no devuelve nada (void)
void fijarse(vector<char> c); //TODO : Resolver esta funcion de 2 formas distintas

int main(){
	
	char c_aux;
	vector<char> caracteres;
	
	cout << "Ingrese un caracter: ";
	cin >> c_aux;
	caracteres.push_back(c_aux);	
	
	cout << endl << "Ingrese otro caracter: ";
	cin >> c_aux;
	caracteres.push_back(c_aux);

	fijarse(caracteres);
	

	return 0;

}
