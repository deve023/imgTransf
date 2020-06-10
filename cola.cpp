#include "cola.h"
 
cola::cola() : lista_(), tam_(0) 
{
}


cola::cola(const cola & c) : lista_(c.lista_), tam_(c.tam_) 
{
}


cola::~cola()
{
}


void cola::encolar(const token & t)
{
    lista_.agregar(t);
    tam_++;
}


token cola::desencolar()
{
    if(vacia())
        return token();
    token& t = lista_.primero();
    lista_.borrar(0);
    tam_--;
    return t;
}


token cola::frente()
{
    return lista_.primero();
}


bool cola::vacia()
{
    return lista_.vacia();
}

