#ifndef MATRIZ_H_INCLUDED_
#define MATRIZ_H_INCLUDED_


#include <iostream>
using namespace std;

template <typename T>
class Matriz
{
private:
	int x,y;
	T ** matriz;
	
public:
	
	Matriz ();
	Matriz (const Matriz &);
	Matriz (int , int );
	~Matriz();

	bool esVacia ()const;	
	T* operator[](int) const;
	void setMatriz (T**, int , int);
	const Matriz &operator = (const Matriz &);
	void imprimir();
	
};

template<typename T>
Matriz<T>::Matriz () : x(0), y(0), matriz(NULL)
{
}

template<typename T>
Matriz<T>::Matriz (const Matriz &m)
{
	this->x =m.x;
	this->y =m.y;

	this->matriz = new T * [this->y];

	for(int i = 0; i < this->y; i++)
	{	
		this->matriz[i] = new T [this->x];
		for (int j = 0;j<this->x;j++)
			this->matriz[i][j]=m.matriz[i][j]; 
	} 
}

template<typename T>
Matriz<T>:: Matriz (int x, int y)
{
	this->x =x;
	this->y =y;

	this->matriz = new T * [this->y];

	for(int i = 0; i < this->y; i++)
		this->matriz[i] = new T [this->x];

}

template<typename T>
Matriz<T>::~Matriz()
{
	if(this->matriz)
	{
		for(int i = 0; i < this->y; i++)
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
T* Matriz<T>::operator[](int indice) const
{
    return matriz[indice];
}

template <typename T>
void Matriz<T>::setMatriz(T** m, int x, int y)
{
	this->x=x;
	this->y=y;

	if (this->matriz)
	{
		for (int i=0; i < this->y; i++)
			delete[] this->matriz [i];
		delete[] this -> matriz;
		this->matriz=NULL;
	}

	if (m==NULL)
		this->matriz=NULL;

	else
	{
		this->matriz = new T * [this->y];

		for(int i = 0; i < this->y; i++)
		{	
			this->matriz[i] = new T [this->x];
			for (int j = 0; j<this->x; j++)
				this->matriz [i][j] = m[i][j];
		}
	}
}	

template <typename T>
const Matriz<T> & Matriz<T>::operator = (const Matriz &m)
{

	if (this->matriz){
		for(int i = 0; i < this->y; i++)
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

	for(int i = 0; i < this->y; i++)
	{	
		this->matriz[i] = new T [this->x];
		for(int j = 0; j<this->x; j++)
			this->matriz [i][j] = m.matriz [i][j];
	}
		
	return *this;
}


template <typename T>
void Matriz<T>::imprimir()
{
	cout << this->x << endl <<this->y << endl;
	if(this->matriz==NULL)
		cout << "Matriz nula" << endl;
	else
	{
		for (int i=0;i<this->y;i++)
		{
			for (int j=0;j<this->x;j++)
				cout<<this->matriz[i][j];
			cout<<endl;
		}
		cout<<endl;
	}
}

#endif

