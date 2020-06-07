#ifndef _PILA_H_
#define _PILA_H_


#include "lista.h"
#include "token.h"

class pila
{
    private:
        lista<token> lista_;
        size_t tam_;
    
    public:
        pila();
        pila(const pila &);
        ~pila();
        
        void push(const token &);
        token pop();
        token tope();
        bool vacia();
        
};


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
    return lista_.primero();
}


bool pila::vacia()
{
    return lista_.vacia();
}


#endif //_PILA_H_