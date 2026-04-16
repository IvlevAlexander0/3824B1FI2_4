#ifndef INTERFACE_INTERFACE_H
#define INTERFACE_INTERFACE_H

#include "../lib_polynomial/polynomial.h"
#include"../lib_table/table.h"
#include"../lib_table/table_AVL.h"
#include"../lib_table/table_hash.h"
#include"../lib_table/table_vector.h"



class InterfacePol {
	Polynomial Pol1;
	Polynomial Pol2;

public:
	InterfacePol();
	~InterfacePol();

	void input_polyn();
	void actions();
	Polynomial sum()const;
	Polynomial sub()const;
	Polynomial mul()const;
	Polynomial sum2()const;
	Polynomial sub2()const;
};


class InterfaseTable {
	Table<Polynomial>* _table;
	int count;
	Polynomial* getPolynomial(const std::string&);

public:
	InterfaseTable();
	~InterfaseTable();

	void choice();
	void inputData(const Polynomial& result = Polynomial());
	Polynomial* findData();
	void removeData();
	int showOperations();
	void workingWithPolynomials();
};
#endif // !INTERFACE_INTERFASE_H