#include "pila.h"

pila::pila() : lista_(), tam_(0) 
{
}


pila::pila(const pila & p) : lista_(p.lista_), tam_(p.tam_) 
{
}


pila::~pila()
{
}


void pila::push(const token & t)
{
    lista_.insertar(t);
    tam_++;
}


token pila::pop()
{
    if(vacia())
        return token();

    token t = lista_.primero();
    lista_.borrar(0);
    tam_--;
    return t;
}


token pila::tope()
{
    if(vacia())
        return token();
    return lista_.primero();
}


bool pila::vacia()
{
    return lista_.vacia();
}

