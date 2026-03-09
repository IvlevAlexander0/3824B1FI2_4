#ifndef INTERFACE_INTERFACE_H
#define INTERFACE_INTERFACE_H

#include "../lib_polynomial/polynomial.h"

class Interface {
	Polynomial Pol1;
	Polynomial Pol2;

public:
	Interface();
	~Interface();

	void input_polyn();
	void actions();
	Polynomial sum()const;
	Polynomial sub()const;
	Polynomial mul()const;
	Polynomial sum2()const;
	Polynomial sub2()const;
	Polynomial mul2()const;
};

#endif // !INTERFACE_INTERFASE_H