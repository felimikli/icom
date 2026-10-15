// ICOM
// 1-Inicial
// 1.1-Representación de Números
// Sistemas Numéricos
// Decimal: se expresa en base 10. 25410=2×102+5×101+4×100
// Binario: se expresa en base 2. 25410=128+64+32+16+8+4+2+0=1×27+1×26+1×25+1×24+1×23+1×22+1×21+0×20=111111102 
// Hexagesimal: se expresa en base 16 con A = 10, B = 11, C = 12, D = 13, E = 14, F = 15. 25410=15×161+14×160=F×161+E×160=FE16 
// Para una base b: 25410=anbn+…+a0b0=ana0b
// an es la parte entera de la división 25410/bn. an-1 es la parte entera de la división (25410-anbn)/bn-1.
// cout<<hex<<a: devuelve la representación hexadecimal del valor de la variable a
// cout<<dec<<a: devuelve la representación decimal del valor de la variable a
// Números binarios negativos
// Existen varias opciones para negar un número negativo:
// Magnitud con signo: el bit de más a la izquierda se utiliza como signo, 0 es positivo y 1 es
// negativo, el resto de los bits representan el valor absoluto del número.
// Complemento a 1: el bit de más a la izquierda es el signo, 0 es positivo y 1 es negativo, para
// negar un número se reemplaza cada 1 por 0 y cada 0 por 1.
// Complemento a 2: ídem con el bit de signo, para negar un número se reemplaza cada 1 por 0
// y cada 0 por 1 (como en complemento a 1) y luego se le suma 1 al resultado.
// Excess 2m-1 (binary offset): para un número con m bits, el número se representa como la
// suma del mismo con 2m-1. Para un número de 8 bits, se le suma 128, ejemplo -3 → 128 + (-3) = 125.

// Los problemas: son que hay dos representaciones distintas para 0 y hay diferentes cantidades de números positivos y negativos.
// Aritmética binaria

// Operaciones entre bits



// Left shift “<<”: Desplaza la representación hacia la izquierda y agrega 0 a la derecha
// Right shift “>>”: Desplaza la representación hacia la derecha y agrega 0 a la izquierda

// Números en punto flotante
// Los números reales se los puede expresar como n=f×10e. Siendo f la fracción y e el exponente.
// El rango está determinado por la cantidad de dígitos del exponente. La precisión está determinada por la cantidad de dígitos en la fracción.

// Error de redondeo: Las operaciones con números de punto flotante pueden llevar a resultados que no se pueden expresar exactamente. El resultado es llevado al número representable más cercano.
// Forma de guardado del punto flotante según IEEE 754.

// Codigo ASCII







// 1.2-Secuencias de bits
// ¿Qué es?
// Una secuencia de bits es simplemente una disposición lineal de bits. Cada bit tiene una posición (índice), y su valor puede ser 0 o 1. Estas secuencias se utilizan para representar números, caracteres, colores, datos multimedia, y más en el sistema binario.
// Cada bit ocupa un único estado (encendido o apagado) en la memoria o hardware.
// Los bits se agrupan en bytes (1 byte = 8 bits).
// Las secuencias de bits más largas se organizan en palabras, dobles palabras, etc.
// Ejemplo de agrupación:
// 8 bits: 10101010 (1 byte)
// 16 bits: 1010101010101010 (2 bytes)
// 32 bits: 10101010101010101010101010101010 (4 bytes)
// Manipulación de secuencias de bits
// Las secuencias de bits se manipulan utilizando operaciones bit a bit (bitwise operations) y funciones especiales. Estas operaciones funcionan sobre números binarios directamente y son comunes en lenguajes como C y C++.
// AND (&): Compara dos bits, devuelve 1 si ambos bits son 1, de lo contrario 0: 1010 & 1100 = 1000
// OR (|): Compara dos bits, devuelve 1 si al menos uno de los bits es 1. 1010 | 1100 = 1110
// XOR (^): Compara dos bits, devuelve 1 si los bits son diferentes, de lo contrario 0. 1010 ^ 1100 = 0110
// NOT (~): Invierte cada bit (cambia 1 a 0 y 0 a 1). ~1010 = 11110101
// Desplazamiento a la izquierda (<<): Desplaza todos los bits a la izquierda, rellenando con 0 desde la derecha. 1010 << 2 = 101000
// Desplazamiento a la derecha (>>): Desplaza todos los bits a la derecha. Puede ser: 1010 >> 2 = 0010
// Lógico: Rellena con 0 desde la izquierda.
// Aritmético: Rellena con el bit de signo (para números con signo).
// Usos de las secuencias de bits
// Representar datos: Números, caracteres (ASCII), colores (RGB), etc.
// Máscara de bits: Filtrar o seleccionar partes específicas de datos.
// Compresión: Almacenar información más eficientemente.
// Criptografía: Operaciones binarias en algoritmos de cifrado.
// Protocolos de red: Para organizar y estructurar datos enviados/recibidos.
// Funciones comunes para manipulación de bits
// Verificar un bit especifico:
// bool isBitSet(int num, int pos) {
//     return (num & (1 << pos)) != 0;
// }
// Establecer un bit especifico:
// Corrección para manejar ambos valores (0 o 1):
// Para establecer un bit en una posición específica, asegurándote de que sea exactamente el valor deseado (0 o 1), necesitas una combinación de operaciones AND y OR. El enfoque correcto es:
// Apagar el bit en la posición deseada (usando una máscara con AND). 
// Encender el bit si el valor es 1 (usando OR).
// void setPixel(size_t x, size_t y, Color c) {
//     // Verificar si los índices están dentro de los límites
//     if (x >= filas || y >= colum) {
//         throw std::out_of_range("Index out of bounds");
//     }

//     // Determinar la columna y el desplazamiento
//     size_t aux = y / 32;        // Índice del uint32_t que contiene el bit
//     size_t bitOffset = y % 32;  // Posición del bit dentro de ese uint32_t

//     // Modificar el bit en la posición correspondiente
//     if (c == Color::ON) { // Activar el bit
//         im[x][aux] |= (1 << bitOffset);
//     } else { // Apagar el bit
//         im[x][aux] &= ~(1 << bitOffset);
//     }
// }
// También se puede hacer
// void setPixel(size_t x, size_t y, Color c){// TODO
//             size_t aux=y/32;
//             if(x >= filas ||y >= colum) { throw std::out_of_range("Index out of bounds"); }    //Me fijo si el indice esta dentro del rango

//             //Establecer un bit especifico:
//             im[x][aux]=(im[x][aux] & ~(1 <<(y%32))) | (c<< (y%32));
            
// 		}

// Limpiar un bit específico:
// int clearBit(int num, int pos) {
//     return num & ~(1 << pos);
// }
// Alternar un bit específico:
// int toggleBit(int num, int pos) {
//     return num ^ (1 << pos);
// }
// Contar el numero de bits en 1: Usando el algoritmo de Hamming Weight o __builtin_popcount (en GCC/Clang):
// int countSetBits(int num) {
//     return __builtin_popcount(num);
// }
// Invertir todos los bits
// int invertBits(int num) {
//     return ~num;
// }
// Buscar el primer bit
// int firstSetBit(int num) {
//     return __builtin_ffs(num); // Devuelve la posición del primer bit en 1.
// }
// Matriz doble puntero que guarda secuencias de bits
// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <cstdint>

// using namespace std;

// // Función para crear una matriz de punteros doble
// uint32_t** crearMatrizBits(int filas, const vector<int>& bitsPorFila) {
//     // Crear matriz de punteros
//     uint32_t** matriz = new uint32_t*[filas];

//     for (int i = 0; i < filas; ++i) {
//         // Calcular el número de columnas necesarias para esta fila
//         int columnas = ceil(bitsPorFila[i] / 32.0);
//         matriz[i] = new uint32_t[columnas]();

//         // Inicializar los valores a 0
//         for (int j = 0; j < columnas; ++j) {
//             matriz[i][j] = 0;
//         }
//     }

//     return matriz;
// }

// // Función para liberar la memoria de la matriz
// void liberarMatriz(uint32_t** matriz, int filas) {
//     for (int i = 0; i < filas; ++i) {
//         delete[] matriz[i];
//     }
//     delete[] matriz;
// }

// // Función para establecer un bit en la matriz
// void setBit(uint32_t** matriz, int fila, int bitIndex) {
//     int col = bitIndex / 32; // Determinar la columna
//     int offset = bitIndex % 32; // Determinar el bit dentro de la columna
//     matriz[fila][col] |= (1 << offset); // Establecer el bit
// }

// // Función para obtener un bit de la matriz
// bool getBit(uint32_t** matriz, int fila, int bitIndex) {
//     int col = bitIndex / 32;
//     int offset = bitIndex % 32;
//     return (matriz[fila][col] & (1 << offset)) != 0;
// }

