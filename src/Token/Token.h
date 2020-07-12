#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "../Estructuras/Lista.h"
#include "../Complejo/Complejo.h"
#include "../Estructuras/Cola.h"
#include "../Estructuras/Pila.h"

#include <string>
#include <iostream>

using namespace std;

typedef enum{NONE, FUNCTION, LPAR, RPAR, OPERATOR, NUMBER, J, Z} token_type_t;

class Token
{
    private:
        token_type_t type_;
        string value_;
        Complejo complejo_; // Si no se trata de un NUMBER, sera el 0+0i. Para un J tendra valor i.
        int precedence_; // Si no se trata de un OPERATOR, sera 0.
        bool l_assoc_; // Si no se trata de un OPERATOR sera falso
        
    public:
    	Token();
    	Token(token_type_t, string, Complejo); // Constructor para NUMBER
    	Token(token_type_t, string); // Constructor para FUNCTION
    	Token(token_type_t, string, int, bool); // Constructor para OPERATOR
        Token(token_type_t); // Constructor para LPAR, RPAR, Z y J
    	
    	token_type_t getType() const;
        string getValue() const;
		int getPrecedence() const;
		Complejo getComplex() const;
		bool is_l_assoc() const;
		
		friend ostream & operator<<(ostream &, const Token &);

};

// Recibe una string y devuelve la cola de tokens correspondiente.
// Recorre la string de izq a der y va acolando los respectivos tokens.
// pre: -
// post: La cola de tokens mantiene el orden en que se leyo la string, de izq a der.
Cola<Token> strtocola(string);

// Recibe una cola de tokens que contiene la transformacion a aplicar en RPN y el complejo al cual se le aplica, devuelve el resultado.
// En caso de no poder ejecutar la transformacion devuelve el complejo 0+0i.
// pre: La cola debe no estar vacia y contener la transformacion en RPN. La transformacion debe ser valida.
// post: Devuelve el resultado de aplicarle la transformacion al complejo.
Complejo transformar(Cola<Token>, Complejo const &);

#endif //_TOKEN_H_