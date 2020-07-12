#ifndef _PILA_H_
#define _PILA_H_


#include "Lista.h"

template<typename T>
class Pila
{
    private:
        Lista<T> lista_;
        size_t tam_;
    
    public:
        Pila();
        Pila(const Pila &);
        ~Pila();
        
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
Pila<T>::Pila() : lista_(), tam_(0) 
{
}

template<typename T>
Pila<T>::Pila(const Pila & p) : lista_(p.lista_), tam_(p.tam_) 
{
}

template<typename T>
Pila<T>::~Pila()
{
}





template<typename T>
void Pila<T>::push(const T & dato)
{
    lista_.insertar(dato);
    tam_++;
}

template<typename T>
T Pila<T>::pop()
{
    if(vacia())
        return T();
    T dato = lista_.primero();
    lista_.borrar(0);
    tam_--;
    return dato;
}

template<typename T>
T Pila<T>::tope() const
{
    if(vacia())
        return T();
    return lista_.primero();
}


template<typename T>
bool Pila<T>::vacia() const
{
    return lista_.vacia();
}


#endif //_PILA_H_