// int main() {
//     int filas = 3; // Número de filas
//     vector<int> bitsPorFila = {50, 100, 70}; // Bits necesarios por fila

//     // Crear la matriz
//     uint32_t** matriz = crearMatrizBits(filas, bitsPorFila);

//     // Establecer algunos bits en la matriz
//     setBit(matriz, 0, 5);    // Fila 0, bit 5
//     setBit(matriz, 1, 40);   // Fila 1, bit 40
//     setBit(matriz, 2, 65);   // Fila 2, bit 65

//     // Mostrar los valores de algunos bits
//     cout << "Bit (0, 5): " << getBit(matriz, 0, 5) << endl;
//     cout << "Bit (1, 40): " << getBit(matriz, 1, 40) << endl;
//     cout << "Bit (2, 65): " << getBit(matriz, 2, 65) << endl;

//     // Liberar memoria
//     liberarMatriz(matriz, filas);

//     return 0;
// }

// 1.3-Variables
// Definiciones
// Set de instrucciones: operaciones básicas que puede hacer la computadora.
// Assembly language: establece una relación directa entre las sentencias del lenguaje y el set de instrucciones. Es de bajo nivel y no portable.
// Lenguaje de alto nivel: Permiten la manipulación de las entidades del problema sin involucrarse con los detalles de su implementación interna
// Variable: Relación entre un nombre simbólico, una porción de memoria y un tipo. Tienen asociado un bloque de memoria (dirección de comienzo y tamaño), además tienen un tipo que define la representación y las operaciones que pueden realizarse sobre ella.


// Enteros (Int, short y long)
// Resto=x%2
// Convertir otro tipo de variable en numero
// static_cast<int>( )
// Convertir texto a numero entero
// atoi(texto)
// Para identificar que un numero entero es en realidad binario 0b:
// int bin=0b111111
// uint32_t: guarda enteros de 32 bits sin signo, lo que significa que almacena valores entre 0 y 4294967295
// int32_t: es para enteros de 32 bits con signo, lo que significa que almacena valores entre -2147483648 y 2147483647. 
// Punto flotante (float y double)
// double es igual que el float pero puede guardar números más extensos.
// Convertir texto a numero float
// atof(texto)

// Booleano
// Solo tiene true y false.
// Char
// Recibe caracteres únicamente.
// Declaración:
// char c = 'a';
// Convertir número en char:
// static_cast<char>(numero)

// String
// Declaración: 
// string s="Esto es Lo primero";
// Es como un vector que guarda cada caracter:
// string s1 = "Hola Mundo"

// Operaciones útiles:
// Concatenación:
// string nombre_completo = nombre + ' ' + apellido;
// w+s
// Agregar s al final de w:
// w+=s
// Operaciones generales
// Para variables
 
  
// Para cout
// \n:lo siguiente se escribe una nueva línea.
// \t:tabulación
// \b: elimina el caracter que se encuentra justo antes del comando
// \r: agarra el texto que esta por delante y con ellos reemplaza los caracteres que est[an al principio


// De la librería math.h
// Raiz: sqrt(y)
// Potencia a la n: pow(y,n
// Tipos de datos UDT
// Tipos de datos definidos por el usuario (UDT): Son tipos de datos que el programador puede crear a partir de los tipos de datos básicos o primitivos. Estos tipos personalizados permiten estructurar y organizar la información de acuerdo a las necesidades específicas de la aplicación, mejorando la legibilidad, reutilización y modularidad del código. Por ejemplo, struct y class.
// struct Complejo {
//     double re, im;
//     void print() {
//         cout << "(" <<re << " + i " << im << ")\n";
//     }
//     double modulo() {
//         return sqrt(re*re+im*im);
//     }
//     Complejo operator+(Complejo a) {
//         Complejo result = { re + a.re, im + a.im};
//         return result;
//     }
// };
// Luego, en el main se define una variable c1 Complejo como:
// Complejo c1=(1.2,1.34);
// El operador es:
// Complejo c3=c1+c2;
// Se imprime con:
// C3.print();



// 2-Control de flujo
// Flujo de programa:
// main toma el control del programa y ejecuta las sentencias que contiene su cuerpo.
// La ejecución de una función es secuencial, pero pueden incluirse bloques condicionales, repetitivos (iteraciones) o llamados a funciones (inclusive a ella misma). 
// Llamar a una función es transferirle el control de ejecución. Cuando la función termina, el control vuelve a la sentencia posterior a la llamada original. 
// Una función termina cuando llega al final de su cuerpo, o alcanza una sentencia return
// Para cualquier estructura de control de flujo, en el caso de que el cuerpo posea una sola sentencia puede omitirse las { }.

// 2.1-Condicioneales
// If
// if( condición ) {
// accionT1;
// accionT2;
// } else {
// accionF1;
// accionF2;
// }
// Si la expresión de la condición termina en un valor numérico, este se tratará como verdadero si su valor es distinto de 0, y como falso si su valor es 0
// Algunas operaciones lógicas
// (X >> 3) & 1, verdadero si el 4 bit es 1
// X, verdadero si X es distinto de 0.
// (X & 1), si la expresión binaria de X termina en 1, xxxx1 & 1=00001, que es el numero 1, por lo que es distinto de 0, verdadero. Si termina en 0, , xxxx0 & 1=00000, dando 0 el resultado, por lo que es 0, falso.
// if((y<=largo && largo<=y+(largo*cos(t)))||(y+(largo*cos(t))<=0 && 0<=y)){
// 	cont2+=1;
// }
// Operador condicional
// cond ? expr1 : expr2;
// esIgual(c1,c2) ? "IGUALES" : "DISTINTOS")
// Otra forma de escribir el if
// if (y < z) // esto es equivalente a:
//     x = y; // x = (y < z) ? y : z;
// else
//     x = z;
// Switch
// Variación de if para casos múltiples:
// switch(expr) { // expr define el caso de entrada
//     case Caso1: // los casos son constantes
//         Accion1_1;
//         ...
//         break; // si no existiese, continuaría
//     case Caso2:
//         Accion2_1;
//         ...
//         break; // si no existiese, continuaría
//     ...
//     default: // puede no existir un default
//         AccionD_1;
//         ...
//         break;
// }
// switch(d) {
// 	case LEFT:  x--; break;
// 	case RIGHT: x++; break;
// 	case UP:    y++; break;
// 	case DOWN:  y--; break;
// 	case NONE:  break;
// 	default: break;  // si llega hasta acá debería disparar una excepcion
// }
// 2.2-Bucles
// While
// while(condición) {
// accion1;
// accion2;
// }
// Do-While
// Difiere con el while en que las acciones se ejecutan al menos una vez antes de evaluar la condición.
// do {
// accion1;
// accion2;
// } while( condición );
// For
// for(a; b; c ) {
// accion1;
// accion2;
// }
// La expresión a es la inicialización, y puede tener una, ninguna o varias sentencias separados por ‘,’ y solo se ejecuta una única vez antes de la iteración.
// La expresión b establece la condición de ejecución de las acciones de la iteración, se evalúa antes de ejecutar el siguiente ciclo.
// La expresión c es ejecutada al final de cada ciclo, antes de reevaluar la condición.
// Expresiones útiles:
// for(int i=0; i<n ; i++ ) {
// accion1;
// accion2;
// }
// For para secuencias
// Variante de for (range-for). Lo que hace es recorrer cada elemento de secuencias que naturalmente tienen un inicio y un fin, un rango. Sirve para vector char, int y también, para string (el string se consideraría como un vector)
// vector<int> v = { 5, 6, 9, 4, 6, 8 };
// for( int x : v ) { // Para cada x en v
// cout << x << '\n';
// }
// Ejemplo para strings:
// int main(){
// string s;
// for( char c : s ) {
// if( c == 'a' ){
// c = 'A';
// }
// }
// return 0;
// }


// 2.3-Otras sentencias
// Break
// Produce la salida inmediata del while, for, do-while ó switch en la línea en que se encuentra.
// while( true ) {
// double x;
// cin >> x;
// if( x < 0.0 ) /* si x es negativo */
// break; /* salgo del while */
// cout << sqrt(x) << "\n";
// }
// Continue
// Termina la iteración actual del while, for ó do-while en la línea en que se encuentra y vuelve al comienzo de la iteración.
// for( int i = 0; i < 20; ++i ) {
// if( i == 13 )
// continue; /* supersticioso yo? */
// cout << i << '\n';
// }
// Goto
// Produce un salto incondicional a una sentencia con una etiqueta que se encuentra en algún lugar de la misma función.
// for( int i = 0; i < 100; ++i ) {
//     for( int j = 0; j < 100; ++j ) {
//         if( i * j == i + j )
//         goto afuera;
//         cout << i << ' ' << j << '\n';
//     }
// }
// afuera:
// cout << "Salida de emergencia??\n";

