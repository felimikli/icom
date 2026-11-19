// Practica 12 - Ejercicio 3: Islas de grafeno
//
// Esqueleto del programa. Implemente el metodo GrafenoAnalyzer::analyze
// (y los metodos auxiliares que crea necesarios).
// La imagen de prueba esta en el archivo islas_grafeno.img

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

class STM_image {
    public:
        // construye una imagen de width x height pixeles
        STM_image(unsigned int width_, unsigned int height_) {
            width = width_;
            height = height_;
            pixels.resize(width * height);
        }

        unsigned int getWidth() const { return width; }
        unsigned int getHeight() const { return height; }

        unsigned short getPixel(int i, int j) const {
            unsigned int pixelIndex = ij2index(i, j);
            return pixels[pixelIndex];
        }

        void setPixel(int i, int j, unsigned short value) {
            unsigned int pixelIndex = ij2index(i, j);
            pixels[pixelIndex] = value;
        }

    private:
        unsigned int ij2index(int i, int j) const {
            assert(i >= 0 && i < (int) height && j >= 0 && j < (int) width);
            unsigned int pixelIndex = i * width + j;
            assert(pixelIndex < pixels.size());
            return pixelIndex;
        }

        unsigned int width;
        unsigned int height;
        vector<unsigned short> pixels;
};

struct Punto2DDiscreto {
	Punto2DDiscreto(int x_, int y_){

		x = x_;
		y = y_;
	}
    int x, y;
};

struct IslaGrafeno {
    vector<Punto2DDiscreto> puntos;
};

class GrafenoAnalyzer {
    public:
        GrafenoAnalyzer(unsigned short threshold_) {
            threshold = threshold_;
        }

        vector<IslaGrafeno> analyze(STM_image img);

    private:
        // ...

        unsigned short threshold;
};

// Lee una imagen STM desde un archivo de texto con el formato:
//     width height
//     seguido de width*height valores de pixel (fila por fila)
STM_image stmLoadImage(const string &fname)
{
    ifstream ifile(fname);
    assert(ifile);

    unsigned int width, height;
    ifile >> width >> height;
    assert(ifile);

    STM_image img(width, height);
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            unsigned short pixel;
            ifile >> pixel;
            assert(ifile);
            img.setPixel(i, j, pixel);
        }
    }
    return img;
}

void make_isla(IslaGrafeno &isla, STM_image &img, int i, int j, int tre){
	

	if(i >= img.getWidth() || i < 0) return;
	if(j >= img.getHeight() || j < 0) return;

	if(img.getPixel(i,j) <  tre) return; 

	img.setPixel(i,j,0);
	Punto2DDiscreto punto(i,j);
	isla.puntos.push_back(punto);

	make_isla(isla, img, i+1,j,tre);
	make_isla(isla, img, i-1,j,tre);
	make_isla(isla, img, i,j+1,tre);
	make_isla(isla, img, i,j-1,tre);

	return;
} 

vector<IslaGrafeno> GrafenoAnalyzer::analyze(STM_image img)
{
    vector<IslaGrafeno> islas;
	
    int wi = img.getWidth();
    int he = img.getHeight();


    for(int j = 0; j < wi; j ++){
	for(int i = 0; i < he; i++){
		IslaGrafeno isla;
		if(img.getPixel(i,j) >= threshold){
			make_isla(isla, img,i,j, threshold);
			islas.push_back(isla);			
		}
	}
    }





    // ...

    return islas;
}

int main()
{
    STM_image img = stmLoadImage("islas_grafeno.img");
    GrafenoAnalyzer gfa(500);

    vector<IslaGrafeno> islas = gfa.analyze(img);

    cout << "cantidad de islas: " << islas.size() << endl;
    for (size_t i = 0; i < islas.size(); ++i)
        cout << "isla " << i << ": size: " << islas[i].puntos.size() << endl;

    return 0;
}
