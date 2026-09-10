#include <iostream>
#include <vector>

class Contenedor {
	public:
		Contenedor(char c1, char c2) {
			caracteres.push_back(c1);
			caracteres.push_back(c2);
		} //TODO

		bool esIgual()
		{
			return (caracteres.at(0)==caracteres.at(1));
		} 

		void fijarse()
		{
			std::cout << "Los caracteres son: " << (esIgual() ? "IGUALES" : "DISTINTOS") << std::endl;
		}	

	private:
		std::vector<char> caracteres; 

};

int main(){
	char c1, c2;
	std::cout << "ingresar dos chars: "  << std::endl;
	std::cin >> c1 >> c2;
	Contenedor c(c1, c2);

	c.fijarse();

	return 0;
}