// 2.4-Manejo de Errores
// Tipos de errores:
// Errores de compilación. Detectados por el compilador. A su vez hay distintos errores de compilación, como errores de sintaxis, errores de tipos, etc.
// Errores de link. Detectados por el linker al momento de producir un ejecutable, normalmente por falta de alguna definición o inclusión de objetos o bibliotecas.
// Errores de run-time. Errores detectados cuando el programa se está ejecutando:
// Errores detectados por la computadora, hardware o sistema operativo.
// Errores detectados por bibliotecas
// Errores de código del programador 
// Errores lógicos. Encontrados por el programador buscando resultados erróneos
// Es imposible eliminar todos los errores
// Para “resolver” los errores de compilación y de link, vamos a asumir que nuestros programas:
// Deberían producir resultados correctos para todas las entradas válidas (input data).
// Deberían dar mensajes de error razonables para todas las entradas inválidas.
// No necesitan preocuparse por errores de hardware.
// No necesitan preocuparse por errores del sistema operativo.
// Tienen permitido terminar su ejecución después de encontrar un error.

// Errores en run-time
// Resueltos los errores de compilación y de link, el código del programa debe detectar y manejar los errores.
// Si una función detecta un error, debe informarlo a la función que la llamó.
// Código de detección de errores en las funciones (por ejemplo de validez de argumentos) que deben ser reportados a quien llamó a la función.
// Código de “handling” de errores reportados por funciones llamadas.
// int area(int a, int b) { 
// if( a < 0 || b < 0 ) // checkeo
// return -1: // retorna error 
// return a * b;
// } 
// int f(int a, int b) {
//     int s = area(a - 3, b – 4);
//     if( s == -1 ) // checkeo
//         error("area: bad args\n");
//     return s;
// }
// Assert (aserción)
// Condición que se supone verdadera y que debería siempre cumplirse para poder seguir ejecutando un algoritmo. assert(condición)
// Si la condición se cumple, no tiene ningún efecto, pero se interrumpe el programa con un mensaje alusivo si no se cumple (Assertion Failed!).
// int main(){
//     cout << "Ingrese un número positivo ";
//     double v;
//     cin >> v;
//     assert(v >= 0);
//     cout << "la raiz cuadrada es: " << sqrt(v) << '\n';
//     return 0;
// }
// 3-Funciones
// 3.1-Funciones fabricadas
// Declaración: hay que indicar el nombre de la función, el tipo del valor retornado (void si no retorna nada) y la cantidad y tipo de los argumentos que deben ser suministrados al llamar a la función.
// int main();
// void exit(int a);
// double sqrt(double a);
// double pow(double a, double b);
// vector<int> fibonnacci(int b);
// (También, se puede retornar vectores o arrays?)
// Definición: se definen las acciones que ejecuta cuando la función se activa. Estas están en el cuerpo de la función.
// Argumentos: Los argumentos que recibe una función sirven para parametrizar su comportamiento (en general no resuelven un único problema, sino una familia de problemas).
// Es importante que en los argumentos se ingresen variables con el mismo tipo de variable definida en la declaración.
// Variables locales o automáticas
// Variables locales: las que están definidas dentro de una función
// Creadas automáticamente cada vez que la función es activada.
// Accesibles solo desde la función que las definió.
// El valor inicial es asignado cada vez que se ejecuta la función.
// Variables locales no inicializadas tienen valores no controlados.
// Los argumentos de una función son variables automáticas que se inicializan con los valores que se les dieron al llamarse la función.
// Valor de retorno
// Las funciones deben retornar un valor del tipo declarado de la función (excepto void que no retornar ningún valor).
// Puede haber múltiples sentencias return en una función.
// nt f1() { } // error
// void f2() { } // ok
// int f3() { return 1; } // ok
// void f4() { return 1; } // error
// int f5() { return; } // error
// void f6() { return; } // ok

// Métodos: F internas a UDT
// Métodos: son funciones internas a un UDT.
// Estas funciones tienen acceso a los atributos del objeto definido por la UDT, sobre el que se activó el método.
// struct Entity {
//     int x, y;
//     void move(Direction d) {
//         switch(d) {
//         case LEFT: x--; break;
//         case RIGHT: x++; break;
//         //...
//         }
//     }
//     //...
// }
// int main() {
//     Entity e1 = {0,0};
//     Entity e2 = {10,10};
//     e1.move(LEFT);
//     //...
//     e2.move(UP);
//     //...
//     return 0;
// }

// 3.2-Funciones predefinidas
// Srand()/rand()
// Funciones que generan números pseudo-aleatorios con algoritmo de congruencia lineal:
// xn+1=a xn+cmod m
// srand(seed): impone el x0. Determina la lógica de la aleatoriedad y define el primer valor.
// rand(): retorna el siguiente valor en la secuencia en el rango [0, RAND_MAX()]. Para que se vayan mostrar varios números aleatorios, se debe poner la función rand()en un bucle que va haciendo llamada a srand(seed) mostrando los valores en función de la lógica del mismo.
// Algo útil es usar la seed en el time(0) que entonces los números aleatorios están definidos por distintas secuencias a lo largo del tiempo, por lo que cambia constantemente haciéndolo mas aleatorio.
// Formas útiles:
// srand(time(0));
// for(int i = 0; i < 10; ++i)
//     cout << rand() << ' ';
// Numero aleatorio entre 0 y 50000
// rand() % 50001
// Rand max:

// Otros generadores aleatorios
// static std::random_device rd;
// static std::mt19937 gen(rd());
// Se ponen juntos
// static std::random_device rd: Crea un dispositivo generador de entropía, utilizado para inicializar números aleatorios. Es estático, por lo que solo se inicializa la primera vez que se llama a la función.
//   Es una clase en C++ que actúa como un generador de números aleatorios basado en el hardware del sistema (si es soportado).
//   Sirve como una fuente de entropía inicial para semillas que se pasan a otros generadores, como std::mt19937.
//   Cuando se llama a rd(), genera un número aleatorio entero sin signo.
//   Si el sistema no tiene soporte para un generador de entropía basado en hardware, se usa un generador pseudoaleatorio.
//   No tiene un rango fijo garantizado, pero típicamente genera valores grandes, cubriendo todo el rango de std::uint32_t.
// Proporciona una semilla aleatoria que va a ser usada después.

// static std::mt19937 gen(rd()): Inicializa un generador de números aleatorios (std::mt19937), basado en el dispositivo rd. También es estático para que no se reinicialice cada vez que se llame a la función.
// std::mt19937 es una implementación del algoritmo Mersenne Twister, un generador pseudoaleatorio de alta calidad que produce secuencias de números aleatorios reproducibles y uniformemente distribuidos.
// Es muy eficiente y genera números aleatorios con un período extremadamente grande 
// A diferencia de std::random_device, genera secuencias reproducibles si se inicializa con la misma semilla.
//   Cuando se inicializa como std::mt19937 gen(rd());, el generador gen utiliza el número generado por rd() como semilla.
//   Después de eso, gen() genera números aleatorios en el rango [0, 2³² - 1].

// Distribución uniforme de números aleatorios entre dos valores:
// std::uniform_real_distribution<> dis_factor(0.5, 1.5);
// double random_factor = dis_factor(gen);
// std::uniform_real_distribution<> dis_factor(0.5, 1.5);
// Define una distribución uniforme de números reales entre 0.5 y 1.5. Esto significa que cualquier valor dentro de este rango tiene la misma probabilidad de ser elegido.
// Se utiliza para generar números reales (decimales) de manera uniforme dentro de un rango específico.
// En este caso, el objeto dis_factor está configurado para generar números aleatorios en el rango [0.5, 1.5].
// Esto significa que cualquier valor generado por dis_factor estará entre 0.5 y 1.5 con la misma probabilidad.
//   0.5 es el valor mínimo (inclusive).
//   1.5 es el valor máximo (inclusive).
// Sintaxis:
// std::uniform_real_distribution<Tipo>(min, max);
// El Tipo es double por defecto si no se especifica
// double random_factor = dis_factor(gen);
// Genera un número aleatorio dentro de esta distribución usando el generador gen.
// El resultado es un factor aleatorio que modifica la probabilidad histórica.

// std::clamp(actual_prob, 0.0, 1.0);:
// Garantiza que la probabilidad ajustada esté en el rango válido [0.0, 1.0].
// Si actual_prob es menor que 0.0, se ajusta a 0.0. Si es mayor que 1.0, se ajusta a 1.0.
// Enumeración de una lista de valores (enum)
// enum Direction {    // enumeración de las posibles direcciones (la última es auxiliar)
//     LEFT, RIGHT, UP, DOWN, NONE, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN, NUM_DIRS
// };
// Funciones generales
// sizeof(a) da el tamaño en Bytes de la variable a
// &a: se accede a la dirección de memoria.
// hex: Cambia el formato de salida de cout al sistema hexadecimal, para que cualquier valor posterior sea mostrado en hexadecimal.
// (intptr_t) &c: Esto convierte la dirección de la variable c a un entero del tipo intptr_t, que es un tipo de entero capaz de almacenar una dirección de memoria. La conversión se realiza para mostrar la dirección como un número entero en lugar de una representación de puntero.
// toupper(): convierte a mayúsculas los caracteres

