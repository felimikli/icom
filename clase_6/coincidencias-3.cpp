#include <iostream>
#include <vector>
#include <string>


class Contenedor {
	public:
		Contenedor() 
		
		{
			std::string c_aux;
			
			while (true)
			{
				std::cout << "Ingrese un string de 8 caracteres: ";
				std::cin >> c_aux;
				if (c_aux.length()==8)
				{
					cartas.push_back(c_aux);
					break;
				}
				else
					std::cout << "Dije 8 caracteres!" << std::endl;
			}		
	
			while (true)
			{
				std::cout << "Ingrese otro string de 8 caracteres: ";
				std::cin >> c_aux;
				if (c_aux.length()==8)
				{
					cartas.push_back(c_aux);
					break;
				}
				else
					std::cout << "Dije 8 caracteres!" << std::endl;
			}
		}
		
		//funcion que se fija si al menos un caracter de cada una de las 2 cartas coincide con al menos un caracter de la otra. Si existe una coincidencia, evuelve true, sino false.
		bool coincidencia(){
			for(char c : cartas.at(0)) {
				if(cartas.at(1).find(c) != std::string::npos) {
					return true;
				}
			}
			return false;
		} //TODO

		void fijarse()
		{
			std::cout << "Las cartas coinciden en algun caracter? " << (coincidencia() ? "SI" : "NO") << std::endl;
		}	

	private:
		std::vector<std::string> cartas; 

};

int main(){
	Contenedor c;
	c.fijarse();

	return 0;
}
