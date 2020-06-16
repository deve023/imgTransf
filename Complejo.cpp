#include "Complejo.h"

#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

Complejo::Complejo():real(0.0),imag(0.0)
{}

Complejo::Complejo(double r, double i):real(r),imag(i)
{}

Complejo::Complejo(const Complejo &c):real(c.real),imag(c.imag)
{}

Complejo::~Complejo()
{}

double Complejo::getReal() const
{
	return this->real;
}

double Complejo::getImag() const
{
	return this->imag;
}

void Complejo::setReal(double r)
{
	this->real = r;
}

void Complejo::setImag(double i)
{
	this->imag = i;
}

double Complejo::modulo() const
{
	return sqrt(this->real * this->real + this->imag * this->imag);
}

double Complejo::arg() const
{
	if(this->imag == 0)
	{
		if(this->real < 0)
			return PI;
		else
			return 0; // Si se trata del complejo (0,0) se devolvera 0.
	}

	if(this->real == 0)
	{	
		if(this->imag > 0)
			return PI/2;
		else
			return 3*PI/2;
	}

	if(this->real > 0)
	{	
		if(this->imag > 0)
			return std::atan(this->imag / this->real); // Cuadrante I
		else
			return 2*PI - std::atan(-this->imag / this->real); // Cuadrante IV
	}
	if(this->imag > 0)
		return PI/2 + std::atan(-this->real / this->imag); // Cuadrante II
	return PI + std::atan(-this->imag / (-this->real)); // Cuadrante III
}

Complejo Complejo::conjugar() const
{
	return Complejo(this->real, -this->imag);
}

Complejo Complejo::exp() const
{
	double r = cos(this->imag);
	double i = sin(this->imag);

	return Complejo(r, i) * std::exp(this->real);
}

Complejo Complejo::ln() const
{
	if(this->modulo() == 0) // Si es el complejo (0,0) no se le puede aplicar ln()
		return Complejo();

	double r = std::log(this->modulo());
	double i = this->arg();

	return Complejo(r, i);
}

Complejo Complejo::pot(int e) const
{
	Complejo resultado = Complejo(1,1);
	Complejo aux;

	if(this->modulo() == 0)
		return Complejo();

	if(e < 0)
	{
		aux = 1.0 / *this;
		e *= -1;
	}
	else
		aux = *this;

	if(e == 1)
		return aux;

	if(e == 0)
		return resultado;

	if(e > 0)
	{
		Complejo recu = aux.pot(e/2);
		resultado = recu * recu;
		if(e & 1) // e impar
			resultado = resultado * aux;
	}

	return resultado;
}

const Complejo& Complejo::operator = (const Complejo &c)
{
	this->setReal(c.getReal());
	this->setImag(c.getImag());

	return *this;
}

Complejo Complejo::operator + (Complejo const &c) const
{
	return Complejo(this->real + c.real, this->imag + c.imag);
}

Complejo Complejo::operator + (double d) const
{
	return Complejo(this->real + d, this->imag);
}

Complejo Complejo::operator - (Complejo const & c) const
{
	return Complejo(this->real - c.real, this->imag - c.imag);
}
Complejo Complejo::operator - (double d) const
{
	return Complejo(this->real - d, this-> imag);
}
Complejo Complejo::operator * (Complejo const & c) const
{
	double r = this->real * c.real - this->imag * c.imag;
	double i = this->imag * c.real + this->real * c.imag;
	return Complejo(r, i);
}

Complejo Complejo::operator * (double d) const
{
	return Complejo(this->real * d, this->imag * d);
}

Complejo Complejo::operator / (Complejo const & c) const
{
	double cAbsSq = c.real * c.real + c.imag * c.imag; // Modulo de c elevado al cuadrado.
	if(cAbsSq == 0)
		return Complejo(); // Si |c| = 0 la division no se puede realizar. Se devuelve el complejo (0,0).

	return *this * c.conjugar() / cAbsSq;
}

Complejo Complejo::operator / (double d) const
{
	if(d == 0)
		return Complejo(); // Si d = 0 la division no se puede realizar. Se devuelve el complejo (0,0).
	return Complejo(this->real / d, this->imag / d);
}

Complejo operator + (double d, Complejo const & c)
{
	return Complejo(d + c.real, c.imag);
}

Complejo operator - (double d, Complejo const & c)
{
	return Complejo(d - c.real, -c.imag);
}

Complejo operator * (double d, Complejo const & c)
{
	return Complejo(d * c.real, d * c.imag);
}

Complejo operator / (double d, Complejo const & c)
{
	if(c.modulo() == 0)
		return Complejo();
	return Complejo(d,0) / c;
}

std::ostream & operator << (std::ostream &os, const Complejo &c)
{
	return os << "(" << c.real << ", " << c.imag << ")";
}