// 3.3-Dispositivos de I/O predefinidos
// Dispositivos de I/O: un programa tiene 3 dispositivos predefinidos por defecto:
// Entrada: teclado: El objeto cin está asociado al dispositivo standard de entrada.
// Salida: consola: El objeto cout está asociado al dispositivo standard de salida.
// Error: consola: El objeto cerr está asociado al dispositivo standard de errores.

// Redireccionamiento
// El sistema operativo provee de mecanismos de redireccionamiento:
// Dispositivos de entrada (<)
// Dispositivo de salida (>, >>)
// Dispositivo de errores (2>, 2>>)
// Lo que hace el redireccionamiento es redefinir la entrada, salida y error del programa a archivos y saltarse el por defecto. Ejemplo:
// Redirecciona la salida del programa al archivo “resultados.dat”
// $ ./prog > resultados.dat
// Redirecciona la entrada del programa desde archivo “datos.dat”
// $ ./prog < datos.dat
// Redirecciona entrada, salida y error
// $ ./prog < input.dat > output.dat 2> errores.dat

// cin.get(): hace que el programa lea desde la entrada estándar, ya sea el teclado o un archivo redirigido, y luego procese esos datos.
// cout.put(c): Esta línea escribe el carácter almacenado en c en la salida estándar (que puede ser la consola o un archivo)
// En el siguiente programa: se copia la entrada estándar (Que en este caso es algo ingresado al teclado) a c hasta que se llega a EOF (Endo f line) final de la línea. Mientras, se va imprimiendo en la salida estándar (consola en este caso) lo que está dentro de c. Es decir, se imprime todo lo que se extrae por medio de cin.get() a la consola.



// 3.4-Definir funciones en .h y .cpp para usarlo en un programa
// Se debe definir un archivo .h que diga:
// Si se llama prototipos.h:
// #ifndef PROTOTIPOS_H_INCLUDED
// #define PROTOTIPOS_H_INCLUDED

// void ImprimeVector(int Vector[],int NumElementos); //Nombre de la función solo

// #endif // PROTOTIPOS_H_INCLUDED
// Luego, un archive .cpp donde se guarden las definiciones de las funciones:
// misfuncs.cpp
// #include "icom_helpers.h"
// #include "prototipos.h"

// void IngreseDatosVector(int Vector[],int NumElementos){
//     int i;
//     for(i=0;i<NumElementos;i++){
//         cout<< "Ingrese valor "<< i+1 << " :"<<endl;
//         cin>>Vector[i];
//     }
// }
// Luego, el archive principal donde se van a usar las funciones. Se debe crear un proyecto y modificarlo en el mail. Después, se deben agregar al proyecto los archivos prototipos.h, misfuncs.cpp y icom_helpers.h abriéndolos en codeblocks y apretando click derecho y poner Add file to active Project. Una vez que estén todos se puede compilar normalmente.

// 4-Array, vectores
// 4.1-Arreglos nativos
// Conjunto estructurado de datos de un mismo tipo.

// El índice del primer elemento de un array es 0 y el del último elemento de un array de N elementos es N-1.
// No se verifican los límites con el arreglo nativo
// Problemas:
// Pérdida de información de tamaño, excepto en el ámbito de su declaración.
// No chequeo de rango cuando se accede a un elemento por indexado.

// Inicialización
// int noInit[5];
// int arr[5] = {}; //Inicializar todos los elementos en 0
// int integers[5] = { 0, 1, 2, 3, 4 };
// char vocales[] = { 'a', 'e', 'i', 'o', 'u' };
// float datos[500] = { 100.0, 300.0, 505.5 };
// double x[500] = { [2] = 505.5, [0] = 100.0, [1] = 300.0 };// para definer cada índice en particular.
// Conviene definir el tamaño del array con una const int:

// Para poner un array como variable que se ingresa a una función y luego al llamarla:
// void func(int a[])
// func(v);
// Al llamar se le pone el nombre sin los corchetes
// Para escribir matrices
// double mat[filas][columnas] = {{2.3, 3.14, 0.12} primera fila,{2.1, 8.9, 0},{0, 2, 4.56}};
// Inicializar todos los elementos de un array:
// int arr[5];
// int valor = 7;
// for (int i = 0; i < 5; ++i) {
//     arr[i] = valor;
// }
// Rellenar todos los elementos con un valor
// std::fill(std::begin(arr), std::end(arr), 7);
// Con estructuras
// Se puede definir estructuras que pueden guardar los elementos en cada valor del array:
// struct Punto2D {
//     double x;
//     double y;
//     void print() { cout << "(" << x << "," << y << ")\n"; }
// };
// ...
// Punto2D parray[10];
// ...
// parray[i] = parray[i+1]; // copia un elemento completo (es decir, x e y) en cada indice.
// ...
// parray[i].x = parray[i+1].x; // copia el campo “x”
// ...
// parray[i].print();
// Algoritmo para ordenamiento en orden creciente
// for(j=0;j<n;j++){
//       for(i=0;i<n-1;i++){
//            if(V[i]>V[i+1]){
//                a=V[i+1];
//                V[i+1]=V[i];
//                V[i]=a;
//            }
//        }
//    }
// Matriz
// int matriz[3][4]; // Matriz de 3 filas y 4 columnas
// Para iterar:
// for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 4; j++) {
//         cout << matriz[i][j] << " ";
//     }
//     cout << endl;
// }
// Cantidad de filas:
// M.size()
// Cantidad de columnas:
// M[0].size()4.2-Arreglos no nativo: librería std::array
// Array no nativo: std::array provee la funcionalidad de un array de tamaño fijo, pero con facilidades que permiten evitar los problemas anteriores.
// Inicialización
// array<int, 5> myIntArray;
// array<Punto2D, 10> myP2DArray; // array de 10 de Punto2D (definido por un UDT)
// array<int, 3> v1 {1, 2, 3}; // declara e inicializa un array de 3 enteros
// iArray[3] = 32; // pone 32 en el cuarto elemento
// Funciones
// Verificación de índice:
// Al poner .at() reemplaza los corchetes pero verifica los índices y si no está en el array dispara una excepción.
// iArray.at(4) = 60;
// iArray.at(8) = 15; // dispara una excepción del tipo out_of_range
// Tamaño del array:
// iArray.size()
// Método de ordenamiento:
// array<int, 5> myArray { 7, 3, 1, 9, 5 };
// sort(myArray.begin(), myArray.end()); // ordena creciente
// sort(myArray.rbegin(), myArray.rend()); // ordena decreciente


// Recorrer los elementos de un Array:

// 4.3-Arreglos no nativo: std::vector
// Arreglo no nativo que es como un array dinámico
// Se usa más cuando no sabemos cuántos elementos vamos a tener desde la entrada. Array dinámico
// Inicialización
// vector<int> myIntVector; // declara un vector de enteros, llamado myArray
// vector<Punto2D> myP2DVector; // vector de Punto2D
// vector<double> v1 {1.1, 2.2, 3.3}; // declara e inicializa
// Acceso:
// Se puede hacer a través del operador [] en forma no-chequeada, o a través del método .at() en forma chequeada.
// double x = v1[1];
// double y = v1.at(3); // dispara una exepción out_of_range
// Funciones
// Redimensionamiento
// Se le puede agregar elementos al vector utilizando .resize():
// vector<int> myIntVector {0, 1, 2};
// myIntVector.resize(5);


// Si se agregan elementos, los mismos son inicializados con el valor por defecto para el tipo (0 para enteros)
// Agregar elementos
// Agrega el valor i al fondo de v, si no hay lugar, agranda el tamaño del vector. Si no se inicializa con nada, empieza a agregar valores desde el inicio (con índice 0).
// v.push_back(i);
// Para poner elementos en el vector
// int main(){
// 	char a;
// 	vector<char> caracteres;
//       cout<<"Ingrese los caracteres: ";
//       cin>>a;
//       caracteres.push_back(a);
//       cin>>a;
//       caracteres.push_back(a);
// }
// Capacidad
// Define la capacidad que va a tener el vector de almacenar elementos. Si se agregan elementos al vector de manera que se sobrepase la capacidad, se redefine la capacidad como un múltiplo de lo definido (no necesariamente el inmediato superior).
// v.reserve(128);
// Para ver la capacidad del vector:
// v.capacity();
// Tamaño
// Para ver la cantidad de elementos del vector.
// v.size();
// Recorrer los elementos de un vector:
// for (auto v: myIntVector)
// 	cout << v << ' ';
// Se puede guardar string en vectores, para acceder al carácter de cada string de cada elemento del vector:
// for (auto v1: cartas[0]){
//     for (auto v2: cartas[1]){
//          if(v1==v2)return true;
//     }
// }
// Funciones útiles
// Para almacenar las palabras de una oración en un vector. Se puede escribir una oración y detecta la separacion ‘ ‘ para determinar las palabras.
// vector<string> words, w2;
//     for (string s; cin >> s && s != "salir"; ) 
//         words.push_back(s);
// // se guardan las palabras, con cada separación ‘ ‘ en el vector words
// Para recorrer cada palabra del vector string e imprimirlas:
// for (string s : w2)
//         cout << s << "\n";
// Ordena las palabras guardadas en words alfabeticamente.
// sort(words.begin(), words.end());

