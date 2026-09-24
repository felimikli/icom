#include <iostream>
#include <vector>
#include <algorithm> // Para std::sort
#include <chrono>    // Para medir el tiempo
#include <ctime>     // Para la función time() semilla del rand()

// Implementación de un ordenamiento lento (O(N^2))
void bubbleSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Función auxiliar para generar un vector con números aleatorios
std::vector<int> generarVectorAleatorio(size_t tamanio) {
    std::vector<int> v(tamanio);

    for (size_t i = 0; i < tamanio; ++i) {
        v[i] = rand(); // Genera números aleatorios
    }
    return v;
}

int main() {
    srand(time(nullptr)); // Inicializa la semilla para rand()
    // Probamos con 10,000 elementos
    const size_t TAMANO = 10000; 
    
    std::cout << "Generando " << TAMANO << " numeros aleatorios...\n\n";
    std::vector<int> base = generarVectorAleatorio(TAMANO);

    // Creamos copias idénticas para que la comparación sea justa
    std::vector<int> copia1 = base;
    std::vector<int> copia2 = base;

    // --- PRUEBA 1: BUBBLE SORT ---
    std::cout << "Ejecutando Bubble Sort..." << std::endl;

    auto inicioBubble = std::chrono::high_resolution_clock::now();
    bubbleSort(copia1);
    auto finBubble = std::chrono::high_resolution_clock::now();
    // si necesito una precision mejor que microsegundos, puedo usar nanosegundos
    auto duracionBubble = std::chrono::duration_cast<std::chrono::microseconds>(finBubble - inicioBubble);

    // --- PRUEBA 2: STD::SORT (QUICKSORT/INTRO_SORT DE C++) ---
    std::cout << "Ejecutando std::sort..." << std::endl;
 
    auto inicioStd = std::chrono::high_resolution_clock::now();
    std::sort(copia2.begin(), copia2.end());
    auto finStd = std::chrono::high_resolution_clock::now();
    // si necesito una precision mejor que microsegundos, puedo usar nanosegundos
    auto duracionStd = std::chrono::duration_cast<std::chrono::microseconds>(finStd - inicioStd);

    // --- MOSTRAR RESULTADOS ---
    std::cout << "\n================ RESULTADOS ================\n";
    std::cout << "Bubble Sort tardo: " << duracionBubble.count() << " us)\n";
    std::cout << "std::sort tardo:   " << duracionStd.count() << " us)\n";
    std::cout << "============================================\n";

    return 0;
}
