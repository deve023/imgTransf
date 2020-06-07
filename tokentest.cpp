#include "token.h"
#include "pila.h"
#include "cola.h"
#include <iostream>

using namespace std;

int main()
{
    lista<token> l1 = strtolist("phase((25+j*3)^z)");
    l1.imprimir();
    lista<token> l2 = strtolist("$,}#@phase ( ( 25 + j * 3 ) ^ z )");
    l2.imprimir();
    lista<token> l3 = strtolist("jzjzjzjzjz");
    l3.imprimir();
    lista<token> l4 = strtolist("");
    l4.imprimir();
    lista<token> l5 = strtolist("atan2(z)");
    l5.imprimir();
    lista<token> l6 = strtolist("2.35*4*z");
    l6.imprimir();
    lista<token> l7 = strtolist("hehehe123");
    l7.imprimir();
    lista<token> l8 = strtolist("123hehehe");
    l8.imprimir();
    lista<token> l9 = strtolist("heh123ehe");
    l9.imprimir();
    lista<token> l10 = strtolist("%$&*^@");
    l10.imprimir();
    
    pila p1;
    p1.push(token(FUNCTION, "jeje"));
    cout<<p1.pop()<<endl;
    cout<<p1.pop()<<endl;
    
    cola c1;
    c1.encolar(token(FUNCTION, "jeje"));
    cout<<c1.desencolar()<<endl;
    cout<<c1.desencolar()<<endl;
}