// 5-Pasaje de Argumentos
// Pasaje de argumentos
// Si se llama a una función que modifica el valor de uno de los elementos del vector, no se ve reflejado en el main aun con void.
// void func(vector<int> a) {
//     a[4] = 32;
//     cout << "En func a[4] = " << a[4] << '\n';
// }
// int main(void){
//     vector<int> v {0, 1, 2, 3, 4, 5, 6};   
//     func(v);
//     cout << "En main v[4] = " << v[4] << '\n';
//     return 0;
// }

// Por valor
// Cuando la función hace una copia de la variable, guardándolo en otro espacio de memoria. Al tener muchas variables hace que se tarde tiempo en guardarse toda la copia. Por lo que no sería tan eficiente.
// void fun(int a)
// Si se le cambia el valor dentro de la función, no se ve afectada en el main.

// Por Referencia
// Cuando la función adopta los valores directamente del espacio de memoria donde se guarda la variable.
// void fun(int &a)
// Si se modifica la variable dentro de la función, se ve modificada en el main.

// Para evitar que se la pueda modificar, se pone const.
// void fun(const array<int, 1000000> &a)
// 5.2-Ámbitos de variables
// El ámbito (se le llama scope) de una variable define:
// Visibilidad: dónde es visible.
// Tiempo de vida: cuando se crea y cuando deja de existir.
// Existen principalmente 2(3) ámbitos para variables:
// Variables locales o automáticas o de stack.
// Variables globales.

// Variables estáticas 
// Variables miembro

// Variables Locales
// Visibilidad: bloque de código en que se la define. Debe ser declarada antes de ser usada.
// Tiempo de vida: el tiempo que dure la ejecución del bloque que la definió. Se crean cuando la variable se declara, deja de existir cuando termina el ámbito en donde fue declarada. Su lugar de vida es una zona llamada “stack” o “pila”. Desde el momento en que es declarada hasta que se cierra la llave del ámbito o scope en la que fue declarada.
// El stack va aumentando de tamaño a medida que se le siguen declarando variables locales dentro de un bloque. Por cada bloque, se inicializa devuelta el stack.
// void f1(int a1, double a2) // a1 y a2 locales a f1
// {
// 	int a, b, c; // variables locales a f1
// 	while(…) {
// 		int d; // variable local al bloque
// 		int c; // variable local al bloque que oculta a la c de f1
// 	}
// }
// void f2(char a1) // a1 local a f2
// {
// int a; // variables locales a f2
// }
// Al usar otra variable local en otro ámbito, se sobreescribe en el mismo espacio de memoria.
// void f() {
// 	int a;
// 	cout << "a de f() esta en " << &a << '\n';
// }
// void g() {
// 	int b;
// 	cout << "b de g() esta en " << &b << '\n';
// 	f();
// }
// int main(){
// 	f();
// 	g();
// 	return 0;
// }
// a de f() esta en 0x7fff29515f54
// b de g() esta en 0x7fff29515f54
// a de f() esta en 0x7fff29515f34

// Variables globales
// Las variables con ámbito global son aquellas que se declaran fuera de cualquier función
// Visibilidad: Son visibles desde cualquier función. 
// Tiempo de vida: el tiempo que dure la ejecución del programa.
// Se desaconseja utilizar variables globales.
// Se debe minimizar el uso de variables globales.
// Las funciones deberían enterarse del problema que tienen que resolver sólo a través de sus argumentos. 
// Una función que utiliza variables globales es muy difícil de reutilizar en otro contexto. 
// Variables locales sumado a la convención de pasajes de argumentos por valor o referencias constantes otorga gran controlabilidad de modificación de una variable.

// Otros ámbitos pueden definir otras variables con los mismos nombres que las globales. En ese caso, se va usar en ese ámbito la variable definida con ese nombre en ese ámbito y no se va a usar la global.
// Variables estáticas
// Una variable/objeto puede declararse como estática.
// static double valor; 
// Aplicadas sobre variables/objetos de ámbito local: Le modifican donde son alojadas, en lugar del stack, se crean en la zona de «datos», modificando también su tiempo de vida.
// Es como una variable local, donde solo se puede usar en el bloque, pero tiene un tiempo de vida de una variable global. Cada vez que se ejecute el bloque y se cambie la variable, la próxima vez q se acceda al bloque la variable de s permanece como queda en la última vez.
// void f(){
// 	static int s = 0;
// 	int b = 0;
// 	s++;
// 	b++;
// 	cout << "s: " << s << " b: " << b << '\n';
// }
// int main() {
// 	f(); f(); f(); f();
// 	return 0;
// }

// 5.2-Ámbito de instancias de UDT
// Se manejan de manera similar a las instancias de tipos nativos. 
// El constructor se define para que una instancia de un UDT sea inicializada correctamente en su declaración. 
// El destructor se define para que una instancia de un UDT pase por una fase de cleanup/destrucción cuando se termina el ámbito en donde fue declarada.
// Es decir, cuando se declara una variable del tipo UDT (struct o class), se inicia un ámbito. Ese nuevo ámbito se inicializa con lo que diga el constructor una vez declarada ese tipo de variable en UDT. Cuando termina el ámbito desde que fue declarada la variable, se activa el destructor y se ejecuta lo que dice en el mismo.
// Ámbito de variables miembro de UDT
// Para las funciones externas, tienen el mismo ámbito que la instancia que las contiene.
// Para una función miembro del UDT (o método) todas las variables miembro de una instancia son accesibles “como si fueran globales”.
// Se almacenan en la misma región de memoria que la instancia. Y su ciclo de vida es el mismo de la instancia.
// Constructores/Destructores
// Constructor:
// Se llama automáticamente cuando se declara una instancia del tipo UDT.
// Es como un método y se caracteriza por tener el mismo nombre del tipo y de no retornar nada.
// Puede haber varios constructores (igual que métodos con el mismo nombre) siempre que se diferencien por cantidad y/o tipo de argumentos.
// Destructor:
// Es llamado automáticamente cuando una variable sale de ámbito.
// Es como un método y se caracteriza por tener el mismo nombre del tipo con el caracter ~ adelante, de no retornar nada y no recibir argumentos.

// struct T {
//     int x, y;
//     T() { //se inicializa cuando x e y no tienen ningun valor
//         x = y = 0;
//         cout << "Construccion con T()\n";
//     }
//     T(int x_, int y_) { //se inicializa cuando x e y no tienen algun valor definido en la declaración
//         x = x_;
//         y = y_;
//         cout << "Construccion con T(int, int)\n";
//     }
//     ~T() {
//         cout << "Destruccion (" << x << ", "<< y << ")\n";
//     }
//     void print() {
//         cout << "(" << x << ", " << y << ")\n";
//     }
// };
// int main() {
//     T t1; //Se inicializa el constructor T(). Primero hace que x=y=0 (depende de los argumentos que se le introduzca activa uno u otro coNStructor)
//     t1.print();
//     cin.get(); // es para que pongas enter y continue el programa
//     {
//         T t3(3,4); //cuando se la inicializa con valores el constructor T(int x_, int y_)
//         t3.print();
//         cin.get();
//     } // sale de scope t3 y se activa el destructor t3
//     cin.get();
//     T t2(1,2);
//     t2.print();
//     cin.get();
//     return 0;
//     // salen de ambito t2 y t1 y se activa el destructor t2 y t1
// }
// Si se crea una clase B con un constructor. Si se define la clase con un arreglo, el constructor se activa la cantidad de veces de cantidad de elementos que tengan. Es como si cada elemento fuese un ámbito nuevo que se inicia.
// Ahora, cuando se termina el ámbito donde estaba declarado el arreglo, se activa la destrucción en la cantidad de elementos que tiene el arreglo donde primero se destruye el ultimo constructor declarado.
// Si no se declara un constructor, se utiliza el constructor por defecto (no hace nada)
// Constructor Copia
// Constructor especial que es activado cuando se quiere inicializar un objeto a partir de otro del mismo tipo (UDT)
// Se realiza una inicialización explícita. Se construye a como copia de b.
// T a = b; // ó T a(b); donde b es del tipo T.
// Declaración:
// A(const A &x) { cout << "Haciendo una copia de " << &x << " en " << this << endl; }

