#include "token.h"
#include "cola.h"
#include "pila.h"

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
	
	this->type_ = type;
	this->complejo_ = Complejo();
	this->precedence_ = 0;
	this->l_assoc_ = false;
	
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
			this->complejo_ = Complejo(0,1);
			break;
		case Z:
			this->value_ = "z";
			break;
		default:
			this->value_ = "";
	}


}

token_type_t token::getType() const
{
	return this->type_;
}

string token::getValue() const
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

cola<token> strtocola(string str)
{
    // Primero se vacia la cola
    cola<token> output;
    string buffer;

    for(size_t i = 0; i <= str.length(); i++)
    {
        if(str[i] == ' ')
            continue;

        if(!buffer.empty() && isalpha(buffer[0]) && !isalnum(str[i]))
        {
            if(buffer[0] == 'j' && buffer.length() == 1)
                output.encolar(token(J));
            else if(buffer[0] == 'z' && buffer.length() == 1)
                output.encolar(token(Z));
            else
                output.encolar(token(FUNCTION, buffer));
            buffer.clear();
        }

        if(!buffer.empty() && isdigit(buffer[0]) && !isdigit(str[i]) && str[i] != '.')
        {
            output.encolar(token(NUMBER, buffer, Complejo(stof(buffer), 0)));
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
                output.encolar(token(LPAR));
                break;
            case ')':
                output.encolar(token(RPAR));
                break;
            case '+':
            case '-':
                output.encolar(token(OPERATOR, string(1, str[i]), 2, true));
                break;
            case '*':
            case '/':
                output.encolar(token(OPERATOR, string(1, str[i]), 3, true));
                break;
            case '^':
                output.encolar(token(OPERATOR, string(1, str[i]), 4, false));
                break;
        }
    }
    
    return output;
}

Complejo transformar(cola<token> rpn, Complejo const & z)
{
	pila<Complejo> resultado;
    
	while(!rpn.vacia())
	{
		token actual = rpn.desencolar();
		
		if(actual.getType() == NUMBER || actual.getType() == J)
		{
			resultado.push(actual.getComplex());
		}
		
		if(actual.getType() == Z)
		{
			resultado.push(z);
		}
		
		if(actual.getType() == OPERATOR)
		{
		    Complejo b, a;
			
			if(!resultado.vacia())
				b = resultado.pop();
			else
				return Complejo();
				
			if(!resultado.vacia())
				a = resultado.pop();
			else
				return Complejo();
				
				
			if(actual.getValue() == "+")
			    resultado.push(a+b);
			else if(actual.getValue() == "-")
			    resultado.push(a-b);
			else if(actual.getValue() == "*")
			    resultado.push(a*b);
			else if(actual.getValue() == "/")
			    resultado.push(a/b);
			else if(actual.getValue() == "^")
				resultado.push(a.pot(b));
		}
		
		if(actual.getType() == FUNCTION)
		{
		    Complejo a;
			
			if(!resultado.vacia())
				a = resultado.pop();
			else
				return Complejo();
			
			if(actual.getValue() == "exp")
			    resultado.push(a.exp());
			else if(actual.getValue() == "ln")
			    resultado.push(a.ln());
			else if(actual.getValue() == "re")
			    resultado.push(Complejo(a.getReal(),0));
			else if(actual.getValue() == "im")
			    resultado.push(Complejo(a.getImag(),0));
			else if(actual.getValue() == "phase")
			    resultado.push(Complejo(a.arg(),0));
			else if(actual.getValue() == "abs")
			    resultado.push(Complejo(a.modulo(),0));
		}
	
	}
	
	return resultado.pop();
}