#include <iostream>

#include "Complejo.h"

using namespace std;

int main()
{
	Complejo a(-1,3), b(3,4), c(0,0), d(-1, 3), e(-2, -8), f(2, -7);

	cout << "--------------------------------------" << endl;

	cout << endl;
	cout << "Suma" << endl;
	cout << a << " + " << b << " = " << a+b << endl;
	cout << a << " + " << "1.5 = " << a+1.5 << endl;
	cout << "1.5 + " << a << " = " << 1.5+a << endl;
	cout << endl;

	cout << "--------------------------------------" << endl;

	cout << endl;
	cout << "Resta" << endl;
	cout << a << " - " << b << " = " << a-b << endl;
	cout << a << " - " << "0.2 = " << a-0.2 << endl;
	cout << "0.2 - " << a << " = " << 0.2-a << endl;
	cout << endl;

	cout << "--------------------------------------" << endl;

	cout << endl;
	cout << "Multiplicacion" << endl;
	cout << a << " * " << b << " = " << a*b << endl;
	cout << a << " * 2 = " << a*2 << endl;
	cout << "2 * " << a << " = " << 2*a << endl;
	cout << endl;

	cout << "--------------------------------------" << endl;

	cout << endl;
	cout << "Division" << endl;
	cout << a << " / " << b << " = " << a/b << endl;
	cout << a << " / 2 = " << a/2 << endl;
	cout << "2 / " << a << " = " << 2/a << endl;
	cout << endl;

	cout << "--------------------------------------" << endl;

	cout << endl;
	cout << "Conjugado" << endl;
	cout << b << "    -->    " << b.conjugar() << endl;
	cout << endl;

	cout << "--------------------------------------" << endl;

	cout << endl;
	cout << "Modulo" << endl;
	cout << b << "    -->    " << b.modulo() << endl;
	cout << endl;

	cout << "--------------------------------------" << endl;

	cout << endl;
	cout << "Exponencial" << endl;
	cout << b << "    -->    " << b.exp() << endl;
	cout << endl;

	cout << "--------------------------------------" << endl;

	cout << endl;
	cout << "Logaritmo" << endl;
	cout << b << "    -->    " << b.ln() << endl;
	cout << c << "    -->    " << c.ln() << endl;
	cout << d << "    -->    " << d.ln() << endl;
	cout << e << "    -->    " << e.ln() << endl;
	cout << f << "    -->    " << f.ln() << endl;
	cout << endl;

	cout << "--------------------------------------" << endl;

	cout << endl;
	cout << "Potenciacion" << endl;
	cout << b << " ^ " << b << " = " << b.pot(b) << endl;
	cout << c << " ^ " << b << " = " << c.pot(b) << endl;
	cout << d << " ^ " << c << " = " << d.pot(c) << endl;
	cout << e << " ^ " << f << " = " << e.pot(f) << endl;
	cout << b << " ^ " << e << " = " << b.pot(e) << endl;
	cout << c << " ^ " << a << " = " << c.pot(a) << endl;
	cout << f << " ^ " << c << " = " << f.pot(c) << endl;
	cout << d << " ^ " << b << " = " << d.pot(b) << endl;
	cout << e << " ^ " << d << " = " << e.pot(d) << endl;
	cout << endl;

	cout << "--------------------------------------" << endl;

	cout << endl;
	cout << "FIN" << endl;
	cout << endl;

	cout << "--------------------------------------" << endl;

}
 