// Se pasan argumentos por valor a funciones:

// En el retorno de funciones:

// Cuando una función recibe objetos por referencia, el “copy constructor” no es activado.
// Forma explicita del constructor copia:
// struct T { T(const T &x) { … } };

// struct A {
//     A() { cout << "Construyendo " << this << endl; }
//     A(const A &x) { cout << "Haciendo una copia de " << &x << " en " << this << endl; }
//     ~A() { cout << "Destruyendo " << this << endl; }
// };
// int main() {
//     A a;
//     cout << "a esta en " << &a << endl;
//     A b(a); // inicializa el cosntructor copia debido a como se ingresa la definición
//     cout << "b esta en " << &b << endl;
//     return 0;
// }

// El this es un puntero al mismo objeto que estoy construyendo.
// Cuando se diseña un UDT, si no se especifica un “copy constructor” el compilador generará uno automáticamente que hará una copia miembro a miembro de la instancia a copiar.
// Hay ocasiones donde un constructor de copia automático es suficientemente bueno.
// Hay ocasiones donde un constructor de copia automático es absolutamente malo.

// 6-Recursión
// 6.1-Recursión
// Recursión: es la especificación de un proceso basado en su propia definición. Involucra:
// Una o más soluciones triviales (directas)
// Una o más soluciones que recurren en el mismo problema, directa o indirectamente
// La manera para declarar en el programa: dentro de la función se vuelve a nombrar a la función:
// int factorial(int n) {
// 	if( n == 0 ) //Siempre se tiene que definir lo que pasa al inicio. Aunque n sea mas grande, por la recursión se va a llegar  a la mínima expresion de n que es 0, entonces, el 0 debe devolver algo
// 	return 1;
// 	return n * factorial(n - 1);
// }
// int fb(int n) {
//     if( n == 0 || n == 1)
//         return n;
//     return fb(n - 1) + fb(n - 2);
// }
// Siempre se debe definir un valor de retorno inicial para que el programa funcione.
// Ejemplo de Hanoi
// void hanoi(int n, int from, int to, int aux) {
// 	if( n == 1 ) {
// 		cout << "Mover de " << from << " a " << to << endl;
// 		return;
// 	}
// 	hanoi( n-1, from, aux, to);
// 	hanoi( 1, from, to, aux);
// 	hanoi( n-1, aux, to, from);
// }
// int main() {
// 	hanoi(3, 1, 3, 2);
// 	return 0;} 
// 6.2-Arreglos de char
// Un string nativo es un array nativo de char terminado con un 0. No es necesario pasar la longitud de los strings nativos.
// char s1[] = { 'T', 'e', 's', 't', 0 };
// char s2[] = "Test";
// char s1[5] = { 'T', 'e', 's', 't', ' ' };
// char s2[6] = { 'w', 'o', 'r', 'k', 's' , '.' };
// char s3[20];
// Funciones útiles
// Concatenar caracteres:
// void concat(char result[], const char str1[],const char str2[]){
// 	int idx1 = 0, idx2 = 0;
// 	char c;
// 	while( (c = str1[idx1]) != 0 )
// 		result[idx1++] = c;
// 	while( (c = str2[idx2]) != 0 )
// 		result[idx1 + idx2++] = c;

// 	result[idx1 + idx2] = 0;
// }
// Comparar caracteres:
// int compara(const char s1[], const char s2[]){
// 	int i = 0;
// 	while( s1[i] && s1[i] == s2[i])
// 		i++;
// 	return s1[i] – s2[i];
// }
// Determinar el largo del string nativo (array de char):
// int largo(const char s[]) {
// 	int i = 0;
// 	for( ; s[i] != 0; i++) ;
// 		return i;
// }
// Para recorrer todos los elementos hasta el final:
// for (int i=0; s1[i] != 0; i++){}

// 6.3-String de biblioteca
// Inicialización
// string s1;
// string s2("AAA"); // con inicialización
// string s3 = "BBB"; // ídem anterior
// string s4{"CCC"}; // ídem anterior
// string s5{s2}; // ídem anterior
// Concatenación
// Concatenación
// s1 = s2 + s3 + s4;
// s1.append(s2); // s1 = "hola mundo"//Agrega s2 al final de s1
// Comparación
// Comparación
// if (s1 == s2) { /* Igualdad */ }
// if (s1 != s2) { /* Desigualdad */ }
// if (s1 < s2) { /* Orden lexicográfico */ }
// if (s1 > s2) { /* Orden lexicográfico inverso */ }
// Las comparaciones entre cadenas (std::string) se realizan lexicográficamente, es decir, carácter por carácter, en el mismo orden que aparecen en el alfabeto o tabla ASCII/Unicode.
// Reglas principales:
// Si un carácter en una posición es menor que el correspondiente en la otra cadena, la primera cadena es menor.
// Si los caracteres en una posición son iguales, se pasa al siguiente carácter.
// Si una cadena es un prefijo exacto de otra, la cadena más corta se considera menor.
// Si todos los caracteres son iguales, las cadenas son iguales.
// (el espacio es mayor que nada) pero menor que cualquier otro caracter
// Funcion compare
// int resultado = s1.compare(s2);
// // Devuelve:
// // 0 si son iguales
// // <0 si s1 es menor que s2
// // >0 si s1 es mayor que s2
// Funcion compare parcial
// int resultado = s.compare(0, 4, "hola"); // Compara los primeros 4 caracteres de s con "hola".
// Verificación
// Largo del string
// s1.length()
// s1.size()
// String vacío
// if (s1.empty())
// Posición de un valor
// size_t pos =s.find(s2) // Devuelve la posición de s2 en s o std::string::npos si no se encuentra
// size_t pos = s.rfind("o"); // Devuelve la posición de la última aparición de "o"
// Una sentencia que define que s.find(s2) no encuentra nada (No posición):
// if(pos != string::npos)
// cout << s2 << " esta en " << pos << '\n';
// Verificacion de prefijos C++20
// if (s.starts_with("hola")) { /* Tiene prefijo "hola" */ }
// if (s.ends_with("mundo")) { /* Tiene sufijo "mundo" */ }
// Iteración
// Recorrido indexado
// for(int i = 0; i < s.length(); ++i) // recorrido indexado
// 	cout << s[i];
// for (size_t i = 0; i < s.size(); ++i) {
//     std::cout << s[i];
// }
// Recorrido auto
// for(auto c : s) // recorrido con range-based for
// 	cout << c;
// for (char c : s) {
//     std::cout << c;
// }
// Recorrido auto pero con un iterador
// for(auto it = s.begin(); it != s.end(); ++it) // idem a través de un iterador
// 	cout << *it; //Imprimir el contenido del apuntado por it
// Iteración inversa
// for (auto it = s.rbegin(); it != s.rend(); ++it) {
//     std::cout << *it; // Itera de atrás hacia adelante.
// }
// Modificación
// Reemplazo por caracteres
// s.replace(0, 4, "adios"); // Reemplaza los primeros 4 caracteres por "adios".
// Insertar un valor en una posición
// s.insert(5, " querido"); // Inserta " querido" en la posición 5.
// Reemplazar un valor
// Reemplaza desde la posición del string s2 (s.find(s2)), todos los caracteres del string s2 (la cantidad es s2.length()) por lo que dice el tercer argumento.
// s.replace(s.find(s2), s2.length(), "eternos");
// Eliminación de caracteres
// s.erase(5, 7); // Elimina 7 caracteres desde la posición 5.
// Redimensionar cadenas
// s.resize(10, 'x'); // Expande a 10 caracteres rellenando con 'x' o trunca si es más larga.
// Pasar carácter a mayúscula
// // Convertir el primer carácter a mayúscula
// texto[0] = std::toupper(texto[0]);
// Pasar carácter a minúscula
// // Convertir el segundo carácter a minúscula
// texto[1] = std::tolower(texto[1]);
// Pasar toda la cadena a mayúscula o minúscula
// std::transform(texto.begin(), texto.end(), texto.begin(), ::toupper);
// std::transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
// Sustracción
// Sustrae una subcadena desde una posición
// std::string sub = s.substr(5, 5); // Obtiene 5 caracteres desde la posición 5.
// Conversión
// De std::string a const char*:
// const char* c_str = s.c_str();
// De cadena a números:
// std::string numStr = "123";
// int num = std::stoi(numStr);
// double d = std::stod(numStr);
// De números a cadena:
// std::string strNum = std::to_string(42);
// Convertir string a vector de caracteres
// std::string s = "hola";
// std::vector<char> vec(s.begin(), s.end());
// Comparación insensible a Mayúsculas
// #include <algorithm>
// #include <cctype>
// std::string s1 = "Hola";
// std::string s2 = "hola";
// std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
// std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
// if (s1 == s2) { /* Comparación insensible a mayúsculas */ }
// Manejo individual de caracteres
// std::string s = "Hola";
// char c = s[0];     // 'H'
// s[0] = 'h';        // Cambia a "hola"
// char d = s.at(1);  // 'o' (similar a s[1] pero verifica límites y lanza excepciones)

