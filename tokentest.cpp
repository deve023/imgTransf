#include "token.h"
#include "pila.h"
#include "cola.h"
#include <iostream>

using namespace std;

cola shunting_yard(cola);

int main()
{
    cola cInfix, cRPN;

    cInfix.strtocola("3+ 5 / 2");
    cRPN = shunting_yard(cInfix);

    while(!cRPN.vacia())
        cout << cRPN.desencolar() << " ";
    cout << endl;
/*

    
    lista<token> l1 = strtolist("phase((25+j*3)^z)");
    l1.imprimir();
    lista<token> l2 = strtolist("$,}#@phase ( ( 25 + j * 3 ) ^ z )");
    l2.imprimir();
    lista<token> l3 = strtolist("jzj z j zjzjz");
    l3.imprimir();
    lista<token> l4 = strtolist("");
    l4.imprimir();
    lista<token> l5 = strtolist("atan2(z+j-2^exp(2*z))");
    l5.imprimir();
    lista<token> l6 = strtolist("2.35*4*z");
    l6.imprimir();
    lista<token> l7 = strtolist("hehehe(123)");
    l7.imprimir();
    lista<token> l8 = strtolist("123hehehe");
    l8.imprimir();
    lista<token> l9 = strtolist("heh123ehe");
    l9.imprimir();
    lista<token> l10 = strtolist("%$&*^@");
    l10.imprimir();
    */

    cola c1;
    c1.strtocola("phase((25+j*3)^z)");
    while(!c1.vacia())
        cout << c1.desencolar() << " ";
    cout << endl;

    c1.strtocola("$,}#@phase ( ( 25 + j * 3 ) ^ z )");
    while(!c1.vacia())
        cout << c1.desencolar() << " ";
    cout << endl;

    c1.strtocola("jzj z j zjzjz");
    while(!c1.vacia())
        cout << c1.desencolar() << " ";
    cout << endl;

    c1.strtocola("");
    while(!c1.vacia())
        cout << c1.desencolar() << " ";
    cout << endl;

    c1.strtocola("atan2(z+j-2^exp(2*z))");
    while(!c1.vacia())
        cout << c1.desencolar() << " ";
    cout << endl;

    c1.strtocola("2.35*4*z");
    while(!c1.vacia())
        cout << c1.desencolar() << " ";
    cout << endl;

    c1.strtocola("hehehe(123)");
    while(!c1.vacia())
        cout << c1.desencolar() << " ";
    cout << endl;

    c1.strtocola("123hehehe");
    while(!c1.vacia())
        cout << c1.desencolar() << " ";
    cout << endl;

    c1.strtocola("%$&*^@");
    while(!c1.vacia())
        cout << c1.desencolar() << " ";
    cout << endl;
/*
    pila p1;
    p1.push(token(FUNCTION, "jeje"));
    cout<<p1.pop()<<endl;
    cout<<p1.pop()<<endl;
    
    cola c1;
    c1.encolar(token(FUNCTION, "jeje"));
    cout<<c1.desencolar()<<endl;
    cout<<c1.desencolar()<<endl;
    */
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
