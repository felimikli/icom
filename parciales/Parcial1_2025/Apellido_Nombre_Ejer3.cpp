#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std;

// Cantidades posibles de bits para tomar como dígitos individuales (Si le resulta confuso pensarlo en cantidad de bits, tenga en cuenta que también puede pensarse como un tipo de base: T equivale a base 4, F a base 16, E a base 256 y S equivale a base 65536)
enum digitPartitionType {T=2, F=4, E=8, S=16};

// Cantidad de bits que definen un dígito individual
const digitPartitionType DIGIT_BITS = S; 

// Máscara utilizada para extraer el dígito menos significativo 
const unsigned int MASK = 0xFFFFFFFF >> (2*S - DIGIT_BITS);

// Cantidad de buckets necesarios para aplicar xSort (ejemplo: Si DIGIT_BITS == 16, entonces 2^16 = 65536 buckets)
const unsigned int NUM_BUCKETS = MASK + 1;


// Función para obtener el dígito de DIGIT_BITS bits que comienza en la posición 'shift' 
unsigned int getDigit(unsigned int num, unsigned int shift) {
	return (num >> (shift*DIGIT_BITS)) & MASK;
} //TODO

// Implementación de xSort
void xSort(vector<unsigned int> & arr) {
	int base = exp2((int) DIGIT_BITS);
	int arr_s = arr.size();
	vector<unsigned int> aux(arr_s, 0);
	int max_digits = (sizeof(unsigned int) * 8) / DIGIT_BITS;
	for(int s = 0; s < max_digits; s++) {
		unsigned int bucket[base] = {0};
		for(auto a : arr) {
			/*
			cout << getDigit(a, s) << endl;
			cout << a << endl;
			cout << s << endl;
			cout << endl;
			*/
			bucket[getDigit(a, s)]++;
		}
		for(int i = 1; i < base; i++) {
			bucket[i] += bucket[i - 1];
		}
		for(int i = arr_s - 1; i >= 0; i--) {
			bucket[getDigit(arr[i], s)]--;
			aux[ bucket[ getDigit(arr[i], s) ] ] = arr[i];
		}
		arr = aux;
	}
} //TODO


// Función principal
int main() {
  srand(time(0));
  
  for (unsigned int cantidadNumeros = 10; cantidadNumeros <= 1000000; cantidadNumeros *= 10) {  
    vector<unsigned int> arr, arr_std_sort; 
    
    arr.resize(cantidadNumeros);
    
    // Se rellena con números aleatorios.
    for (unsigned int i = 0; i < cantidadNumeros; i++)
      arr.at(i) = rand();
      
    // Sólo para visualizar más fácilmente el funcionamiento correcto del programa
    if (cantidadNumeros == 10)
      for (unsigned int i = 0; i < cantidadNumeros; i++)
        arr.at(i) %= 100;
      
    // Copia del vector para std::sort
    arr_std_sort = arr;      
      
    // Sólo para visualizar más fácilmente el funcionamiento correcto del programa
    if (cantidadNumeros==10) {
      cout << "Testeo para confirmar que la función ordene correctamente:" << endl << endl;
      cout << "Vector original:             ";
      for (unsigned int num : arr) {
        cout << num << " ";
      }
      cout << endl;
    }
      
    // Medir el tiempo de xSort
    auto start_xSort = chrono::high_resolution_clock::now();
    xSort(arr);
    auto end_xSort = chrono::high_resolution_clock::now();
    auto duration_xSort = chrono::duration_cast<chrono::microseconds>(end_xSort - start_xSort);
      
    // Sólo para visualizar más fácilmente el funcionamiento correcto del programa
    if (cantidadNumeros == 10) {
      cout << "Vector ordenado (xSort):     ";
      for (unsigned int num : arr) {
        cout << num << " ";
      }
      cout << endl;
    }
      
    // Medir el tiempo de std::sort
    auto start_std_sort = chrono::high_resolution_clock::now();
    sort(arr_std_sort.begin(), arr_std_sort.end());
    auto end_std_sort = chrono::high_resolution_clock::now();
    auto duration_std_sort = chrono::duration_cast<chrono::microseconds>(end_std_sort - start_std_sort);
      
    // Sólo para visualizar más fácilmente el funcionamiento correcto del programa
    if (cantidadNumeros == 10) {
      cout << "Vector ordenado (std::sort): ";
      for (unsigned int num : arr_std_sort) {
        cout << num << " ";
      }
      cout << endl << endl;
    }
      
    cout << "coinciden? " << (arr == arr_std_sort) << endl;
    cout << "Vector de cantidadNumeros = " << cantidadNumeros << endl;
    cout << "Tiempo de ejecución (xSort):     " << duration_xSort.count() << " microsegundos" << endl;
    cout << "Tiempo de ejecución (std::sort): " << duration_std_sort.count() << " microsegundos" << endl << endl;
  }
  return 0;
}
