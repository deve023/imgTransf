#ifndef _MATRIZ_H_INCLUDED_
#define _MATRIZ_H_INCLUDED_


#include <iostream>

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

	// Libera la memoria asignada a la matriz y le asgina valores nulos a los atributos.
	// pre: -
	// post: -
	void setMatrizNULL();
	
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
void Matriz<T>::setMatrizNULL()
{
	if(this->matriz)
	{
		for(int i = 0; i < this->y; i++)
			delete[] this->matriz[i];
		delete[] this->matriz;
		this->matriz = NULL;
		this->x = 0;
		this->y = 0;
	}
}	

template <typename T>
const Matriz<T> & Matriz<T>::operator = (const Matriz &m)
{
	this->setMatrizNULL();

	if(m.esVacia())
	{
		this->setMatrizNULL();
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
