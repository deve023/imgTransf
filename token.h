#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "Complejo.h"
#include "lista.h"

#include <iostream>

using namespace std;

typedef enum{NONE, FUNCTION, LPAR, RPAR, OPERATOR, NUMBER, J, Z} token_type_t;


class token
{
    private:
        token_type_t type_;
        string value_;
        //Complejo complejo_;
        //int precedence_;
        //bool l_assoc_;
        
    public:
    	token();
    	token(token_type_t, string);
    	
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