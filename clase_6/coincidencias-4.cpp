#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class Mazo
{
	public:
		// Construye una instancia de Mazo leyendo las 'cartas' a partir la
		// informacion leida en el archivo 'mazo.txt'.
		// El archivo cuenta con un string por renglon, con los simbolos de la
		// carta
		Mazo(const std::string &fname) {
			std::ifstream mazo(fname);
			std::string carta;
			cartas.push_back("");
			while(std::getline(mazo, carta)) {
				cartas.push_back(carta);
			}
		}// TODO

		//Funcion que imprime el mazo
		void print() {
			for(std::string carta : cartas) {
				for (char ch : carta) {
					std::cout << ch;
				}
				std::cout << std::endl;
			}
		}//TODO

	private:
		// representacion de todas las cartas
		std::vector<std::string> cartas;

};

int main()
{
	Mazo m("mazo.txt");
	m.print();

	return 0;
}
