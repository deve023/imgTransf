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

static string function;
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

	function = arg;

	// Funcion por defecto
	if(!function.compare("-")) 
		function = "z";
	else
		function = arg;
}

static void opt_help(string const &arg)
{
	cout << "tp0 [-f funcion] [-i archivo] [-o archivo]" << endl;

	exit(0);
}

int main(int argc, char * const argv[])
{
	comando comando(options);
	comando.parse(argc, argv);

	Imagen orig;
	
	// Leo imagen 
	if(!orig.leerArchivoPgm(iss))
	{
		cout << "Error al leer imagen" << endl;
		return 1;
	}
	/*
	Imagen dest;
	
	// Se aplica la transformacion correspondiente
	dest = orig.transformar(function?)

	// Se escribe la imagen transformada
	dest.escribirArchivoPgm(oss);
	*/
	
	return 0;
}
