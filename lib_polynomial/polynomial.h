// Copyright 2023 Vinokurov Ivan

#ifndef LIB_POLYNOMIAL_POLYNOMIAL_H_
#define LIB_POLYNOMIAL_POLYNOMIAL_H_

#include "../lib_list/list.h"

class CMonomial {
 private:
	double coefficient;
	int degree[3];
 public:
	CMonomial();
	CMonomial(const CMonomial& monomial);
	CMonomial(int _coefficient, int* _degree);
	~CMonomial();

	std::string toString();
	bool operator==(CMonomial _monomial);
	bool operator!=(CMonomial _monomial);
	CMonomial operator+(CMonomial _monomial); 
	CMonomial operator-(CMonomial _monomial);
	CMonomial operator*(CMonomial _monomial);
	CMonomial operator*(double _coef);
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
	 double findResult(int _x, int _y, int _z);

	 CPolynomial operator+(CMonomial _monomial);
	 CPolynomial operator-(CMonomial _monomial);
	 CPolynomial operator*(CMonomial _monomial);
	 CPolynomial operator/(CMonomial _monomial);

	 CPolynomial operator+(CPolynomial _monomial);
	 CPolynomial operator-(CPolynomial _monomial);
	 CPolynomial operator*(CPolynomial _monomial);
	 CPolynomial operator*(double _coef);
	 CPolynomial operator/(CPolynomial _monomial);

	 CPolynomial getDerivative(CPolynomial _monomial);
};

#endif