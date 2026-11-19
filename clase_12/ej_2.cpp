///////////////////
// EJERICICIO 02 //
///////////////////
/*
Sistema de Simulación (problema de diseño).

IDEAS PRINCIPALES DEL DISEÑO
----------------------------
1) Block (clase base abstracta): todo lo que aparece en el diagrama es un bloque.
   Tiene nombre, puertos de entrada, puertos de salida y tres operaciones que el
   simulador llama en cada paso de tiempo:
       leerEntradas()      -> copia el valor de la señal conectada a cada entrada
       calcularSalidas(t)  -> y = f(estado, u, t)
       actualizarEstado()  -> x(t+dt) = g(x, u, t)   (solo bloques con estado)

2) Clasificación de bloques (cada tipo es una clase derivada):
       - Fuentes  (0 entradas): Constant, Clock, SignalGenerator, Reference...
       - Sumideros(0 salidas):  ToWorkspace, Animation, Scope...
       - Algebraicos (sin estado, salida depende de la entrada en el mismo paso):
                     Gain, Sum, Mux, Saturation, Fcn, MatrixGain...
       - Dinámicos (con estado): Integrator, LimitedIntegrator, TransferFunction,
                     DiscreteStateEstimator...
       - Subsystem: un bloque que CONTIENE un diagrama (patrón Composite).

3) Señales: una Signal une un puerto de salida con un puerto de entrada.
   Una salida puede alimentar a muchas entradas, pero una entrada tiene
   una sola fuente. El valor que viaja es un vector<double> (para soportar Mux).

4) Diagram: es dueño de los bloques (unique_ptr) y de las señales.

5) Subsystem: contiene un Diagram con bloques Inport/Outport. Conectarse a
   la entrada i del subsistema equivale a conectarse al Inport i de adentro, y
   leer la salida i del subsistema es leer la salida del Outport i. Así el
   simulador puede "aplanar" toda la jerarquía y no necesita tratar los
   subsistemas como caso especial. El nombre completo se arma con el padre:
   "Pendulum/Mux".

6) Simulador: aplana el diagrama, calcula el ORDEN DE EJECUCIÓN y corre el loop.
   El orden sale de un ordenamiento topológico (Kahn) con esta regla:
     "B depende de A si una salida de A entra en B y B tiene feedthrough directo"
   Los bloques con estado (integradores) NO tienen feedthrough: su salida en el
   paso n solo depende del estado, por eso cortan los lazos de realimentación
   (como el del péndulo). Si igual queda un ciclo -> lazo algebraico -> error.

   Loop de simulación, para cada paso t:
       for b in orden: b.leerEntradas(); b.calcularSalidas(t);
       for b in orden: b.leerEntradas(); b.actualizarEstado(t, dt);
   El estado se actualiza en una segunda pasada porque un integrador calcula su
   salida ANTES de que el bloque que lo alimenta (más adelante en el orden) haya
   calculado la suya; recién en la segunda pasada su entrada está actualizada.

Abajo está el diseño en C++. Se implementaron unos pocos bloques (de forma
mínima) solo para poder compilar y probar el diseño con un ejemplo.
*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <cmath>
#include <algorithm>

using Valor = std::vector<double>;   // valor que transporta una señal

class Block;
class Subsystem;

/////////////////
//   PUERTOS   //
/////////////////
struct OutputPort {
	Block* duenio;
	Valor valor;
};

struct InputPort {
	Block* duenio;
	const OutputPort* fuente = nullptr;   // de dónde viene la señal
	Valor valor;
};

// Señal: une una salida con una entrada
struct Signal {
	OutputPort* desde;
	InputPort* hacia;
};

/////////////////
//    BLOCK    //
/////////////////
class Block {
	public:
		Block(const std::string& nombre_, size_t nIn, size_t nOut)
			: nombre(nombre_), entradas(nIn), salidas(nOut) {
			for (auto& e : entradas) e.duenio = this;
			for (auto& s : salidas)  s.duenio = this;
		}
		virtual ~Block() = default;

		// Los puertos guardan punteros a su dueño -> copiar un bloque
		// dejaría punteros colgando. Se prohíbe la copia.
		Block(const Block&) = delete;
		Block& operator=(const Block&) = delete;

		const std::string& getNombre() const { return nombre; }
		std::string nombreCompleto() const;          // "Pendulum/Mux"
		void setPadre(Subsystem* p) { padre = p; }

		virtual size_t numEntradas() const { return entradas.size(); }
		virtual size_t numSalidas()  const { return salidas.size(); }
		virtual InputPort&  entrada(size_t i) { return entradas.at(i); }
		virtual OutputPort& salida(size_t i)  { return salidas.at(i); }

		// ¿la salida depende de la entrada en el mismo paso de tiempo?
		virtual bool tieneFeedthrough() const { return true; }

		// Operaciones que llama el simulador
		virtual void inicializar() {}
		void leerEntradas() {
			for (auto& e : entradas) {
				if (!e.fuente) throw std::runtime_error("Entrada sin conectar en " + nombreCompleto());
				e.valor = e.fuente->valor;
			}
		}
		virtual void calcularSalidas(double t) = 0;
		virtual void actualizarEstado(double /*t*/, double /*dt*/) {}

		// Agrega a 'lista' los bloques ejecutables (un Subsystem agrega los suyos)
		virtual void aplanar(std::vector<Block*>& lista) { lista.push_back(this); }

	protected:
		std::string nombre;
		Subsystem* padre = nullptr;
		std::vector<InputPort>  entradas;
		std::vector<OutputPort> salidas;
};

