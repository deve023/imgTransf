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
        
        // Realiza el alta en la pila de un elemento pasado por argumento.
        // pre: la pila debe haber sido creada.
        // post: la pila modificada con la insercion del nuevo elemento.
        void push(const T &);

        // Elimina el elemento del tope de la pila.
        // pre: la pila, ya creada, debe no estar vacia.
        // post: pila modificada por la eliminacion del elemento del tope.
        T pop();

        // Retorna el valor tope de la pila.
        // pre: la pila, ya creada, no debe estar vacia.
        // post: -
        T tope() const;

        // Devuelve un valor indicando si la pila esta vacia.
        // pre: la pila debe haber sido creada.
        // post: -
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