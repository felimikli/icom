#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>

using namespace std;

const float EPSILON = 1.e-8;

struct Punto3D
{
    float x, y, z;
};

Punto3D operator-(const Punto3D &p1, const Punto3D &p2) {
    return Punto3D{p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}

Punto3D operator/(const Punto3D &p, float f) {
    return Punto3D{p.x / f, p.y / f, p.z / f};
}

Punto3D cross_product(const Punto3D &p1, const Punto3D &p2) {
    return Punto3D{
        p1.y * p2.z - p1.z * p2.y,
        p1.z * p2.x - p1.x * p2.z,
        p1.x * p2.y - p1.y * p2.x,
    };
}

float dot_product(const Punto3D &p1, const Punto3D &p2) {
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

bool operator==(const Punto3D &p1, const Punto3D &p2) {
    Punto3D diff = p1 - p2;
    return dot_product(diff, diff) < EPSILON;
}

ostream &operator<<(ostream &os, const Punto3D &p) {
    os << p.x << ' ' << p.y << ' ' << p.z;
    return os;
}

struct Facet
{
    // vector unitario normal al plano del triangulo y apuntando hacia afuera del objeto
    Punto3D facet_normal;

    // los 3 vertices en el orden dado por la regla de la mano derecha
    array<Punto3D,3> outer_loop;

    // Calcular el versor normal al triángulo outer_loop
    Punto3D normal(); // ToDo

    // retorna el menor valor de z de outer_loop
    float min_z(); // ToDo

    // retorna verdadero si los dos vertices que se le pasan pertenecen al Facet en el orden que se pasan
    bool es_lado(const Punto3D &v1, const Punto3D &v2); // ToDo
};

// operador que compara dos facet por coordenada z de sus vertices
// uso: si f1 y f2 son dos Facet, entonces (f1 < f2) es verdadero si
// el menor z del objeto f1  es menor que el menor z de f2
bool operator<(Facet f1, Facet f2)
{
    return f1.min_z() < f2.min_z();
}

struct STL
{
    // Carga el modelo desde el contenido del archivo
    // de nombre filename
    bool readFromFile(const string &filename); // ToDo

    // Escribe el modelo al archivo de nombre filename
    // respetando el formato STL ASCII
    bool writeToFile(const string &filename);  // ToDo

    // retorna verdadero si el facet normal de cada facet es consistente
    // con el que se calcula a partir de los vertices.
    bool consistencia_facet_normal(); // ToDo

    // chequea que todos los lados de un triangulo sean compartidos
    // por uno y solo uno de los otros triangulos
    bool consistencia_lados_compartidos(); // ToDo

    // retorna verdadero si todos los facets estan dentro del octante positivo
    // x>=0, y>=0 y z>=0
    bool octante_positivo(); // ToDo

    bool is_valid() {
        // si no tengo ningun facet en el contenedor, no es valido
        if( facets.empty() )
            return false;
        return consistencia_facet_normal() && consistencia_lados_compartidos() && octante_positivo();
    }

    // optimiza el modelo, ordenando los Facets de forma creciente en z
    void optimize(); // ToDo

    // escalea el modelo. sx es el factor de escala en x, etc.
    // si sx=sy=sz=1 entonces el modelo quedaria exactamente igual
    // hint: al escalear un modelo, los facet normal tambien van a cambiar
    void scale(float sx, float sy, float sz); // ToDo

    // retorna la cantidad de facets que tiene el modelo
    size_t getNumFacets(); // ToDo

    string nombre;
    vector<Facet> facets;
};

int main()
{
    STL stl;

    if( ! stl.readFromFile("block100.stl") ) {
        cout << "Error leyendo desde block100.stl\n";
        return 1;
    }

    cout << "NumFacets: " << stl.getNumFacets() << endl;

    if( ! stl.is_valid() ) {
        cout << "Formato de archivo incorrecto\n";
        return 2;
    }

    stl.optimize();
    stl.scale(0.5,0.5,0.5);

    if( ! stl.is_valid() ) {
        cout << "Formato de archivo incorrecto\n";
        return 2;
    }

    if( ! stl.writeToFile("block50.stl") ) {
        cout << "Error escribiendo a block50.stl\n";
        return 3;
    }

    cout << "done\n";

    return 0;
}

