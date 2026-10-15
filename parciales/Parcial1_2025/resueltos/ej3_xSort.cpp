#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <stdlib.h>

using namespace std;

// Cantidades posibles de bits para tomar como dígitos individuales (Si le resulta confuso pensarlo en cantidad de bits, tenga en cuenta que también puede pensarse como un tipo de base: T equivale a base 4, F a base 16, E a base 256 y S equivale a base 65536)
enum digitPartitionType {T=2, F=4, E=8, S=16};

// Cantidad de bits que definen un dígito individual
const digitPartitionType DIGIT_BITS = E; 

// Máscara utilizada para extraer el dígito menos significativo 
const unsigned int MASK = 0xFFFFFFFF >> (2*S - DIGIT_BITS);

// Cantidad de buckets necesarios para aplicar xSort (ejemplo: Si DIGIT_BITS == 16, entonces 2^16 = 65536 buckets)
const unsigned int NUM_BUCKETS = MASK + 1;


// Función para obtener el dígito de DIGIT_BITS bits que comienza en la posición 'shift' 
unsigned int getDigit(unsigned int num, unsigned int shift)
{
  return (num >> shift) & MASK;
}

// Implementación de xSort
void xSort(vector<unsigned int> & arr)
{
  
  for(unsigned int shift = 0; shift < 32; shift += DIGIT_BITS) {
    int buckets[NUM_BUCKETS] = {0};
    for(auto a: arr)
      buckets[getDigit(a,shift)]++;
    for(size_t i = 0; i < NUM_BUCKETS - 1; i++)
      buckets[i + 1] += buckets[i];
    vector<unsigned int> aux(arr.size());
    for(auto it = arr.rbegin(); it != arr.rend(); it++)
      aux[--buckets[getDigit(*it,shift)]] = *it;
    arr = aux;
  }  
}
// Función para imprimir el contenido de un vector (sólo para depuración)
void printVector(const vector<unsigned int> & arr) {
  for (unsigned int num : arr) {
    cout << num << " ";   
  }
  cout << endl;
}               

int funCmp(const void * a, const void * b) {
  return ( *(unsigned int*)a - *(unsigned int*)b );
} 

// Función principal
int main() {
  srand(time(0));
  
  for (unsigned int cantidadNumeros = 10; cantidadNumeros <= 1000000; cantidadNumeros *= 10) {  
    vector<unsigned int> arr, arr_std_sort, arr_qsort; 
    
    arr.resize(cantidadNumeros);
    
    // Se rellena con números aleatorios.
    for (unsigned int i = 0; i < cantidadNumeros; i++)
      arr.at(i) = rand();
      
    // Copia del vector para std::sort
    arr_std_sort = arr;  
    arr_qsort = arr;    
    
    // Medir el tiempo de xSort
    auto start_xSort = chrono::high_resolution_clock::now();
    xSort(arr);
    auto end_xSort = chrono::high_resolution_clock::now();
    auto duration_xSort = chrono::duration_cast<chrono::microseconds>(end_xSort - start_xSort);
      
    // Medir el tiempo de std::sort
    auto start_std_sort = chrono::high_resolution_clock::now();
    sort(arr_std_sort.begin(), arr_std_sort.end());
    auto end_std_sort = chrono::high_resolution_clock::now();
    auto duration_std_sort = chrono::duration_cast<chrono::microseconds>(end_std_sort - start_std_sort);

     // Medir el tiempo de std::sort
    auto start_qsort = chrono::high_resolution_clock::now();
    qsort(arr_qsort.data(), arr_qsort.size(), sizeof(unsigned int),funCmp);
    auto end_qsort = chrono::high_resolution_clock::now();
    auto duration_qsort = chrono::duration_cast<chrono::microseconds>(end_qsort - start_qsort);
      
    if(arr != arr_std_sort) {
      printVector(arr);
      printVector(arr_std_sort);  
      cout << "Error: Los vectores ordenados no coinciden!" << endl;
      return -1;
    } 
       
    cout << "Vector de cantidadNumeros = " << cantidadNumeros << endl;
    cout << "Tiempo de ejecución (xSort):     " << duration_xSort.count() << " microsegundos" << endl;
    cout << "Tiempo de ejecución (std::sort): " << duration_std_sort.count() << " microsegundos" << endl << endl;
    cout << "Tiempo de ejecución (qsort): " << duration_qsort.count() << " microsegundos" << endl << endl;

  }
  return 0;
}
