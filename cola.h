#ifndef _COLA_H_
#define _COLA_H_


#include "lista.h"


template<typename T>
class cola
{
    private:
        lista<T> lista_;
        size_t tam_;
        
    public:   
        cola();
        cola(const cola &);
        ~cola();
        
        void encolar(const T &);
        T desencolar();
        T frente() const;
        bool vacia() const;
        
        const cola & operator = (const cola &);

};


template<typename T>
cola<T>::cola() : lista_(), tam_(0) 
{
}

template<typename T>
cola<T>::cola(const cola & c) : lista_(c.lista_), tam_(c.tam_) 
{
}

template<typename T>
cola<T>::~cola()
{
}

template<typename T>
void cola<T>::encolar(const T & dato)
{
    lista_.agregar(dato);
    tam_++;
}

template<typename T>
T cola<T>::desencolar()
{
    if(vacia())
        return T();
    T dato = lista_.primero();
    lista_.borrar(0);
    tam_--;
    return dato;
}

template<typename T>
T cola<T>::frente() const
{
    if(vacia())
        return T();
        
    return lista_.primero();
}

template<typename T>
bool cola<T>::vacia() const
{
    return lista_.vacia();
}

template<typename T>
const cola<T> & cola<T>::operator = (const cola &c)
{
	while(!this->vacia())
		this->desencolar();

	this->lista_ = c.lista_;
	this->tam_ = c.tam_;

	return *this;
}
#endif //_COLA_H_