// 6.4-Manipulación de archivos
// Para un manejo básico de archivos, se usa  std::ifstream y std::ofstream
// cin es una instancia (objeto) del tipo (clase) std::istream asociado al dispositivo estandar de entrada (redireccionable)
// cout es una instancia (objeto) del tipo (clase) std::ostream asociado al dispositivo estandar de salida (redireccionable) 
// El protocol simplificado de uso es:
// Declaración -> apertura -> manipulación (lecturas o escrituras) -> cierre
// Hay que usar using namespace std;
// Ejemplo de uso:
// int main(void){
// 	ofstream oFile; // crea la instancia de ofstream
// 	oFile.open("kk.dat"); // abre un archivo y lo asocia a oFile
// 	// podria haber declarado ofstream oFile("kk.dat")
// 	if(oFile.is_open()) { // equivalente a if(oFile) { ..., es abrir el archivo
// 		oFile << "Esto va a parar al file\n";
// 		oFile << "y esto\n" << "y esto tambien...\n";
// 		oFile.close();
// 	}
// 	ifstream iFile("kk.dat");
// 	if(iFile) { //Si iFile está abierto
// 		string line; //se define el string line
// 		while (getline (iFile, line))//se define el line como una linea de iFile y va agarrando una línea nueva acá vez q se repite el bucle.
// 			cout << line << '\n';
// 	}
// 	return 0;
// }
// Otro ejemplo: Generar un archivo con datos
// #include "icom_helpers.h"
// // genera un archivo con NUM_DATOS números aleatorios entre 0 y 999
// const int NUM_DATOS = 500;
// int main(void){
// 	ofstream oFile("datos.dat");
// 	if(oFile.is_open()) {
// 		srand(time(0));
		
// 		for(int i = 0; i < NUM_DATOS; ++i)
// 			oFile << (rand()%1000) << '\n';
		
// 	oFile.close();
// 	}
// 	return 0;
// }

// Leer los datos:
// #include "icom_helpers.h"
// // Lee datos desde "datos.dat", los ordena y los escribe en "datos_ord.dat"
// int main(void){
// 	ifstream iFile("datos.dat");
// 	if(iFile.is_open()) {
// 		vector<int> datos;
// 	int d;
// 	while(iFile >> d)
// 		datos.push_back(d);
// 	iFile.close();
// 	sort(datos.begin(), datos.end());
// 	ofstream oFile("datos_ord.dat");
// 	for(int d: datos)
// 		oFile << d << '\n';
// 	}
// 	return 0;
// }
// Forma de ingresar datos
// ifstream infile(filename);
//         if (!infile)
//         {
//             cout << "No se pudo abrir el archivo " << filename << endl;
//             return;
//         }
// while (infile >> equipoA >> equipoB){
// fixtureInicial.emplace_back(equipoA, equipoB); 
//       equiposSet.insert(equipoA);
//        equiposSet.insert(equipoB);
//         }
// Otro
// while (infile >> equipoA >> equipoB >> resultado){
//             partidos[{equipoA,equipoB}].push_back(resultado
//         }
// Agregarle cosas a un puntero a vector:
//     while (ifile >> m1 >> x1 >> y1 >> z1){ //Mientras se pueda encontrar estos valores separados por un espacio:
//         pCluster->push_back(Star(m1,x1,y1,z1));
//     }
// Agregar datos a un archivo y que no se sobreescriban
// void print(unsigned int t){
//         cout<< "Iteracion: " <<t<<endl;
//         cout<< "Poblacion de depredadores: " <<N_Depredadores()<<endl;
//         cout<< "Poblacion de presas: " <<N_Presas()<<endl;
//         cout<< "Cantidad de pasto total: " <<N_Pastizal()<<endl;
//         f_out.open("poblacion.txt", ios::out | ios::app);
//         if(f_out.is_open()) {
//             f_out << "Iteracion: " <<t<<endl;
//             f_out << "Poblacion de depredadores: "<<N_Depredadores()<<endl;
//             f_out << "Poblacion de presas: " <<N_Presas()<<endl;
//             f_out << "Cantidad de pasto total: " <<N_Pastizal()<<endl;
//             f_out.close();
//         }
//     }
// Se agrega , ios::out | ios::app  para no sobreescribir sobre el archivo y que se vayan agregando los datos al final del archivo. Al compilar devuelta elimina todos los datos anteriores y vuelve a imprimir.
// 7-Punteros
// 7.1-Punteros
// Puntero: es una variable que contiene la dirección de memoria de otra variable. Guarda el valor de la dirección de memoria de una variable del mismo tipo que la definida.
// Sin * corresponde a la dirección de memoria de la variable, con * es el valor de la variable. (Aunque para inicializarlo se pone la dirección de memoria)
// Siempre inicializa los punteros, ya sea con nullptr, una dirección válida o memoria dinámica.
// int a = 8;
// int *pi = &a;
// Si se lo declara después:
// int count = 10, x;
// int *pi;
// pi = &count;
// x = *pi;
// Derrreferenciación: para acceder al valor almacenado en la dirección apuntada por el puntero: *ptr
// Para acceder a la dirección de memoria de un char se pone el puntero en la declaración
// char *c[n];
// dirección de memoria de cada componente: &c[j]
// Siempre al usar punteros, hay que inicializarlos.
// Es importante que el tipo de variable definida del puntero sea la misma que el tipo de variable de la variable a guardar.
// Puedo cambiar el valor de una variable mediante el puntero:

// Cuando una variable guarda varios datos en un tipo Struct. El puntero debe seleccionar uno u otro:


// Utilidades
// Modificar el valor de las variables dentro de funciones:
// void incrementar(int* ptr) {
//     (*ptr)++; // Incrementa el valor apuntado
// }

// int main() {
//     int x = 5;
//     incrementar(&x); // Pasa la dirección de x
//     std::cout << x << std::endl; // Salida: 6
//     return 0;
// }
// Arrays y punteros
// int arr[] = {1, 2, 3};
// int* ptr = arr;       // Apunta al inicio del array
// std::cout << ptr[1];  // Salida: 2 (equivalente a arr[1])
// Punteros dobles
// Los punteros pueden apuntar a otros punteros, creando niveles de indirección.
// int x = 10;
// int* ptr = &x;
// int** dblPtr = &ptr; // Apunta al puntero 'ptr'
// Los punteros dobles son útiles cuando trabajas con arrays dinámicos de punteros:
// int rows = 3, cols = 4;
// // Crear un array dinámico de punteros
// int** matrix = new int*[rows];
// // Crear arrays dinámicos para cada fila
// for (int i = 0; i < rows; ++i) {
//     matrix[i] = new int[cols];
// }
// // Asignar valores
// matrix[1][2] = 42; // Segunda fila, tercera columna
// // Liberar memoria
// for (int i = 0; i < rows; ++i) {
//     delete[] matrix[i];
// }
// delete[] matrix;
// Para pasar punteros por referencia:
// void cambiarPuntero(int** ptr) {
//     *ptr = new int(42); // Modifica el puntero original
// }

// int main() {
//     int* p = nullptr;
//     cambiarPuntero(&p); // Pasar la dirección de 'p'
//     std::cout << *p << std::endl; // Salida: 42
//     delete p; // Liberar memoria
//     return 0;
// }
// 5. Analogía para entender punteros dobles
// Piensa en punteros dobles como un sistema de direcciones:
// Variable normal (x): Es como un edificio con un número específico.
// Puntero (p1): Es una carta con la dirección del edificio.
// Puntero doble (p2): Es una carta que contiene la dirección de la carta con la dirección del edificio.
// Para encontrar el edificio:
// Abres la primera carta (*p2) para obtener la dirección del puntero (p1).
// Abres la carta obtenida (*p1) para llegar al edificio (x).
// 7.2-Relación Punteros y Arreglos nativos
// En sí, los arreglos serían punteros fijos a un determinado índice que no pueden ser reapuntados
// Podemos elegir con los punteros donde se guarda.
// Para declararlo:
// int vec[100];
// int *pi = vec; // int *pi = &vec[0];
// Son punteros que no pueden ser reapuntados


// Los arreglos nativos son tales cuando se definen, cuando se pasan como argumento a una función van como un puntero, que no es más que la copia de la dirección de memoria del primer elemento del vector.
// 7.3-Operaciones con punteros de arreglos

// La resta es la distancias entre punteros


