#include "../icom_helpers.h"

//EJERCICIO 1
/*1. Se desea representar un polígono con una interfaz simple para poder conocer algunas propiedades del
mismo. La representación e interfaz deseada es la siguiente. Se solicita completar la implementación del
UDT.
Evalúe la necesidad de implementar un constructor de copia, uno de asignación y un destructor. En el caso
de llegar a la conclusión de que hacen falta, impleméntelos.
*/

struct Punto2D {
	double X;
	double Y;
};


class Poligono {
	public:
		// construye un poligono cerrado con los vertices dados
		Poligono(const vector<Punto2D> &vertices){
			this->vertices = vertices;	
		}
		// retorna el perimetro del poligono
		double perimetro() const{
			int len = vertices.size();
			float per = 0;

			for(int i = 1; i < len; len ++){
				per += sqrt( (vertices[i].X - vertices[i-1].X)*(vertices[i].X - vertices[i-1].X) + (vertices[i].Y - vertices[i-1].Y)*(vertices[i].Y - vertices[i-1].Y));
			}
			if (len > 1){
				per += sqrt( (vertices[len].X - vertices[0].X)*(vertices[len].X - vertices[0].X) + (vertices[len].Y - vertices[0].Y)*(vertices[len].Y - vertices[0].Y));

			}
			return per;
		}
		// retorna el area del poligono
		double area() const{
			int n = vertices.size();
			float ar = 0;

			for(int i = 0; i < n; i ++){
				int next = (i+1) % n;
				//(yi + yi+1) * (xi - xi+1)
				ar +=( (vertices[i].Y + vertices[i+1].Y) * (vertices[i].X - vertices[i+1].X));
			}
			return 0.5*ar;

		}
	private:
		vector<Punto2D> vertices;
};

int main(void){
	return 0;
}
