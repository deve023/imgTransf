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

#endif //_PILA_H_