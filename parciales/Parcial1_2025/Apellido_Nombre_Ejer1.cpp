#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdint>
#include <cmath>

using namespace std;

using Pixel = uint8_t; 
using Image = vector<vector<Pixel>>;

// lee y retorna la imagen que se encuentra almacenada en el archivo fileName.
// dentro del archivo, la imagen se encuentra organizada como
// ancho, alto
// pixel0, pixel1, pixel2, ...
Image readImage(const string &fileName) 
{
	// TODO
	int cols, rows;
	Image im;
	ifstream f(fileName);
	f >> cols >> rows;
	for(int i = 0; i < rows; i++) {
		vector<Pixel> row;
		for(int j = 0; j < cols; j++) {
			int p;
			f >> p;
			row.push_back(Pixel(p));
		}
		im.push_back(row);
	}
	return im;
}

// Funci0n que debe retornar un vector de SIZE/2 pixeles,(donde SIZE el el ancho/alto
// de la imagen) que corresponden a la secuencia de valores obtenidos radialmente desde el
// centro de la imagen en la direccion especificada por el angulo azimuth expresado en grados
vector<Pixel> getRadial(const Image &img, float azimuth)
{
    // TODO
	float az = M_PI * azimuth/180;
	float cos_ = cos(az);
	float sin_ = sin(az);
	vector<Pixel> line;
	// asumo cuadrada
	int size = img.size();
	int x_c = size/2;
	int y_c = size/2;
	int x, y;
	for(int i = 0; i < size/2; i++) {
		x = x_c + i * cos_;
		y = y_c - i * sin_;
		line.push_back(img[y][x]);
	}
	return line;
}

void printRadial(const vector<Pixel> &line) 
{
    for(auto a: line)
        cout << hex << int(a) << ' ';
    cout << '\n';
}


int main()
{
    Image img = readImage("image.dat");

    for(auto az = 0.0; az < 360.0; ++az){
        vector<Pixel> radial = getRadial(img, az);
        printRadial(radial);
    }
    return 0;
}
