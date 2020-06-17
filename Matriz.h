#ifndef _MATRIZ_H_INCLUDED_
#define _MATRIZ_H_INCLUDED_


#include <iostream>
using namespace std;

template <typename T>
class Matriz
{
private:
	size_t x,y;
	T ** matriz;
	
public:
	
	Matriz();
	Matriz(const Matriz &);
	Matriz(size_t , size_t );
	~Matriz();

	// Devuelve un booleano indicando si la matriz es vacia.
	// pre: La matriz debe haber sido creada.
	// post: -
	bool esVacia()const;	

	// Recibe un doble puntero a T, y su tamaño, y setea el valor de matriz acorde.
	// pre: El doble puntero debe tener memoria asignada.
	// post: La matriz contiene los valores pasados mediante el doble puntero a T.
	void setMatriz (T**, size_t , size_t);
	
	T* operator[](size_t) const;
	const Matriz &operator = (const Matriz &);
};

template<typename T>
Matriz<T>::Matriz() : x(0), y(0), matriz(NULL)
{
}

template<typename T>
Matriz<T>::Matriz(const Matriz &m)
{
	this->x =m.x;
	this->y =m.y;

	this->matriz = new T * [this->y];

	for(size_t i = 0; i < this->y; i++)
	{	
		this->matriz[i] = new T [this->x];
		for (size_t j = 0;j<this->x;j++)
			this->matriz[i][j]=m.matriz[i][j]; 
	} 
}

template<typename T>
Matriz<T>:: Matriz(size_t x, size_t y)
{
	this->x =x;
	this->y =y;

	this->matriz = new T * [this->y];

	for(size_t i = 0; i < this->y; i++)
		this->matriz[i] = new T [this->x];

}

template<typename T>
Matriz<T>::~Matriz()
{
	if(this->matriz)
	{
		for(size_t i = 0; i < this->y; i++)
			delete[] this->matriz[i];
		delete[] this->matriz;
	}
}


template<typename T>
bool Matriz<T>::esVacia() const
{
  	if (this->matriz==NULL)
  		return true;
  	return false;
}

template<typename T>
T* Matriz<T>::operator[](size_t indice) const
{
    return matriz[indice];
}

template <typename T>
void Matriz<T>::setMatriz(T** m, size_t x, size_t y)
{
	this->x=x;
	this->y=y;

	if (this->matriz)
	{
		for (size_t i=0; i < this->y; i++)
			delete[] this->matriz [i];
		delete[] this -> matriz;
		this->matriz=NULL;
	}

	if (m==NULL)
		this->matriz=NULL;

	else
	{
		this->matriz = new T * [this->y];

		for(size_t i = 0; i < this->y; i++)
		{	
			this->matriz[i] = new T [this->x];
			for (size_t j = 0; j<this->x; j++)
				this->matriz [i][j] = m[i][j];
		}
	}
}	

template <typename T>
const Matriz<T> & Matriz<T>::operator = (const Matriz &m)
{

	if (this->matriz){
		for(size_t i = 0; i < this->y; i++)
			delete[] this->matriz[i];
		delete[] this->matriz;
		this->matriz=NULL;
	}	

	if(m.esVacia())
	{
		this->setMatriz(NULL, 0, 0);
		return *this;
	}

	this->x = m.x;
	this->y = m.y;

	this->matriz = new T * [this->y];

	for(size_t i = 0; i < this->y; i++)
	{	
		this->matriz[i] = new T [this->x];
		for(size_t j = 0; j<this->x; j++)
			this->matriz [i][j] = m.matriz [i][j];
	}
		
	return *this;
}

#endif // _MATRIZ_H_INCLUDED_
