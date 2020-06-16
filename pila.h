#ifndef _PILA_H_
#define _PILA_H_


#include "lista.h"

template<typename T>
class pila
{
    private:
        lista<T> lista_;
        size_t tam_;
    
    public:
        pila();
        pila(const pila &);
        ~pila();
        
        void push(const T &);
        T pop();
        T tope() const;
        bool vacia() const;
        
};


template<typename T>
pila<T>::pila() : lista_(), tam_(0) 
{
}

template<typename T>
pila<T>::pila(const pila & p) : lista_(p.lista_), tam_(p.tam_) 
{
}

template<typename T>
pila<T>::~pila()
{
}





template<typename T>
void pila<T>::push(const T & dato)
{
    lista_.insertar(dato);
    tam_++;
}

template<typename T>
T pila<T>::pop()
{
    if(vacia())
        return T();
    T dato = lista_.primero();
    lista_.borrar(0);
    tam_--;
    return dato;
}

template<typename T>
T pila<T>::tope() const
{
    if(vacia())
        return T();
    return lista_.primero();
}


template<typename T>
bool pila<T>::vacia() const
{
    return lista_.vacia();
}


#endif //_PILA_H_