/////////////////
//   DIAGRAM   //
/////////////////
class Diagram {
	public:
		// Crea un bloque de tipo T dentro del diagrama. Nombres únicos.
		template <typename T, typename... Args>
		T& agregar(Args&&... args) {
			auto b = std::make_unique<T>(std::forward<Args>(args)...);
			T& ref = *b;
			if (buscar(ref.getNombre()))
				throw std::runtime_error("Nombre repetido: " + ref.getNombre());
			ref.setPadre(padre);
			bloques.push_back(std::move(b));
			return ref;
		}

		void conectar(Block& origen, size_t salida, Block& destino, size_t entrada) {
			OutputPort& o = origen.salida(salida);
			InputPort& i = destino.entrada(entrada);
			if (i.fuente) throw std::runtime_error("Entrada ya conectada en " + destino.nombreCompleto());
			i.fuente = &o;
			senales.push_back({&o, &i});
		}

		Block* buscar(const std::string& nombre) const {
			for (auto& b : bloques) if (b->getNombre() == nombre) return b.get();
			return nullptr;
		}

		void aplanar(std::vector<Block*>& lista) {
			for (auto& b : bloques) b->aplanar(lista);
		}

		void setPadre(Subsystem* p) { padre = p; }

	private:
		std::vector<std::unique_ptr<Block>> bloques;   // el diagrama es dueño
		std::vector<Signal> senales;
		Subsystem* padre = nullptr;                    // nullptr = diagrama raíz
};

/////////////////////////
//  BLOQUES CONCRETOS  //
/////////////////////////

// ---- Fuentes ----
class Constant : public Block {
	public:
		Constant(const std::string& n, Valor v) : Block(n, 0, 1), valor(v) {}
		void calcularSalidas(double) override { salidas[0].valor = valor; }
	private:
		Valor valor;
};

class Clock : public Block {
	public:
		Clock(const std::string& n) : Block(n, 0, 1) {}
		void calcularSalidas(double t) override { salidas[0].valor = {t}; }
};

// ---- Algebraicos ----
class Gain : public Block {
	public:
		Gain(const std::string& n, double k_) : Block(n, 1, 1), k(k_) {}
		void calcularSalidas(double) override {
			salidas[0].valor = entradas[0].valor;
			for (double& x : salidas[0].valor) x *= k;
		}
	private:
		double k;
};

class Sum : public Block {
	public:
		// signos: por ejemplo "+-+" -> 3 entradas, la segunda se resta
		Sum(const std::string& n, const std::string& signos_)
			: Block(n, signos_.size(), 1), signos(signos_) {}
		void calcularSalidas(double) override {
			Valor res(entradas[0].valor.size(), 0.0);
			for (size_t i = 0; i < entradas.size(); i++) {
				double s = (signos[i] == '-') ? -1 : 1;
				for (size_t j = 0; j < res.size(); j++) res[j] += s * entradas[i].valor[j];
			}
			salidas[0].valor = res;
		}
	private:
		std::string signos;
};

