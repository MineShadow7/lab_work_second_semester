// Copyright 2023 Vinokurov Ivan

#ifndef LIB_POLYNOMIAL_POLYNOMIAL_H_
#define LIB_POLYNOMIAL_POLYNOMIAL_H_

#include "../lib_list/list.h"
#include "sstream"

class CMonomial {
 private:
	double coefficient;
	int degree[3];

	bool checkequality(CMonomial m_monomial);

 public:
	CMonomial();
	CMonomial(const CMonomial& monomial);
	CMonomial(double _coefficient, int* _degree);
	~CMonomial();

	std::string toString();

	bool operator==(CMonomial _monomial);
	bool operator!=(CMonomial _monomial);

	CMonomial& operator=(CMonomial& _monomial);

	CMonomial operator+(CMonomial _monomial); 
	CMonomial operator-(CMonomial _monomial);
	CMonomial operator*(CMonomial _monomial);
	CMonomial operator*(double _coefficient);
	CMonomial operator/(CMonomial _monomial);

	CMonomial getDerivative(CMonomial _monomial);
};

class CPolynomial {
 private:
	CList<CMonomial> list;
 public:
	 CPolynomial();
	 CPolynomial(const CPolynomial& _polynomial);
	 CPolynomial(CList<CMonomial> _list);
	 ~CPolynomial();

	 std::string toString();

	 bool operator==(CPolynomial _polynomial);
	 bool operator!=(CPolynomial _polynomial);

	 double findResult(double _x, double _y, double _z);

	 void Parse(std::string _string);

	 CPolynomial operator+(CMonomial _monomial);
	 CPolynomial operator-(CMonomial _monomial);
	 CPolynomial operator*(CMonomial _monomial);
	 CPolynomial operator/(CMonomial _monomial);

	 CPolynomial& operator=(CPolynomial& _polynomial);

	 CPolynomial operator+(CPolynomial _polynomial);
	 CPolynomial operator-(CPolynomial _polynomial);
	 CPolynomial operator*(CPolynomial _polynomial);
	 CPolynomial operator*(double _coefficient);
	 CPolynomial operator/(CPolynomial _polynomial);

	 CPolynomial getDerivative(CPolynomial _polynomial);
};

#endif
