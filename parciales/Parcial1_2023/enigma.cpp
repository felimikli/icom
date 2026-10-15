#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

// Cantidad de pares de caracteres intercambiados de forma arbitraria por el operario de turno
const unsigned int N_plug_pairs = 10;

// UDT que define un caracter del teclado de la maquina Enigma. Recuerde que:
// A==Caracter(0), B==Caracter(1), etc.
enum Caracter
{
	A,	B,	C,	D,	E,	F,	G,	H,	I,	J,	K,	L,	M,	N,	O,	P,	Q,	R,	S,	T,	U,	V,	W,	X,	Y,	Z,	C_SIZE 
};

// UDT que emula los intercambios manuales entre letras (Caracter)
struct Plugboard
{

	// Constructor para la version comercial. Como no intercambiaremos letras en el plugboard,
	// las C_SIZE letras estan mapeadas a si mismas.
	Plugboard()
	{
		// Inicializo todo plug_pairs[A]=A, plug_pairs[B]=B, etc.
		for (int i = 0; i < C_SIZE; i++)
			plug_pairs[i] = Caracter(i);
	}



	// TODO
	//  Constructor para la version militar. El arreglo nativo de Caracter contiene 20 letras,
	//  ya que N_plug_pairs==10: {C0,C1,C2,C3,...,C19} Debe usar esta lista para que quede
	//  mapeada la letra C0 con la C1 y la C1 con la C0, la C2 con la C3 y la C3 con la C2, etc.
	//  Los Caracteres no incluidos en el arreglo nativo c[] deben quedar mapeados a si mismos.
	Plugboard(Caracter c[2 * N_plug_pairs]) {
		// primero mapeo todos a si mismos
		for (int i = 0; i < C_SIZE; i++)
			plug_pairs[i] = Caracter(i);


		// se puede hacer i += 2 pues size c = 2 * algo
		for(int i = 0; i < 2 * N_plug_pairs; i += 2) {
			plug_pairs[c[i]] = c[i + 1];
			plug_pairs[c[i + 1]] = c[i];
		}
	}



	// TODO
	//  Metodo que devuelve el Caracter intercambiado por el Caracter c, asegurando primero que
	//  no se haya salido del rango permitido por su tipo (Caracter)
	Caracter at(Caracter c) {
		if(c >= C_SIZE) {
			// retorno C_SIZE, hubo un error, caracter no valido
			return C_SIZE;
		}
		return plug_pairs[c];
	}
	
	

private:
	// Caracter de salida en funcion del Caracter de entrada (correspondiente al indice del arreglo. i.e., a la entrada 0 == A, 1 == B, etc.)
	Caracter plug_pairs[C_SIZE];
};

// UDT que emula el tambor de entrada. Mezcla una vez los caracteres tanto a la ida como a la vuelta, pero se mantiene siempre fija.
class Wheel
{
	// Caracter de salida en funcion del Caracter de entrada (correspondiente al indice del vector. i.e., a la entrada 0 == A, 1 == B, etc.)
	vector<Caracter> contactos;

public:
	// Inicializa la rueda estatica, mezclando caracteres mediante el uso de los indices. Al usar srand(0) aqui,
	// todas las máquinas enigma virtuales, por mas que sean pseudoaleatorias, van a usar las mismas ruedas y rotores.
	Wheel()
	{
		srand(0);
		Caracter r;
		do
		{
			r = Caracter(rand() % C_SIZE);
			if (find(contactos.begin(), contactos.end(), r) == contactos.end())
				contactos.push_back(r);
		} while (contactos.size() < C_SIZE);
	}



	// TODO
	// Devuelve el Caracter de salida solicitado
	Caracter get_caracter(Caracter in) {
		return contactos[in];
	}
	
	
	
	//TODO
	// Devuelve el indice correspondiente al Caracter solicitado, convertido a Caracter
	Caracter get_indice_caracter(Caracter in) {
		for(int i = 0; i < C_SIZE; i++) {
			if(contactos[i] == in) {
				return Caracter(i);
			}
		}
		return Caracter(C_SIZE);
	}


	// Devuelve la posicion del contacto correspondiente del lado izquierdo de la rueda (para cuando la señal se propaga de derecha a izquierda. Es decir, a la ida)
	Caracter get_contacto_izq(Caracter in)
	{
		return get_caracter(in);
	}
	
