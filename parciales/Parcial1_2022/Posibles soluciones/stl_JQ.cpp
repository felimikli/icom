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
        Punto3D lado1 = outer_loop.at(1) - outer_loop.at(0);
        Punto3D lado2 = outer_loop.at(2) - outer_loop.at(0);
        Punto3D cp = cross_product(lado1, lado2);
        return cp / sqrt(dot_product(cp, cp));

    } // ToDo

    // retorna el menor valor de z de outer_loop
    float min_z() const
    {
        vector<float> vec_z;
        vec_z.push_back(outer_loop.at(0).z);
        vec_z.push_back(outer_loop.at(1).z);
        vec_z.push_back(outer_loop.at(2).z);
        return *min_element(vec_z.begin(), vec_z.end());
    } // ToDo

    // retorna verdadero si los dos vertices que se le pasan pertenecen al Facet en el orden que se pasan
    bool es_lado(const Punto3D &v1, const Punto3D &v2)
    {
        return ((v1 == outer_loop.at(0) && v2 == outer_loop.at(1)) || (v1 == outer_loop.at(1) && v2 == outer_loop.at(2)) || (v1 == outer_loop.at(2) && v2 == outer_loop.at(0)));
    } // ToDo
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
        ifstream iFile("block100.stl");
        string s1, s2;
        Punto3D p;
        Facet f;

        if (iFile)
        {
            iFile >> s1;
            if (s1 != "solid")
                return false;
            iFile >> nombre;

            iFile >> s1;
            while (s1 == "facet")
            {
                iFile >> s1;
                // normal versor
                if (s1 != "normal")
                    return false;
                iFile >> f.facet_normal.x >> f.facet_normal.y >> f.facet_normal.z;
                // outer loop
                iFile >> s1 >> s2;
                if (!(s1 == "outer" && s2 == "loop"))
                    return false;
                for (int i = 0; i < 3; i++)
                {
                    iFile >> s1;
                    if (s1 != "vertex")
                        return false;
                    iFile >> p.x >> p.y >> p.z;
                    f.outer_loop.at(i) = p;
                }
                iFile >> s1 >> s2;
                if (!(s1 == "endloop" && s2 == "endfacet"))
                    return false;
                facets.push_back(f);
                iFile >> s1;
            }
            if (s1 != "endsolid")
                return false;
            return true;
        }
        return false;
    } // ToDo

    // Escribe el modelo al archivo de nombre filename
    // respetando el formato STL ASCII
    bool writeToFile(const string &filename)
    {
        ofstream oFile(filename);
        if (oFile)
        {
            oFile << "solid " << nombre << endl;
            for (Facet f : facets)
            {
                oFile << "\tfacet normal " << f.facet_normal << endl;
                oFile << "\t\touter loop" << endl;
                for (int i = 0; i < int(f.outer_loop.size()); i++)
                {
                    oFile << "\t\t\tvertex " << f.outer_loop.at(i) << endl;
                }
                oFile << "\t\tendloop" << endl;
                oFile << "\tendfacet" << endl;
            }
            oFile << "endsolid" << endl;
            return true;
        }
        return false;
    } // ToDo

    // retorna verdadero si el facet normal de cada facet es consistente
    // con el que se calcula a partir de los vertices.
    bool consistencia_facet_normal()
    {
        for (Facet f : facets)
        {
            if (f.facet_normal == f.normal())
                continue;
            else
                return false;
        }
        return true;
    } // ToDo

    // chequea que todos los lados de un triangulo sean compartidos
    // por uno y solo uno de los otros triangulos
    bool consistencia_lados_compartidos()
    {
        bool lado1, lado2, lado3;
        bool lado1_found, lado2_found, lado3_found;
        for (size_t i = 0; i < facets.size(); i++)
        {
            lado1_found = false;
            lado2_found = false;
            lado3_found = false;

            for (size_t j = 0; j < facets.size(); j++)
            {
                if (i == j)
                    continue;
                // chequeo si son lados en el sentido contrario
                lado1 = facets.at(j).es_lado(facets.at(i).outer_loop.at(2), facets.at(i).outer_loop.at(1));
                lado2 = facets.at(j).es_lado(facets.at(i).outer_loop.at(1), facets.at(i).outer_loop.at(0));
                lado3 = facets.at(j).es_lado(facets.at(i).outer_loop.at(0), facets.at(i).outer_loop.at(2));
                if (lado1)
                {
                    if (!lado1_found)
                        lado1_found = true;
                    else
                        return false;
                }
                if (lado2)
                {
                    if (!lado2_found)
                        lado2_found = true;
                    else
                        return false;
                }
                if (lado3)
                {
                    if (!lado3_found)
                        lado3_found = true;
                    else
                        return false;
                }
            }
            if (!(lado1_found && lado2_found && lado3_found))
                return false;
        }
        return true;

    } // ToDo

    // retorna verdadero si todos los facets estan dentro del octante positivo
    // x>=0, y>=0 y z>=0
    bool octante_positivo()
    {
        for (Facet f : facets)
        {
            for (int i = 0; i < int(f.outer_loop.size()); i++)
            {
                if ((f.outer_loop.at(i).x < 0) || (f.outer_loop.at(i).y < 0) || (f.outer_loop.at(i).z < 0))
                    return false;
            }
        }
        return true;
    } // ToDo

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
    } // ToDo

    // escalea el modelo. sx es el factor de escala en x, etc.
    // si sx=sy=sz=1 entonces el modelo quedaria exactamente igual
    // hint: al escalear un modelo, los facet normal tambien van a cambiar
    void scale(float sx, float sy, float sz)
    {
        for (int i = 0; i < int(facets.size()); i++)
        {
            for (int j = 0; j < int(facets.at(i).outer_loop.size()); j++)
            {
                facets.at(i).outer_loop.at(j).x *= sx;
                facets.at(i).outer_loop.at(j).y *= sy;
                facets.at(i).outer_loop.at(j).z *= sz;
            }
            facets.at(i).facet_normal = facets.at(i).normal();
        }
    } // ToDo

    // retorna la cantidad de facets que tiene el modelo
    size_t getNumFacets()
    {
        return facets.size();
    } // ToDo

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
