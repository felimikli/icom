#include "../icom_helpers.h"

class Componente{
	string nombre;
//Defino bloque como cualquier cosa que tiene entradas
	//Metodos	
	public:
	virtual float out() = 0;
	virtual 
	
	protected:
		vector<Componentes> entradas; //Tiene un puntero a los bloques a donde buscar las entradas
}


class Circuito : public Componente{ //Segun en nivel de abstraccion es un componente o un circuito
	Vector<Componente> salidas; //por cada bloque en la salida, le va piediendo las salida a cada uno
	
	public:
		Circuito(Vector<Componente> salidas){
			this->salidas = salidas;
		}
		float out() override{
			for(auto salida: salidas){
				salida.output();
			}
		}
}


class Reference : public Componente{
	float ref;

	public:
		Siganl_gen(float gen){
			this->ref = ref;
		}
		float out() override{
			return ref;
		}
}


class Sumados : public Componente{
	public: 
		Sumados(Vector<Componente> entradas){
			this->entradas = entradas;			
		}
		float out() override{
			sum = 0;
			for(auto e:Wqntrada:entradas){
				sum += entrada.out();
			}
		}
	private:
		float sum;

}
