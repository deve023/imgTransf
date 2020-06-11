#include "token.h"
#include <iostream>


token::token() : type_(NONE), value_(""), complejo_(Complejo()), precedence_(0), l_assoc_(false)
{
}

token::token(token_type_t type, string value, Complejo c) :
	type_(type), value_(value), complejo_(c), precedence_(0), l_assoc_(false)
{	
}

token::token(token_type_t type, string value) :
	type_(type), value_(value), complejo_(Complejo()), precedence_(5), l_assoc_(false)
{
}

token::token(token_type_t type, string value, int precedence, bool is_l_assoc) : 
	type_(type), value_(value), precedence_(precedence), l_assoc_(is_l_assoc)
{
}

token_type_t token::getType() const
{
	return this->type_;
}

bool token::is_function() const
{
	return this->type_ == FUNCTION;
}

bool token::is_lpar() const
{
	return this->type_ == LPAR;
}

bool token::is_rpar() const
{
	return this->type_ == RPAR;
}

bool token::is_operator() const
{
	return this->type_ == OPERATOR;
}

bool token::is_number() const
{
	return this->type_ == NUMBER;
}

bool token::is_j() const
{
	return this->type_ == J; 
}

bool token::is_z() const
{
	return this->type_ == Z;
}

bool token::is_l_assoc() const
{
	return l_assoc_;
}

int token::precedence() const
{
	return this->precedence_;
}

Complejo token::complex() const
{
	return this->complejo_;
}

ostream & operator<<(ostream &os, const token &t)
{
	//return os << t.type_ << '(' << t.value_ << ')'; //imprime "tipo(valor)"
	return os << t.value_; //imprime solo el valor
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
			l.agregar(token(NUMBER, buffer, Complejo(stof(buffer), 0)));
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
				l.agregar(token(OPERATOR, string(1, str[i]), 2, true));
				break;
			case '*':
			case '/':
				l.agregar(token(OPERATOR, string(1, str[i]), 3, true));
				break;
			case '^':
				l.agregar(token(OPERATOR, string(1, str[i]), 4, false));
				break;	
		}
		
	}

	return l;
}
