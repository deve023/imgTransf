#ifndef COMPLEJO_INCLUDED_
#define COMPLEJO_INCLUDED_

using namespace std;

class Complejo
{

private:
	double real;
	double imag;

public:
	Complejo():real(0.0),imag(0.0){};
	Complejo(double r, double i):real(r),imag(i){};
	Complejo(const Complejo &c):real(c.real),imag(c.imag){};
	~Complejo(){};

	double getReal() const;
	double getImag() const;
	void setReal(double);
	void setImag(double);

	const Complejo& operator = (const Complejo &);
	Complejo operator * (double) const;

	// FALTAN  operators

};


#endif // COMPLEJO_INCLUDED_