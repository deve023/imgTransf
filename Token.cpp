#include "Token.h"
#include "Cola.h"
#include "Pila.h"

#include <iostream>


Token::Token() : type_(NONE), value_(""), complejo_(Complejo()), precedence_(0), l_assoc_(false)
{
}

Token::Token(token_type_t type, string value, Complejo c) :
	type_(type), value_(value), complejo_(c), precedence_(0), l_assoc_(false)
{	
}

Token::Token(token_type_t type, string value) :
	type_(type), value_(value), complejo_(Complejo()), precedence_(5), l_assoc_(false)
{
}

Token::Token(token_type_t type, string value, int precedence, bool is_l_assoc) : 
	type_(type), value_(value), precedence_(precedence), l_assoc_(is_l_assoc)
{
}

Token::Token(token_type_t type)
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

token_type_t Token::getType() const
{
	return this->type_;
}

string Token::getValue() const
{
	return this->value_;
}

bool Token::is_l_assoc() const
{
	return l_assoc_;
}

int Token::getPrecedence() const
{
	return this->precedence_;
}

Complejo Token::getComplex() const
{
	return this->complejo_;
}

ostream & operator<<(ostream &os, const Token &t)
{
	//return os << t.type_ << '(' << t.value_ << ')'; //imprime "tipo(valor)"
	return os << t.value_; //imprime solo el valor
}

Cola<Token> strtocola(string str)
{
    Cola<Token> output;
    string buffer;
	
    for(size_t i = 0; i <= str.length(); i++)
    {
        if(str[i] == ' ')
            continue;
		
		if(str[i] == '-' && (i==0 || str[i-1]=='('))
		{
			output.encolar(Token(NUMBER, "-1", Complejo(-1,0)));
			output.encolar(Token(OPERATOR,"*",3,true));
			continue;
		}
		
        if(!buffer.empty() && isalpha(buffer[0]) && !isalnum(str[i]))
        {
            if(buffer[0] == 'j' && buffer.length() == 1)
                output.encolar(Token(J));
            else if(buffer[0] == 'z' && buffer.length() == 1)
                output.encolar(Token(Z));
            else
                output.encolar(Token(FUNCTION, buffer));
            buffer.clear();
        }

        if(!buffer.empty() && isdigit(buffer[0]) && !isdigit(str[i]) && str[i] != '.')
        {
            output.encolar(Token(NUMBER, buffer, Complejo(stof(buffer), 0)));
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
                output.encolar(Token(LPAR));
                break;
            case ')':
                output.encolar(Token(RPAR));
                break;
            case '+':
            case '-':
                output.encolar(Token(OPERATOR, string(1, str[i]), 2, true));
                break;
            case '*':
            case '/':
                output.encolar(Token(OPERATOR, string(1, str[i]), 3, true));
                break;
            case '^':
                output.encolar(Token(OPERATOR, string(1, str[i]), 4, false));
                break;
        }
    }
    
    return output;
}


Complejo transformar(Cola<Token> rpn, Complejo const & z)
{
	Pila<Complejo> resultado;
    
	while(!rpn.vacia())
	{
		Token actual = rpn.desencolar();
		
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