#ifndef _COMPLEJO_INCLUDED_
#define _COMPLEJO_INCLUDED_

#include <iostream>

#include "cola.h"
//class token;

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

	double modulo() const;
	double arg() const;
	Complejo conjugar() const;

	Complejo exp() const;
	Complejo ln() const;

	Complejo pot(int) const;

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