class Mux : public Block {        // junta varias señales en un vector
	public:
		Mux(const std::string& n, size_t nIn) : Block(n, nIn, 1) {}
		void calcularSalidas(double) override {
			Valor res;
			for (auto& e : entradas) res.insert(res.end(), e.valor.begin(), e.valor.end());
			salidas[0].valor = res;
		}
};

class Saturation : public Block {
	public:
		Saturation(const std::string& n, double lo_, double hi_) : Block(n, 1, 1), lo(lo_), hi(hi_) {}
		void calcularSalidas(double) override {
			salidas[0].valor = entradas[0].valor;
			for (double& x : salidas[0].valor) x = std::clamp(x, lo, hi);
		}
	private:
		double lo, hi;
};

class Fcn : public Block {        // función arbitraria f(u)
	public:
		Fcn(const std::string& n, std::function<Valor(const Valor&)> f_) : Block(n, 1, 1), f(f_) {}
		void calcularSalidas(double) override { salidas[0].valor = f(entradas[0].valor); }
	private:
		std::function<Valor(const Valor&)> f;
};

// ---- Dinámicos (con estado) ----
class Integrator : public Block {
	public:
		Integrator(const std::string& n, Valor x0_) : Block(n, 1, 1), x0(x0_) {}
		bool tieneFeedthrough() const override { return false; }   // corta lazos
		void inicializar() override { x = x0; }
		void calcularSalidas(double) override { salidas[0].valor = x; }
		void actualizarEstado(double, double dt) override {     // Euler explícito
			for (size_t i = 0; i < x.size(); i++) x[i] += dt * entradas[0].valor[i];
		}
	protected:
		Valor x0, x;
};
// Otros con estado que entrarían igual: LimitedIntegrator (Integrator + clamp),
// TransferFunction (num/den -> espacio de estados), DiscreteStateEstimator, etc.

// ---- Sumideros ----
class ToWorkspace : public Block {
	public:
		ToWorkspace(const std::string& n) : Block(n, 1, 0) {}
		void calcularSalidas(double t) override {
			tiempos.push_back(t);
			datos.push_back(entradas[0].valor);
		}
		std::vector<double> tiempos;
		std::vector<Valor> datos;
};

// ---- Puertos de subsistema ----
class Inport : public Block {     // dentro del subsistema: trae la entrada de afuera
	public:
		Inport(const std::string& n) : Block(n, 1, 1) {}
		void calcularSalidas(double) override { salidas[0].valor = entradas[0].valor; }
};

class Outport : public Block {    // dentro del subsistema: lleva la salida hacia afuera
	public:
		Outport(const std::string& n) : Block(n, 1, 1) {}
		void calcularSalidas(double) override { salidas[0].valor = entradas[0].valor; }
};

/////////////////
//  SUBSYSTEM  //
/////////////////
class Subsystem : public Block {
	public:
		Subsystem(const std::string& n, size_t nIn, size_t nOut) : Block(n, 0, 0) {
			interno.setPadre(this);
			for (size_t i = 0; i < nIn; i++)
				inports.push_back(&interno.agregar<Inport>("In" + std::to_string(i + 1)));
			for (size_t i = 0; i < nOut; i++)
				outports.push_back(&interno.agregar<Outport>("Out" + std::to_string(i + 1)));
		}

		Diagram& diagrama() { return interno; }
		Inport&  inport(size_t i)  { return *inports.at(i); }
		Outport& outport(size_t i) { return *outports.at(i); }

		// Las entradas/salidas del subsistema "son" las de sus Inport/Outport
		size_t numEntradas() const override { return inports.size(); }
		size_t numSalidas()  const override { return outports.size(); }
		InputPort&  entrada(size_t i) override { return inports.at(i)->entrada(0); }
		OutputPort& salida(size_t i)  override { return outports.at(i)->salida(0); }

		// Un subsistema no se ejecuta: se ejecutan sus bloques internos
		void calcularSalidas(double) override {}
		void aplanar(std::vector<Block*>& lista) override { interno.aplanar(lista); }

	private:
		Diagram interno;
		std::vector<Inport*> inports;
		std::vector<Outport*> outports;
};

std::string Block::nombreCompleto() const {
	return padre ? padre->nombreCompleto() + "/" + nombre : nombre;
}

/////////////////
//  SIMULADOR  //
/////////////////
class Simulador {
	public:
		Simulador(Diagram& d) : raiz(d) {}

