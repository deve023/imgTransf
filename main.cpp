#include <fstream>
#include <iostream>
#include <cstdlib>

#include "Comando.h"
#include "Imagen.h"
#include "Pila.h"
#include "Cola.h"
#include "Token.h"

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_function(string const &);
static void opt_help(string const &);

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "funcion", "-", opt_function, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static Cola<Token> function;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

// Recibe una cola de tokens en notacion infija y devuelve otra cola con tokens en RPN.
// De haber un problema, como no estar balanceada la expresion, se devuelve una cola vacia.
// pre: La cola pasada por argumento debe haber sido creada y no estar vacia.
// post: Devuelve una cola de tokens lista para usarse y no vacia, si todo salio bien.
Cola<Token> shunting_yard(Cola<Token> infix);

// Recibe una cola de tokens y devuelve un booleano indicando si la transformacion que representa es valida.
// La cola de tokens se considera no valida si contiene una funcion que el programa no soporte.
// pre: la cola de tokens debe haber sido creada y no estar vacia.
// post: Devuelve un booleano acorde.
bool esValida(Cola<Token> c);

static void opt_input(string const &arg)
{
	
	if(arg == "-")
		iss = &cin;
	else
	{
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}

	if (!iss->good())
	{
		cerr << "No se puede abrir " << arg << "." << endl;
		exit(1);
	}
}

static void opt_output(string const &arg)
{
	if(arg == "-")
		oss = &cout;
	else
	{
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	if(!oss->good())
	{
		cerr << "No puede abrir " << arg << "." << endl;
		exit(1);
	}

}

static void opt_function(string const &arg)
{

	string f;

	// Funcion por defecto
	if(arg == "-") 
		f = "z";
	else
		f = arg;

	Cola<Token> infix;
	infix = strtocola(f);

	if(!esValida(infix))
	{
		cerr << "La funcion no es valida..." << endl;
		exit(1);
	}

	function = shunting_yard(infix);
	if(function.vacia())
	{
		cerr << "La funcion no es valida." << endl;
		exit(1);
	}
}

static void opt_help(string const &arg)
{
	cout << "tp0 [-f funcion] [-i archivo] [-o archivo]." << endl;

	exit(0);
}


int main(int argc, char * const argv[])
{
	Comando comando(options);
	comando.parse(argc, argv);

	Imagen orig, dest;
	
	// Leo imagen 
	if(!orig.leerArchivoPgm(iss))
	{
		cout << "Error al leer imagen." << endl;
		return 1;
	}

	dest = orig.transformarImagen(function);

	// Se escribe la imagen transformada
	dest.escribirArchivoPgm(oss);
	
	return 0;
}

Cola<Token> shunting_yard(Cola<Token> infix)
{
    Cola<Token> output;
    Pila<Token> opPila;

    while(!infix.vacia())
    {
        Token t = infix.desencolar();
        switch(t.getType())
        {
            case NUMBER:
            case Z:
            case J:
                output.encolar(t);
                break;
            case FUNCTION:
                opPila.push(t);
                break;
            case OPERATOR:
                while(!opPila.vacia())
                {
                	if(opPila.tope().getType() == LPAR)
                	{
                		opPila.push(t);
                		break;
                	}
                	
                    if(opPila.tope().getPrecedence() > t.getPrecedence() || (opPila.tope().getPrecedence() == t.getPrecedence() && t.is_l_assoc()))
                        output.encolar(opPila.pop());
                    else
                    {
                        opPila.push(t);
                        break;
                    }
                }
                if(opPila.vacia())
                    opPila.push(t);
                break;
            case LPAR:
                opPila.push(t);
                break;
            case RPAR:
                while(!opPila.vacia() && !(opPila.tope().getType() == LPAR))
                    output.encolar(opPila.pop());
                if(opPila.vacia())
                    return Cola<Token>(); // error: la expresion esta desbalanceada. Devuelve Cola() por defecto.
                opPila.pop(); // Descarta el LPAR que esta en la pila
                break;
            default:
                return Cola<Token>(); // Si no es de ninguno de estos tipos, hubo un error. Devuelve Cola() por defecto.
        }
    }

    while(!opPila.vacia())
    {
    	if(opPila.tope().getType() == LPAR)
    		return Cola<Token>();
        output.encolar(opPila.pop());
    }

    return output;
}

bool esValida(Cola<Token> c)
{
	while(!c.vacia())
	{
		Token t = c.desencolar();
		token_type_t tType = t.getType();
		if(c.vacia())
		{
			// Si el ultimo token es un operador o una funcion o un LPAR, la expresion no tiene sentido.
			if(tType == OPERATOR || tType == FUNCTION || tType == LPAR)
				return false;
			return true;
		}

		Token sig = c.frente();

		token_type_t sigType = sig.getType();

		if(tType == RPAR)
			continue;

		if(tType == LPAR)
		{
			if(sigType == RPAR)
				return false;
			continue;
		}

		if(tType == FUNCTION)
		{
			string v = t.getValue();
			if(v != "exp" && v != "ln" && v != "re" && v != "im" && v != "abs" && v != "phase")
				return false;

			// Seguido de un FUNCTION debe haber un LPAR.
			if(sigType != LPAR)
				return false;
			continue;
		}

		if(tType == NUMBER || tType == Z || tType == J)
		{
			if(sigType != OPERATOR && sigType != RPAR)
				return false;
			continue;
		}

		if(tType == OPERATOR)
		{
			if(sigType == OPERATOR)
				return false;
			continue;
		}
	}
	return true;
}