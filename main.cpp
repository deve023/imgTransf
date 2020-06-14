#include <fstream>
#include <iostream>
#include <cstdlib>

#include "comando.h"
#include "Imagen.h"

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

static cola function;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

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

	cola infix;
	infix.strtocola(f)

	if(!esValida(infix))
	{
		cerr << "La funcion no es valida." << endl;
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
	cout << "tp0 [-f funcion] [-i archivo] [-o archivo]" << endl;

	exit(0);
}

cola shunting_yard(cola infix);
bool esValida(cola c);

int main(int argc, char * const argv[])
{
	comando comando(options);
	comando.parse(argc, argv);

	Imagen orig, dest;
	
	// Leo imagen 
	if(!orig.leerArchivoPgm(iss))
	{
		cout << "Error al leer imagen" << endl;
		return 1;
	}

	/*
	// Se aplica la transformacion correspondiente
	dest = orig.transformar(function);

	// Se escribe la imagen transformada
	dest.escribirArchivoPgm(oss);
	*/
	
	return 0;
}

cola shunting_yard(cola infix)
{
    cola output;
    pila opPila;

    while(!infix.vacia())
    {
        token t = infix.desencolar();
        switch(t.getType())
        {
            case NUMBER:
                output.encolar(t);
                break;
            case FUNCTION:
                opPila.push(t);
                break;
            case OPERATOR:
                while(!opPila.vacia())
                {
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
                    return cola(); // error: la expresion esta desbalanceada. Devuelve Cola() por defecto.
                opPila.pop(); // Descarta el LPAR que esta en la pila
                break;
            default:
                return cola(); // Si no es de ninguno de estos tipos, hubo un error. Devuelve Cola() por defecto.
        }
    }

    while(!opPila.vacia())
        output.encolar(opPila.pop());

    return output;
}

bool esValida(cola c)
{
	bool isZ = false;

	while(!c.vacia())
	{
		token t = c.desacolar();
		if(t.getType() == Z)
		{
			isZ = true;
			continue;
		}

		if(t.getType() != FUNCTION)
			continue;

		string v = t.getValue();
		if(v != "exp" && v != "ln" && v != "re" && v != "im" && v != "abs" && v != "phase")
			return false;

	}

	return isZ;
}