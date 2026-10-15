#include <iostream>
#include <vector>

using namespace std;

struct Moneda {
	int denom;     // valor de la denominacion
	size_t cantidad;  // cantidad de monedas de esa denominacion
};

struct ATM {
	// Construye un cajero con el casete inicial de dinerpo
	// Las denominaciones llegan ordenadas en forma decreciente por valor.
	// TODO (0.20)
	ATM(const vector<Moneda> &casette) {
		this->casette = casette;
	}

	// descompone el monto dado en un conjunto de monedas intentando usar 
	// las denominaciones mas grandes posibles y las cantidades disponibles
	// de cada denominacion. En caso de no tener dinero suficiente, no
	// debería entregar dinero
	// TODO (0.80)
	vector<Moneda> descompone(int monto) {
		int resto = monto;
		vector<Moneda> retorno;
		// recorro el casette, ordenado por denominaciones de mayor a menor
		for(int i = 0; i < casette.size(); i++) {
			// para cada denominación, la cantidad a restar del resto
			// es lo maximo que se pueda (resto / casette.denom)
			// limitado por la cantidad disponible
			int cant = min((int) casette[i].cantidad, resto / casette[i].denom);
			if(cant > 0) {
				resto -= cant * casette[i].denom;
				retorno.push_back({casette[i].denom, cant});
			}
			if(resto == 0) {
				// si resto es 0, puedo retornar
				return retorno;
			}
		}
		return {};
	}

	vector<Moneda> casette;
};

void imprime(const vector<Moneda> &c)
{
	for(auto m : c) {
		cout << "$ " << m.denom << " #" << m.cantidad << endl;
	}
	cout << "\n";
}
int main()
{
	vector<Moneda> reserva = { {2000, 100}, {1000, 100}, {500, 100}, {200, 100}, {100, 100}, {50, 100}, {20, 100}, {10, 100}, {5, 100}, {2, 100}, {1, 100}};
	ATM mon(reserva);

	vector<Moneda> c1 = mon.descompone(300000);
	imprime(c1);
	c1 = mon.descompone(300000);
	imprime(c1);
	c1 = mon.descompone(52101);
	imprime(c1);
	c1 = mon.descompone(30000000);
	imprime(c1);
	c1 = mon.descompone(209148);
	imprime(c1);
	c1 = mon.descompone(1923811);
	imprime(c1);
	c1 = mon.descompone(22);
	imprime(c1);
	c1 = mon.descompone(99999999);
	imprime(c1);

	return 0;
}