	// Devuelve la posicion del contacto correspondiente del lado derecho de la rueda (para cuando la señal se propaga de izquierda a derecha. Es decir, a la vuelta)
	Caracter get_contacto_der(Caracter in)
	{
		return get_indice_caracter(in);
	}
	
	
};

// UDT que emula los rotores. Mezclan una vez los caracteres tanto a la ida como a la vuelta. 
class Rotor
{
	// Numero de veces que avanzo el rotor. No necesariamente empieza en 0, ya que los settings iniciales definiran
	// su posicion inicial.
	unsigned short int indice_inicio;

	// Caracter de salida en funcion del Caracter de entrada (correspondiente al indice del vector. i.e., a la entrada 0 == A, 1 == B, etc.)
	vector<Caracter> contactos;

public:
	Rotor(unsigned short int rot_setting)
	{
		Caracter r;
		do
		{
			r = Caracter(rand() % C_SIZE);
			if (find(contactos.begin(), contactos.end(), r) == contactos.end())
				contactos.push_back(r);
		} while (contactos.size() < C_SIZE);

		indice_inicio = 0;
		rotar(rot_setting);
	}
	
	

	// TODO
	// Devuelve el Caracter correspondiente al indice in.
	Caracter get_caracter(Caracter in) {
		return contactos[(contactos.size() - indice_inicio + in) % contactos.size()];
	}
	
	

	// Devuelve el indice correspondiente al Caracter solicitado, convertido a Caracter
	Caracter get_indice_caracter(Caracter in)
	{
		for (unsigned short int i=0; i<contactos.size(); i++)
		{
			if (contactos.at( (contactos.size() - indice_inicio +i )%contactos.size() ) == in)
			{
				return Caracter(i);
			}
		}
		return C_SIZE;
	}
	
	
	
	// TODO
	// Avanza el Rotor r veces
	void rotar(unsigned short int r) {
		// rotar el vector
		// rotate(contactos.begin(), contactos.begin() + r, contactos.end());
		// vector<Caracter> copy;
		// for(unsigned short int i=0; i<contactos.size(); i++) {
			// copy.push_back(contactos[(i + r) % contactos.size()]);
		// }
		// contactos = copy;
		indice_inicio = (indice_inicio + r) % contactos.size();
	}
	
	
	// Devuelve la posicion del contacto correspondiente del lado izquierdo de la rueda (para cuando la señal se propaga de derecha a izquierda. Es decir, a la ida)
	Caracter get_contacto_izq(Caracter in)
	{
		return get_caracter(in);
	}
	
	// Devuelve la posicion del contacto correspondiente del lado derecho de la rueda (para cuando la señal se propaga de izquierda a derecha. Es decir, a la vuelta)
	Caracter get_contacto_der(Caracter in)
	{
		return get_indice_caracter(in);
	}



	// TODO
	// Rota una vez el rotor. Si se dio una vuelta entera contando desde la posicion 0, no la inicial, devuelve verdadero y
	// reinicia el contador de indice_inicio a 0. Si no se cumple una vuelta, retorna falso
	bool avanzar() {
		indice_inicio++;
		if(indice_inicio == contactos.size()) {
			indice_inicio = 0;
			return true;
		}
		return false;
	}
	
	
};

// UDT que emula el refector. Refleja la señal de forma sencilla, intercambiando de forma estatica 2 Caracteres. 
// Basicamente se aplica una vuelta en U a la señal, es decir: A<->Z, B<->Y, etc.
class Reflector
{
	// Caracter de salida en funcion del Caracter de entrada (correspondiente al indice del vector. i.e., a la entrada 0 == A, 1 == B, etc.)
	vector<Caracter> conexiones;

public:
	Reflector() 
	{
		for (Caracter c_e = A, c_s = Caracter((unsigned short int)C_SIZE - 1); c_e < C_SIZE; c_e = Caracter((unsigned short int)c_e + 1), c_s = Caracter((unsigned short int)c_s - 1))
		{
			conexiones.push_back(c_s);
		}
	}

	Caracter reflejar(Caracter in)
	{
		return conexiones.at(in); // por como esta creado, siempre es reflejo
	}
};

class Enigma
{
	Plugboard p_board;
	Wheel st_wheel;
	Reflector ref;
	vector<Rotor> rot;