// Ejemplo en donde se copian los elementos de un string nativo (vector char) a otro vector.
// #include "icom_helpers.h"
// // copia de strings nativos
// void copyNativeString(char *to, const char *from);
// int main() {
// 	char string1[] = "A string to be copied.";
// 	char string2[50];
// 	copyNativeString(string2, string1);
// 	cout << string2 << endl;
// 	return 0;
// }
// void copyNativeString(char *to, const char *from) {
// 	while( *to++ = *from++ );
// }
// 7.4-Derreferenciar
// Los punteros se pueden derreferenciar. La derreferencia es acceder al valor almacenado.
// El operador de desreferencia (*)
// ptr contiene la dirección de memoria de x.
// *ptr accede al valor almacenado en la dirección que ptr apunta (en este caso, 10).
// int a, *ptr, v[] = { 0, 1, 2, 3, 4, 5 };
// ptr = v;
// a = ptr[2]; //Corresponde al valor numerico
// ptr[1] = 567;
// Equivalencias
// *(ptr+i)  ptr[i]; //Valor numérica en la posición i del stack
// (ptr+i)  &ptr[i]; //Direccion de memoria de la posición i del stack


// 7.5-Puntero a función
// Los punteros a función son punteros que contienen la dirección de memoria donde se encuentra el código de una función. El tipo de un puntero a función está dado por el prototipo de la función a la que apunta. Esto es, el tipo de retorno y la cantidad y tipo de sus argumentos.
// Declaración de una variable puntero a función:
// int (*fnPtr)(void);
// Esto declara la variable fnPtr como un puntero a una función que retorna un entero y no recibe argumentos

// Al usar punteros a funciones, puedes tratar a las funciones como datos, lo que significa que puedes almacenar y pasar funciones a otras partes del código de manera dinámica. Esto es especialmente útil cuando tienes varias funciones similares y necesitas seleccionar cuál ejecutar en tiempo de ejecución.
// Ejemplo en tu código: En lugar de escribir varias estructuras de control como if o switch para seleccionar qué función ejecutar, simplemente almacenas las funciones en un arreglo y las llamas aleatoriamente con un índice. Esto es más elegante y limpio que escribir muchas comparaciones.

// Punteros a función como argumento
// El tipo de puntero a función lo utiliza el compilador para asegurar que al ser llamada la función, la
// cantidad y el tipo de los argumentos y el tipo del valor de retorno sean los adecuados.
// using fun_ptr_t=double (*) (double); //es un alias para una función que retorna un double a partir de un puntero que toma como argumento la función con un parámetro double.
// Te permite escribir código más claro y flexible. Usando fun_ptr_t, puedes pasar diferentes funciones a la función integra, sin tener que saber los detalles específicos de cada una, siempre que sigan la misma firma (es decir, que acepten y devuelvan un double). Es decir, puedo usar cualquier funciona definida como cuad, sincos u otra y ponerla en la inicialización de integra y utilizarla dentro de la definición de integra. Me permite usar distintas funciones con una misma definición de función.

// 1. Abstracción y Flexibilidad
// Al usar punteros a funciones, puedes tratar a las funciones como datos, lo que significa que puedes almacenar y pasar funciones a otras partes del código de manera dinámica. Esto es especialmente útil cuando tienes varias funciones similares y necesitas seleccionar cuál ejecutar en tiempo de ejecución.
// Ejemplo en tu código: En lugar de escribir varias estructuras de control como if o switch para seleccionar qué función ejecutar, simplemente almacenas las funciones en un arreglo y las llamas aleatoriamente con un índice. Esto es más elegante y limpio que escribir muchas comparaciones.
// p[rand()%5](); // Llama aleatoriamente a f1, f2, f3, f4 o f5
// 2. Reusabilidad
// Al usar un alias como FunPtr_t, puedes reutilizar este tipo de puntero a función en diferentes partes del código sin tener que escribir repetidamente la firma de la función. Esto mejora la legibilidad y mantenibilidad del código.
// Ejemplo: Si tienes varias funciones con la misma firma (void nombre_funcion(void)), puedes crear un arreglo de estas funciones y reutilizarlas en distintas partes del programa. Esto es útil, por ejemplo, en programas que requieren ejecutar diferentes rutinas o callbacks.
// 3. Evitar Repetición de Código
// En lugar de escribir un código específico para cada función en cada caso, puedes hacer que el programa seleccione y ejecute la función automáticamente, reduciendo la repetición de código. Esto es particularmente útil cuando tienes muchas funciones que realizan tareas similares.
// Ejemplo: En lugar de llamar explícitamente a f1(), f2(), f3(), etc., cada vez que necesites, puedes usar un bucle o un sistema de selección dinámica (como en tu caso con rand()), para llamar a cualquiera de las funciones automáticamente.
// 4. Diseño basado en eventos o callbacks
// Punteros a funciones son útiles cuando se desea implementar un sistema basado en eventos o callbacks. Por ejemplo:
// En un sistema de menús, puedes tener diferentes acciones (funciones) asignadas a diferentes botones. Los punteros a funciones te permiten fácilmente asociar funciones específicas a cada acción sin usar estructuras de control complicadas.
// En aplicaciones gráficas o de sistemas en tiempo real, puedes usar punteros a funciones para asignar manejadores de eventos o rutinas de actualización dinámicamente.
// 5. Optimización de estructuras de control
// Usar punteros a funciones puede reemplazar un código con muchas sentencias if-else o switch. En su lugar, puedes tener un arreglo de funciones y simplemente acceder a ellas por un índice, lo que puede hacer el código más rápido y más eficiente.
// Ejemplo: Imagina que tienes un sistema donde necesitas ejecutar diferentes rutinas basadas en el estado de un programa. En vez de hacer algo como:
// if (estado == 1) f1();
// else if (estado == 2) f2();
// else if (estado == 3) f3();
// Simplemente puedes usar punteros a funciones:
// FunPtr_t funcs[] = {f1, f2, f3};
// funcs[estado - 1]();
// 6. Modularidad y Escalabilidad
// Si más adelante quieres agregar o cambiar el comportamiento de las funciones que se llaman, simplemente puedes modificar o añadir funciones al arreglo o cambiarlas en tiempo de ejecución. Esto le da una gran modularidad al código, permitiendo que sea fácilmente escalable y modificable sin tener que cambiar demasiadas partes del programa.
// Usar punteros a funciones con typedef en un programa te permite:
// Tratar funciones como datos, pasarlas como argumentos y almacenarlas dinámicamente.
// Reducir la repetición de código y escribir código más limpio y organizado.
// Implementar estructuras dinámicas como menús, sistemas basados en eventos o seleccionar funciones en tiempo de ejecución.
// Facilitar la modularidad y escalabilidad del código, ya que puedes añadir o cambiar funciones sin necesidad de modificar muchas partes del programa.

// 7.6-This
// this es un puntero implícito que apunta al objeto de la clase actual desde el cual se está ejecutando un método.
// Si uso un método de la clase que toma una variable por referencia, se pone return this, para devolver el valor de la referencia después de haber sido modificado por el método.
// Se puede usar this para acceder a los miembros del programa: this->word
// Consideraciones al usar this
// Cosas a considerar para usar this correctamente
// Evitar usar this en objetos nulos: Si el puntero actual (this) es nulo, cualquier intento de acceder a miembros o métodos resultará en un comportamiento indefinido. En este programa, se hace una verificación explícita de this == EmptyTree para evitar este problema.
// Entender el contexto de this:
// En un constructor o destructor, this apunta al objeto que se está creando o destruyendo.
// En métodos estáticos, this no está disponible porque esos métodos no están asociados a ninguna instancia específica.
// No confundir this con punteros normales:
// Aunque this es un puntero, no debería liberarse manualmente con delete. En este programa, el destructor elimina los subárboles (left y right), pero nunca intenta liberar this.
// Uso en métodos que devuelven el objeto actual:
// Es común usar this como retorno cuando se implementa un patrón encadenado (fluent interface), aunque no se usa en este programa.
// Errores comunes con this
// Modificar o liberar el objeto apuntado por this:
// Intentar usar delete this dentro de un método puede causar problemas graves, como acceso a memoria liberada.
// Olvidar inicializar this en estructuras complejas:
// Si se utiliza un patrón de árbol como este, es crucial asegurarse de que los punteros (left, right) estén correctamente inicializados.
// 7.8-Puntero como argumento de una función
// Ejemplo:
// void interactuar(Entidad *e1, Entidad *e2)//El 
// 	{
// 		bool b1,b2;
// 		unsigned int g1,g2;
// 		for (unsigned int i=0; i<reglas.get_CV(); i++)
// 		{
// 			b1 = e1->interactuar(e2);
// 			b2 = e2->interactuar(e1);…
// Poner el * significa que son punteros que almacenan la variable de memoria, para acceder al elemento se usa e1->vida o se puede usar (*e1).vida
// Para llamar a la función hay que poner:
// interactuar(&jugador1, &jugador2);


