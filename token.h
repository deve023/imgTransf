#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "Complejo.h"
#include "lista.h"

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
    	token(token_type_t, string); // Constructor para FUNCTION, LPAR, RPAR, J y Z
    	token(token_type_t, string, int, bool); // Constructor para OPERATOR
    	
    	token_type_t getType() const;

		bool is_function() const;
		bool is_lpar() const;
		bool is_rpar() const;
		bool is_operator() const;
		bool is_number() const;
		bool is_j() const;
		bool is_z() const;
		bool is_l_assoc() const;
		int precedence() const;
		Complejo complex() const;
		
		friend ostream & operator<<(ostream &, const token &);

};

lista<token> strtolist(string str);

#endif //_TOKEN_H_