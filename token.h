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


ostream & operator<<(ostream &os, const token &t)
{
	//return os << t.type_ << '(' << t.value_ << ')'; //imprime "tipo(valor)"
	return os << t.value_; //imprime solo el valor
}

token::token() : type_(NONE), value_("")
{
}

token::token(token_type_t type, string value) : type_(type), value_(value)
{
}


lista<token> strtolist(string str)
{
	lista<token> l;
	string buffer;
	
	for(size_t i = 0; i<=str.length(); i++)	
	{
		if(str[i] == ' ')
			continue;
		
		if(!buffer.empty() && isalpha(buffer[0]) && !isalnum(str[i]))
		{
			if(buffer[0] == 'j' && buffer.length() == 1)
				l.agregar(token(J, "j"));
			else if(buffer[0] == 'z' && buffer.length() == 1)
				l.agregar(token(Z, "z"));
			else
			{
				l.agregar(token(FUNCTION, buffer));
				
			}	
			buffer.clear();
		}
		
		if(!buffer.empty() && isdigit(buffer[0]) && !isdigit(str[i]) && str[i]!='.')
		{
			l.agregar(token(NUMBER, buffer));
			buffer.clear();
		}

		if(isalpha(str[i]) || isdigit(str[i]) || str[i] == '.')
		{
			buffer+=str[i];
			continue; 
		}

		
	    switch(str[i])
		{
			case '(':
				l.agregar(token(LPAR, "("));
				break;
			case ')':
				l.agregar(token(RPAR, ")"));
				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
				l.agregar(token(OPERATOR, string(1, str[i])));
				break;	
		}
		
	}

	return l;
}

#endif //_TOKEN_H_