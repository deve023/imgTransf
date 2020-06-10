#ifndef _COLA_H_
#define _COLA_H_


#include "lista.h"
#include "token.h"


class cola
{
    private:
        lista<token> lista_;
        size_t tam_;
        
    public:   
        cola();
        cola(const cola &);
        ~cola();
        
        void encolar(const token &);
        token desencolar();
        token frente();
        bool vacia();
};

#endif //_COLA_H_