#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdint>
#include <cmath>
#include <cassert>

using namespace std;

using Pixel = uint8_t; 
using Image = vector<vector<Pixel>>;

// lee y retorna la imagen que se encuentra almacenada en el archivo fileName.
// dentro del archivo, la imagen se encuentra organizada como
// ancho, alto
// pixel0, pixel1, pixel2, ...
Image readImage(const string &fileName) 
{
    Image img;
    ifstream in(fileName);
    if(in) {
        size_t w, h;
        in >> w >> h;
        img.resize(h);
        for(size_t i = 0; i < h; ++i) {
            img[i].resize(w);
            for(size_t j = 0; j < w; ++j) {
                int val;
                in >> val;
                img[i][j] = val;
            }
        }

    }
    return img;
}

size_t limit(size_t val, size_t lim) {
    return val < lim ? val : lim-1;
}

// Funci0n que debe retornar un vector de SIZE/2 pixeles,(donde SIZE el el ancho/alto
// de la imagen) que corresponden a la secuencia de valores obtenidos radialmente desde el
// centro de la imagen en la direccion especificada por el angulo azimuth expresado en grados
vector<Pixel> getRadial(const Image &img, float azimuth)
{
    size_t sz = img.size() / 2;
    vector<Pixel> ret(sz);
    float azimuthRad = 2 * M_PI * azimuth/360;
    float deltaRX = cos(azimuthRad);
    float deltaRY = sin(azimuthRad);
    for(size_t i = 0; i < sz; ++i) {
        size_t x_idx = limit(sz + i * deltaRX, img[0].size());
        size_t y_idx = limit(sz + i * deltaRY, img.size());
        ret[i] = img[y_idx][x_idx];
    }
    return ret;

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