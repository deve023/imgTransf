#ifndef _COMPLEJO_INCLUDED_
#define _COMPLEJO_INCLUDED_

#include <iostream>

#include "Cola.h"

class Complejo
{

private:
	double real;
	double imag;

public:
	Complejo();
	Complejo(double, double);
	Complejo(const Complejo &);
	~Complejo();

	double getReal() const;
	double getImag() const;
	void setReal(double);
	void setImag(double);

	// Calcula el modulo del complejo y lo devuelve.
	double modulo() const;

	// Calcula el argumento del complejo y lo devuelve.
	double arg() const;

	// Calcula el conjugado del complejo y lo devuelve.
	Complejo conjugar() const;

	// Devuelve el resultado de aplicar exp(z).
	Complejo exp() const;

	// Devuelve el resultado de aplicar ln(z).
	Complejo ln() const;

	// Devuelve el resultado de aplicar z^w, siendo z y w dos complejos. z siendo el complejo al que se le aplica el metodo.
	Complejo pot(const Complejo &) const;

	const Complejo& operator = (const Complejo &);

	Complejo operator + (Complejo const &) const;
	Complejo operator + (double) const;
	Complejo operator - (Complejo const &) const;
	Complejo operator - (double) const;
	Complejo operator * (Complejo const &) const;
	Complejo operator * (double) const;
	Complejo operator / (Complejo const &) const;
	Complejo operator / (double) const;

	friend Complejo operator + (double, Complejo const &);
	friend Complejo operator - (double, Complejo const &);
	friend Complejo operator * (double, Complejo const &);
	friend Complejo operator / (double, Complejo const &);
	
	friend std::ostream & operator << (std::ostream &, const Complejo &);
	
};



#endif // _COMPLEJO_INCLUDED_