	// TODO
	// Avanza los Rotores que correspondan cada vez que se ingresa un Caracter para cifrar o descifrar. El primer Rotor se
	// rota siempre que se llama a este metodo. El segundo rotor solo se rota si el primero cumplio una vuelta entera.
	// El tercero solo se rota si el segundo dio una vuelta entera.
	void avanzar(void) {
		if(rot[0].avanzar()) {
			if(rot[1].avanzar()) {
				rot[2].avanzar();
			}
		}
	}
	
	

public:
	Enigma(const vector<Caracter> &rotor_settings, const Plugboard &p_board_settings) : p_board(p_board_settings), st_wheel(), ref()
	{
		for (unsigned short int i = 0; i < rotor_settings.size(); i++)
		{
			rot.push_back(Rotor(rotor_settings.at(i)));
		}
	}

	// Cifra o descifra un mensaje
	string feed(const string &msg)
	{
		string new_msg;
		Caracter caracter_auxiliar;
		for (auto c : msg)
		{
			// Convierte todos los caracteres que sean letras a mayuscula, y todos los que no lo sean a espacios
			if ((c >= 'a' && c <= 'z'))
				caracter_auxiliar = Caracter(toupper(c) - 'A');
			else if ((c >= 'A' && c <= 'Z'))
				caracter_auxiliar = Caracter(c - 'A');
			else
			{
				new_msg += ' ';
				continue;
			}

			// La señal pasa por el tablero de conexiones
			caracter_auxiliar = p_board.at(caracter_auxiliar);
			
			// La señal pasa por el tambor de entrada
			caracter_auxiliar = st_wheel.get_contacto_izq(caracter_auxiliar);
			
			// La señal pasa por los rotores
			for (unsigned short int i = 0; i < rot.size(); i++)
			{
				caracter_auxiliar = rot.at(i).get_contacto_izq(caracter_auxiliar);
			}
			
			// La señal es reflejada
			caracter_auxiliar = ref.reflejar(caracter_auxiliar);
			
			// La señal pasa en sentido contrario por los rotores
			for (unsigned short int i = 0; i < rot.size(); i++)
			{
				caracter_auxiliar = rot.at(rot.size() - 1 - i).get_contacto_der(caracter_auxiliar);
			}
			
			// La señal pasa en sentido contrario por el tambor de entrada
			caracter_auxiliar = st_wheel.get_contacto_der(caracter_auxiliar);
			
			// La señal pasa en sentido contrario por el tablero de conexiones
			caracter_auxiliar = p_board.at(caracter_auxiliar);
			
			// Se guarda el caracter cifrado en un string, para eventualmente devolver el mensaje cifrado completo
			new_msg += char(caracter_auxiliar) + 'A';
			
			// Avanza (rota) los rotores que correspondan
			avanzar();
		}
		return new_msg;
	}
};

int main()
{
	Caracter pares_conectados[2 * N_plug_pairs] = {A, D,   G, H,   N, K,   L, P,   Z, B,   F, E,   Q, S,   V, W,   Y, X,   I, J};
	Plugboard plugboard_settings(pares_conectados); // Version militar de enigma tenia 10 plugs para switchear los caracteres como 
	// se le antojase al operario de turno, sumando muchisimas mas combinaciones.
	// version comercial no tenia plugboard. i.e., Plugboard plugboard_settings();
	vector<Caracter> rotor_settings_1 = {A, B, C}; // Los rotores tenian C_SIZE posibles posiciones iniciales cada uno. al principio
	                                               // usaban 3 rotores, pero al final habia maquinas con hasta 8.
	vector<Caracter> rotor_settings_2 = {A, A, A}; // Probemos con todos los rotores en 0, condicion por defecto, y considerando que
	                                               // tenemos milagrosamente el plugboard, lo mas dificil de saber, ya garantizado.
	string original_msg, coded_msg, decoded_msg;
	Enigma coder(rotor_settings_1, plugboard_settings);
	Enigma decoder(rotor_settings_1, plugboard_settings);
	Enigma bad_decoder(rotor_settings_2, plugboard_settings); // Si la maquina no empezaba en las MISMAS condiciones que la que codifico,
	                                                          // entonces no se recupera nada util del mensaje

	cout << "Ingrese mensaje a (de)codificar, sin numeros ni caracteres especiales, solo letras: ";
	getline(cin, original_msg);

	coded_msg = coder.feed(original_msg);

	cout << "Mensaje (de)codificado: " << coded_msg << endl;

	decoded_msg = bad_decoder.feed(coded_msg);

	cout << "Mensaje mal de(de)codificado: " << decoded_msg << endl;

	decoded_msg = decoder.feed(coded_msg);

	cout << "Mensaje bien de(de)codificado: " << decoded_msg << endl;

	return 0;
}
