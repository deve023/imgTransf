#ifndef _PIXEL_H_INCLUDED_
#define _PIXEL_H_INCLUDED_

#include "Complejo.h"

class Pixel
{

private:
	int intensidad;
	Complejo pos;

public:
	Pixel();
	Pixel(int, Complejo);
	~Pixel();

	void setIntensidad(int);
	void setPos(Complejo);
	int getIntensidad() const;
	Complejo getPos() const;

	const Pixel &operator = (const Pixel &);
};

#endif // _PIXEL_H_INCLUDED_