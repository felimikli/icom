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

Punto3D operator-(const Punto3D &p1, const Punto3D &p2)
{
    return Punto3D{p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}

Punto3D operator/(const Punto3D &p, float f)
{
    return Punto3D{p.x / f, p.y / f, p.z / f};
}

Punto3D cross_product(const Punto3D &p1, const Punto3D &p2)
{
    return Punto3D{
        p1.y * p2.z - p1.z * p2.y,
        p1.z * p2.x - p1.x * p2.z,
        p1.x * p2.y - p1.y * p2.x,
    };
}

float dot_product(const Punto3D &p1, const Punto3D &p2)
{
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

bool operator==(const Punto3D &p1, const Punto3D &p2)
{
    Punto3D diff = p1 - p2;
    return dot_product(diff, diff) < EPSILON;
}

ostream &operator<<(ostream &os, const Punto3D &p)
{
    os << p.x << ' ' << p.y << ' ' << p.z;
    return os;
}

struct Facet
{
    // vector unitario normal al plano del triangulo y apuntando hacia afuera del objeto
    Punto3D facet_normal;

    // los 3 vertices en el orden dado por la regla de la mano derecha
    array<Punto3D, 3> outer_loop;

    // Calcular el versor normal al triángulo outer_loop
    Punto3D normal()
    {
        Punto3D v1{outer_loop[1] - outer_loop[0]};
        Punto3D v2{outer_loop[2] - outer_loop[0]};
        Punto3D normal = cross_product(v1, v2);
        return normal / sqrt(dot_product(normal, normal));
    }

    // retorna el menor valor de z de outer_loop
    float min_z()
    {
        float res = outer_loop[0].z;
        res = res > outer_loop[1].z ? outer_loop[1].z : res;
        res = res > outer_loop[2].z ? outer_loop[2].z : res;
        return res;
    }

    // retorna verdadero si los dos vertices que se le pasan pertenecen al Facet en el orden que se pasan
    bool es_lado(const Punto3D &v1, const Punto3D &v2)
    {
        if (outer_loop[0] == v1 && outer_loop[1] == v2)
            return true;
        if (outer_loop[1] == v1 && outer_loop[2] == v2)
            return true;
        if (outer_loop[2] == v1 && outer_loop[0] == v2)
            return true;
        return false;
    }
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
    bool readFromFile(const string &filename)
    {
        ifstream file(filename);

        if (file.is_open())
        {
            string s;
            Facet facet;

            file >> s;
            if (s != "solid")
                return false;
            file >> nombre;

            file >> s;
            while (s == "facet")
            {
                file >> s;
                if (s != "normal")
                    return false;

                file >> facet.facet_normal.x;
                file >> facet.facet_normal.y;
                file >> facet.facet_normal.z;

                file >> s;
                if (s != "outer")
                    return false;
                file >> s;
                if (s != "loop")
                    return false;

                for (int i = 0; i < 3; i++)
                {
                    file >> s;
                    if (s != "vertex")
                        return false;
                    file >> facet.outer_loop[i].x;
                    file >> facet.outer_loop[i].y;
                    file >> facet.outer_loop[i].z;
                }

                facets.push_back(facet);

                file >> s;
                if (s != "endloop")
                    return false;
                file >> s;
                if (s != "endfacet")
                    return false;
                file >> s;
            }

            if (s != "endsolid")
                return false;
        }
        else
        {
            return false;
        }

        return true;
    }

    // Escribe el modelo al archivo de nombre filename
    // respetando el formato STL ASCII
    bool writeToFile(const string &filename)
    {
        ofstream file(filename);

        if (file.is_open())
        {
            file << "solid " << nombre << endl;

            for (const auto &facet : facets)
            {
                file << '\t' << "facet normal " << facet.facet_normal << endl;
                file << "\t\t"
                     << "outer loop" << endl;
                for (const auto &point : facet.outer_loop)
                    file << "\t\t\t"
                         << "vertex " << point << endl;
                file << "\t\t"
                     << "endloop" << endl;
                file << "\t"
                     << "endfacet" << endl;
            }
            file << "endsolid " << nombre << endl;
        }
        else
        {
            return false;
        }

        return true;
    }

    // retorna verdadero si el facet normal de cada facet es consistente
    // con el que se calcula a partir de los vertices.
    bool consistencia_facet_normal()
    {
        for (auto &facet : facets)
        {
            if (!(facet.facet_normal == facet.normal()))
                return false;
        }
        return true;
    }

    // chequea que todos los lados de un triangulo sean compartidos
    // por uno y solo uno de los otros triangulos
    bool consistencia_lados_compartidos()
    {
        int cnt0, cnt1, cnt2;

        for (int i = 0; i < getNumFacets(); i++)
        {
            cnt0 = 0;
            cnt1 = 0;
            cnt2 = 0;

            for (int j = 0; j < getNumFacets(); j++)
            {
                if (i == j)
                    continue;

                if (facets[j].es_lado(facets[i].outer_loop[1], facets[i].outer_loop[0]))
                    cnt0++;
                if (facets[j].es_lado(facets[i].outer_loop[2], facets[i].outer_loop[1]))
                    cnt1++;
                if (facets[j].es_lado(facets[i].outer_loop[0], facets[i].outer_loop[2]))
                    cnt2++;
            }
            if (cnt0 != 1 || cnt1 != 1 || cnt2 != 1)
                return false;
        }
        return true;
    }

    // retorna verdadero si todos los facets estan dentro del octante positivo
    // x>=0, y>=0 y z>=0
    bool octante_positivo()
    {
        for (const auto &facet : facets)
        {
            for (const auto &point : facet.outer_loop)
            {
                if (point.x < 0 || point.y < 0 || point.z < 0)
                    return false;
            }
        }
        return true;
    }

    bool is_valid()
    {
        // si no tengo ningun facet en el contenedor, no es valido
        if (facets.empty())
            return false;
        return consistencia_facet_normal() && consistencia_lados_compartidos() && octante_positivo();
    }

    // optimiza el modelo, ordenando los Facets de forma creciente en z
    void optimize()
    {
        sort(facets.begin(), facets.end());
    }

    // escalea el modelo. sx es el factor de escala en x, etc.
    // si sx=sy=sz=1 entonces el modelo quedaria exactamente igual
    // hint: al escalear un modelo, los facet normal tambien van a cambiar
    void scale(float sx, float sy, float sz)
    {
        for (auto &facet : facets)
        {
            for (auto &point : facet.outer_loop)
            {
                point.x *= sx;
                point.y *= sy;
                point.z *= sz;
            }
            facet.facet_normal = facet.normal();
        }
    }

    // retorna la cantidad de facets que tiene el modelo
    size_t getNumFacets()
    {
        return facets.size();
    }

    string nombre;
    vector<Facet> facets;
};

int main()
{
    STL stl;

    if (!stl.readFromFile("block100.stl"))
    {
        cout << "Error leyendo desde block100.stl\n";
        return 1;
    }

    cout << "NumFacets: " << stl.getNumFacets() << endl;

    if (!stl.is_valid())
    {
        cout << "Formato de archivo incorrecto\n";
        return 2;
    }

    stl.optimize();
    stl.scale(0.5, 0.5, 0.5);

    if (!stl.is_valid())
    {
        cout << "Formato de archivo incorrecto\n";
        return 2;
    }

    if (!stl.writeToFile("block50.stl"))
    {
        cout << "Error escribiendo a block50.stl\n";
        return 3;
    }

    cout << "done\n";

    return 0;
}
