#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

// representa la base de una jerarquía de expresiones
class Exp {
	public:
		virtual ~Exp() {}

		// imprime la expresión en formato algebraico
		virtual void print() = 0;

		// evalua la expresion especializada con var = X
		virtual double evaluate(double X) = 0;

		// calcula y retorna la expresión derivada
		virtual Exp *derivate() = 0;

		// clona la expresion
		virtual Exp *clone() = 0;

};

// representa expresiones constantes
class ConstExp : public Exp {    // constant
	public:
		ConstExp(double value_)
			: value(value_) { }

		void print()              { /* ToDo */ };
		double evaluate(double X) { /* ToDo */ return 0; }
		Exp *derivate()    { /* ToDo */ return nullptr; }
		Exp *clone()       { /* ToDo */ return nullptr; }

	private:
		double value;
};

// representa expresiones binarias (+, -, *, /)
class BinaryExp : public Exp {    // PLUS, MINUS, MULT, DIV
	public:
		BinaryExp(Exp *e1_, Exp *e2_)
			: e1(e1_), e2(e2_) { }
		~BinaryExp() {
			delete e1;
			delete e2;
		}

	protected:
		Exp *e1;
		Exp *e2;
};

// representa expresiones unarias (sin, cos, tan)
class UnaryExp : public Exp {    // SIN, COS, TAN
	public:
		UnaryExp(Exp *e1_)
			: e1(e1_) { }
		~UnaryExp() {
			delete e1;
		}

	protected:
		Exp *e1;
};

// representa expresiones variables ( X )
class VariableExp : public Exp {    // VARIABLE
	public:
		void print()              { /* ToDo */ };
		double evaluate(double X) { /* ToDo */ return 0; }
		Exp *derivate()    { /* ToDo */ return nullptr; }
		Exp *clone()       { /* ToDo */ return nullptr; }
};

class PlusExp : public BinaryExp {
	public:
		PlusExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2){}
		void print()              { /* ToDo */ };
		double evaluate(double X) { /* ToDo */ return 0; }
		Exp *derivate()    { /* ToDo */ return nullptr; }
		Exp *clone()       { /* ToDo */ return nullptr; }
};

class MinusExp : public BinaryExp {
	public:
		MinusExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2){}
		void print()              { /* ToDo */ };
		double evaluate(double X) { /* ToDo */ return 0; }
		Exp *derivate()    { /* ToDo */ return nullptr; }
		Exp *clone()       { /* ToDo */ return nullptr; }
};

class MultExp : public BinaryExp {
	public:
		MultExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2){}
		void print()              { /* ToDo */ };
		double evaluate(double X) { /* ToDo */ return 0; }
		Exp *derivate()    { /* ToDo */ return nullptr; }
		Exp *clone()       { /* ToDo */ return nullptr; }
};

class DivExp : public BinaryExp {
	public:
		DivExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2){}
		void print()              { /* ToDo */ };
		double evaluate(double X) { /* ToDo */ return 0; }
		Exp *derivate()    { /* ToDo */ return nullptr; }
		Exp *clone()       { /* ToDo */ return nullptr; }
};

class SinExp : public UnaryExp {
	public:
		SinExp(Exp *e1) : UnaryExp(e1){}
		void print()              { /* ToDo */ };
		double evaluate(double X) { /* ToDo */ return 0; }
		Exp *derivate()    { /* ToDo */ return nullptr; }
		Exp *clone()       { /* ToDo */ return nullptr; }
};

class CosExp : public UnaryExp {
	public:
		CosExp(Exp *e1) : UnaryExp(e1){}
		void print()              { /* ToDo */ };
		double evaluate(double X) { /* ToDo */ return 0; }
		Exp *derivate()    { /* ToDo */ return nullptr; }
		Exp *clone()       { /* ToDo */ return nullptr; }
};

class TanExp : public UnaryExp {
	public:
		TanExp(Exp *e1) : UnaryExp(e1){}
		void print()              { /* ToDo */ };
		double evaluate(double X) { /* ToDo */ return 0; }
		Exp *derivate()    { /* ToDo */ return nullptr; }
		Exp *clone()       { /* ToDo */ return nullptr; }
};


int main()
{
	Exp *expr = new DivExp(
			new SinExp(                        // numerador
				new PlusExp(
					new MultExp(
						new ConstExp(3),
						new VariableExp()),
					new ConstExp(4))),
			new PlusExp(                       // denominador
				new ConstExp(2),
				new MultExp(
					new ConstExp(3),
					new CosExp(
						new DivExp(
							new VariableExp(),
							new PlusExp(
								new ConstExp(2),
								new VariableExp()))))));


	expr->print();

	double val = expr->evaluate(3.14);

	cout << "la Exp evaluada en 3.14 vale: " << val << endl;
	Exp *deriv = expr->derivate();

	deriv->print();

	delete deriv;
	delete expr;

	return 0;
}
