#include "Complejo.h"

#include <cmath>

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

const Complejo& Complejo::operator = (const Complejo &c)
{
	this->setReal(c.getReal());
	this->setImag(c.getImag());

	return *this;
}

Complejo Complejo::operator * (double f) const
{
	return Complejo(this->real*f ,this->imag*f);
}
