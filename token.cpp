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

token::token(token_type_t type)
{
	switch(type)
	{
		case LPAR:
			this->value_ = "(";
			break;
		case RPAR:
			this->value_ = ")";
			break;
		case J:
			this->value_ = "j";
			break;
		case Z:
			this->value_ = "z";
			break;
		default:
			this->value_ = "";
	}

	this->type_ = type;
	this->complejo_ = Complejo();
	this->precedence_ = 0;
	this->l_assoc_ = false;
}

token_type_t token::getType() const
{
	return this->type_;
}

string getValue() const
{
	return this->value_;
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

int token::getPrecedence() const
{
	return this->precedence_;
}

Complejo token::getComplex() const
{
	return this->complejo_;
}

ostream & operator<<(ostream &os, const token &t)
{
	//return os << t.type_ << '(' << t.value_ << ')'; //imprime "tipo(valor)"
	return os << t.value_; //imprime solo el valor
}
