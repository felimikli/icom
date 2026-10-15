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
unsigned int getDigit(unsigned int num, unsigned int shift); //TODO

// Implementación de xSort
void xSort(vector<unsigned int> & arr); //TODO


// Función principal
int main() {
  srand(time(0));
  
  for (unsigned int cantidadNumeros = 10; cantidadNumeros <= 1000000; cantidadNumeros *= 10) {  
    vector<unsigned int> arr, arr_std_sort; 
    
    arr.resize(cantidadNumeros);
    
    // Se rellena con números aleatorios.
    for (unsigned int i = 0; i < cantidadNumeros; i++)
      arr.at(i) = rand();
      
    // Solo para visualizar más fácilmente el funcionamiento correcto del programa
    if (cantidadNumeros == 10)
      for (unsigned int i = 0; i < cantidadNumeros; i++)
        arr.at(i) %= 100;
      
    // Copia del vector para std::sort
    arr_std_sort = arr;      
      
    // Solo para visualizar más fácilmente el funcionamiento correcto del programa
    if (cantidadNumeros == 10) {
      cout << endl << "<Testeo para confirmar que la función ordene correctamente>" << endl;
      cout << "Vector original:             ";
      for (unsigned int num : arr) {
        cout << num << " ";
      }
      cout << endl;
    }
      
    // Medir el tiempo que tarda xSort
    auto start_xSort = chrono::high_resolution_clock::now();
    xSort(arr);
    auto end_xSort = chrono::high_resolution_clock::now();
    auto duration_xSort = chrono::duration_cast<chrono::microseconds>(end_xSort - start_xSort);
      
    // Solo para visualizar más fácilmente el funcionamiento correcto del programa
    if (cantidadNumeros == 10) {
      cout << "Vector ordenado (xSort):     ";
      for (unsigned int num : arr) {
        cout << num << " ";
      }
      cout << endl;
    }
      
    // Medir el tiempo que tarda std::sort
    auto start_std_sort = chrono::high_resolution_clock::now();
    sort(arr_std_sort.begin(), arr_std_sort.end());
    auto end_std_sort = chrono::high_resolution_clock::now();
    auto duration_std_sort = chrono::duration_cast<chrono::microseconds>(end_std_sort - start_std_sort);
      
    // Solo para visualizar más fácilmente el funcionamiento correcto del programa
    if (cantidadNumeros == 10) {
      cout << "Vector ordenado (std::sort): ";
      for (unsigned int num : arr_std_sort) {
        cout << num << " ";
      }
      cout << endl << endl;
    }
      
    cout << "<Vector de " << cantidadNumeros << " números>" << endl;
    cout << "Tiempo de ejecución (xSort):     " << duration_xSort.count() << " microsegundos" << endl;
    cout << "Tiempo de ejecución (std::sort): " << duration_std_sort.count() << " microsegundos" << endl << endl;
  }
  return 0;
}


unsigned int getDigit(unsigned int num, unsigned int shift) {
  return (num >> shift) & MASK;
}

void xSort(vector<unsigned int> & arr) {
  for (unsigned int shift = 0; shift < 8*sizeof(unsigned int); shift += DIGIT_BITS) {
    
    // Para contar ocurrencias de cada valor posible de un dígito
    vector<unsigned int> bucket(NUM_BUCKETS, 0);
    
    // Para guardar temporalmente los elementos ordenados por el dígito considerado
    vector<unsigned int> auxiliarr(arr.size());
    
    // Contar ocurrencias de cada valor posible (ejemplo: Si DIGIT_BITS == 16, entonces 2^16 = 65536 valores posibles para cada uno de los 2 dígitos)
    for (unsigned int num : arr) {
      bucket.at(getDigit(num, shift)) += 1;
    }
        
    // Calcular posiciones acumuladas para poder utilizar los valores guardados en cada bucket como índice simplemente restando 1 (para ver por qué, tenga en cuenta que el bucket de valor mas alto siempe tendrá un valor de cantidadNumeros)
    for (size_t i = 1; i < bucket.size(); i++) {
      bucket.at(i) += bucket.at(i - 1);
    }
        
    // Colocar los elementos en el nuevo orden, según el dígito considerado. Es necesario ir al revés, por cómo se usan los buckets como índices.
    for (int i = arr.size() - 1; i >= 0; i--) {
      unsigned int digit = getDigit(arr.at(i), shift);
      auxiliarr.at(bucket.at(digit) - 1) = arr.at(i);
      bucket.at(digit) -= 1; // Necesario para no pisar elementos
    }

    // Copiar vector de salida al original, quedando así ordenado por el dígito considerado
    arr = auxiliarr;
  }
  
  return;
}