		void simular(double t0, double tf, double dt) {
			std::vector<Block*> orden = calcularOrden();
			for (Block* b : orden) b->inicializar();

			for (double t = t0; t <= tf + dt / 2; t += dt) {
				for (Block* b : orden) { b->leerEntradas(); b->calcularSalidas(t); }
				// se vuelven a leer las entradas: un bloque sin feedthrough puede
				// haberse ejecutado antes que el bloque que lo alimenta
				for (Block* b : orden) { b->leerEntradas(); b->actualizarEstado(t, dt); }
			}
		}

		std::vector<Block*> calcularOrden() {
			std::vector<Block*> bloques;
			raiz.aplanar(bloques);

			// grafo de dependencias (solo a través de bloques con feedthrough)
			std::unordered_map<Block*, std::vector<Block*>> sucesores;
			std::unordered_map<Block*, int> gradoEntrada;
			for (Block* b : bloques) gradoEntrada[b] = 0;
			for (Block* b : bloques) {
				if (!b->tieneFeedthrough()) continue;
				for (size_t i = 0; i < b->numEntradas(); i++) {
					const OutputPort* f = b->entrada(i).fuente;
					if (!f) throw std::runtime_error("Entrada sin conectar en " + b->nombreCompleto());
					sucesores[f->duenio].push_back(b);
					gradoEntrada[b]++;
				}
			}

			// Kahn
			std::vector<Block*> orden, listos;
			for (Block* b : bloques) if (gradoEntrada[b] == 0) listos.push_back(b);
			while (!listos.empty()) {
				Block* b = listos.back(); listos.pop_back();
				orden.push_back(b);
				for (Block* s : sucesores[b])
					if (--gradoEntrada[s] == 0) listos.push_back(s);
			}
			if (orden.size() != bloques.size())
				throw std::runtime_error("Lazo algebraico en el diagrama");
			return orden;
		}

	private:
		Diagram& raiz;
};

/////////////////
//   EJEMPLO   //
/////////////////
/*
  Oscilador armónico x'' = u - k x  armado como subsistema "Oscilador":

        u  ->(In1)-> [Sum +-] -> [Integrator v] -> [Integrator x] -> (Out1) -> x
                        ^                                 |
                        +-------------[Gain k]------------+

  Con u = 0, k = 1, x(0) = 1, v(0) = 0  ->  x(t) = cos(t)
*/
void ej_2()
{
	Diagram modelo;
	auto& u    = modelo.agregar<Constant>("Entrada", Valor{0.0});
	auto& osc  = modelo.agregar<Subsystem>("Oscilador", 1, 1);
	auto& reloj = modelo.agregar<Clock>("Clock");
	auto& mux  = modelo.agregar<Mux>("Mux", 2);
	auto& out  = modelo.agregar<ToWorkspace>("out.x");

	Diagram& d = osc.diagrama();
	auto& sum  = d.agregar<Sum>("Sum", "+-");
	auto& intV = d.agregar<Integrator>("IntegradorV", Valor{0.0});
	auto& intX = d.agregar<Integrator>("IntegradorX", Valor{1.0});
	auto& k    = d.agregar<Gain>("K", 1.0);

	d.conectar(osc.inport(0), 0, sum, 0);
	d.conectar(sum, 0, intV, 0);
	d.conectar(intV, 0, intX, 0);
	d.conectar(intX, 0, k, 0);
	d.conectar(k, 0, sum, 1);          // realimentación
	d.conectar(intX, 0, osc.outport(0), 0);

	modelo.conectar(u, 0, osc, 0);
	modelo.conectar(reloj, 0, mux, 0);
	modelo.conectar(osc, 0, mux, 1);
	modelo.conectar(mux, 0, out, 0);

	Simulador sim(modelo);

	std::cout << "Orden de ejecucion:" << std::endl;
	for (Block* b : sim.calcularOrden())
		std::cout << "  " << b->nombreCompleto() << std::endl;

	sim.simular(0.0, 10.0, 0.001);

	std::cout << "\n   t        x(t)       cos(t)" << std::endl;
	for (size_t i = 0; i < out.datos.size(); i += 1000) {
		double t = out.datos[i][0], x = out.datos[i][1];
		std::printf("%5.1f  %10.5f  %10.5f\n", t, x, std::cos(t));
	}
}

int main()
{
	try {
		ej_2();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
