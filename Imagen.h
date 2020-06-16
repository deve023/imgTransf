#ifndef IMAGEN_H_INCLUDED_
#define IMAGEN_H_INCLUDED_

#ifndef NULL
#define NULL 0
#endif

#include "Complejo.h"
#include "Pixel.h"
#include "Matriz.h"

#include <iostream>

#define INTENSIDADMAX_MAX 65536 // Valor máximo para intensidadMax según el formato PGM

using namespace std;

class Imagen
{

private:
	int sizeX, sizeY;
	int intensidadMax;
	Matriz<Pixel> pixeles;

public:
	Imagen();
	Imagen(Matriz<int> intensidadPixeles, int sx, int sy, int im);
	Imagen(const Imagen &);
	~Imagen();

	bool setIntensidadMax(int);

	// Setea los valores de pixeles, sizeX y sizeY.
	// Se le pasa una matriz con la intensidad de cada pixel, y sus dimensiones.
	// Devuelve false si no pudo almacenar los valores.
	// 		En ese caso si intensidadPixeles era NULL, no se ve alterada la imagen.
	//		En cambio si el problema surgio con las intensidades de los pixeles, se deja pixeles apuntando a NULL.
	// pre: pixeles debe no ser NULL y sx e sy almacenar sus dimensiones y ser ambos positivos.
	//      Las intensidades deben estar en el rango [0, intensidadMax].
	// post: imagen tendra almacenados sus pixeles, con intensidad y posicion en el plano complejo acordes. Asi como sizeX y sizeY.
	bool setPixeles(Matriz<int> intensidadPixeles, int sx, int sy);

	int getSizeX() const;
	int getSizeY() const;
	int getIntensidadMax() const;

	// Se devuelve una copia de la matriz dinamica de pixeles almacenada en imagen
	// Si this->pixeles es NULL devuelve NULL.
	// pre: imagen deberia existir y tener una matriz de pixeles asociada
	// post: se devuelve un puntero a la matriz copia de pixeles
	Matriz<Pixel> getPixeles() const  ;
	// Se devuelve un puntero a una matriz dinamica que almacena las intensidades de los pixeles asociados a la imagen
	// Si this->pixeles es NULL devuelve NULL.
	// pre: imagen deberia existir y tener una matriz de pixeles asociada
	// post: se devuelve un puntero a la matriz dinamica de intensidades de pixeles
	Matriz<int> getIntensidadPixeles() const;

	Imagen &operator = (const Imagen &);

	// Imagen transformar(funcion?) const;

	// Se lee una imagen en formato PGM de (*istream) y se almacena en el objeto imagen.
	// pre: istream debe estar apuntando al archivo ya abierto en modo lectura, este debe ser de texto y respetar el formato de imagen PGM.
	//      Asi como tener almacenada una imagen no nula.
	// post: el objeto imagen termina almacenando los datos de la imagen leida.
	// en caso de fallar la lectura, se devuelve false y no se modifican los atributos del objeto imagen.
	bool leerArchivoPgm(istream *);

	// Se escribe en formato PGM en (*ostream) los datos del objeto imagen.
	// Si la imagen es nula no se escribe el archivo.
	// pre: ostream debe estar apuntando a un archivo de texto ya abierto en modo escritura. La imagen debe no ser nula.
	// post: el archivo queda reescrito con los datos de la imagen en formato PGM.
	void escribirArchivoPgm(ostream *) const;
};

#endif // IMAGEN_H_INCLUDED_