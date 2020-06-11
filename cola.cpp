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

bool cola::strtocola(string str)
{
    // Primero se vacia la cola
    while(!this->vacia())
        this->desencolar();

    string buffer;

    for(size_t i = 0; i <= str.length(); i++)
    {
        if(str[i] == ' ')
            continue;

        if(!buffer.empty() && isalpha(buffer[0]) && !isalnum(str[i]))
        {
            if(buffer[0] == 'j' && buffer.length() == 1)
                this->encolar(token(J));
            else if(buffer[0] == 'z' && buffer.length() == 1)
                this->encolar(token(Z));
            else
                this->encolar(token(FUNCTION, buffer));
            buffer.clear();
        }

        if(!buffer.empty() && isdigit(buffer[0]) && !isdigit(str[i]) && str[i] != '.')
        {
            this->encolar(token(NUMBER, buffer, Complejo(stof(buffer), 0)));
            buffer.clear();
        }

        if(isalpha(str[i]) || isdigit(str[i]) || str[i] == '.')
        {
            buffer += str[i];
            continue;
        }

        switch(str[i])
        {
            case '(':
                this->encolar(token(LPAR));
                break;
            case ')':
                this->encolar(token(RPAR));
                break;
            case '+':
            case '-':
                this->encolar(token(OPERATOR, string(1, str[i]), 2, true));
                break;
            case '*':
            case '/':
                this->encolar(token(OPERATOR, string(1, str[i]), 3, true));
                break;
            case '^':
                this->encolar(token(OPERATOR, string(1, str[i]), 4, false));
                break;
        }
    }

    return true;
}