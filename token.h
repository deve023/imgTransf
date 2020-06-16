#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "lista.h"
#include "Complejo.h"
#include "cola.h"

#include <string>
#include <iostream>

using namespace std;

typedef enum{NONE, FUNCTION, LPAR, RPAR, OPERATOR, NUMBER, J, Z} token_type_t;

class token
{
    private:
        token_type_t type_;
        string value_;
        Complejo complejo_; // Si no se trata de un NUMBER, sera el 0+0i. Si es z tambien se le asigna ese valor nulo.
        int precedence_; // Si no se trata de un OPERATOR, sera 5.
        bool l_assoc_; // Si no se trata de un OPERATOR sera falso
        
    public:
    	token();
    	token(token_type_t, string, Complejo); // Constructor para NUMBER
    	token(token_type_t, string); // Constructor para FUNCTION
    	token(token_type_t, string, int, bool); // Constructor para OPERATOR
        token(token_type_t); // Constructor para LPAR, RPAR, Z y J
    	
    	token_type_t getType() const;
        string getValue() const;
		int getPrecedence() const;
		Complejo getComplex() const;

		bool is_function() const;
		bool is_lpar() const;
		bool is_rpar() const;
		bool is_operator() const;
		bool is_number() const;
		bool is_j() const;
		bool is_z() const;
		bool is_l_assoc() const;
		
		friend ostream & operator<<(ostream &, const token &);

};


cola<token> strtocola(string);
Complejo transformar(cola<token> &, Complejo const &);

#endif //_TOKEN_H_