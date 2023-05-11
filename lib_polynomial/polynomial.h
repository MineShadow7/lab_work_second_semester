// Copyright 2023 Vinokurov Ivan

#ifndef LIB_POLYNOMIAL_POLYNOMIAL_H_
#define LIB_POLYNOMIAL_POLYNOMIAL_H_

#include "../lib_list/list.h"
#include <sstream>
#include <ostream>
#include <stack>


class CMonomial {
private:
	double coefficient;
	int degree[3];

	bool checkequality(CMonomial m_monomial);
protected:
	double getcoefficient();

public:
	CMonomial();
	CMonomial(const CMonomial& monomial);
	CMonomial(double _coefficient, int* _degree);

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
	friend class CPolynomial;
};

class CPolynomial {
private:
	CList<CMonomial> list;
	int GetPrecedence(char op);
	bool isOperator(char c);
	bool isVariable(char c);
	std::string ToRPN(std::string _string);
	double countMonom(CMonomial monom, double _x, double _y, double _z);
public:
	CPolynomial() { };
	CPolynomial(const CPolynomial& _polynomial);
	CPolynomial(CList<CMonomial> _list);

	~CPolynomial() { }

	std::string toString();

	bool operator==(CPolynomial _polynomial);
	bool operator!=(CPolynomial _polynomial);
	double findResult(double _x, double _y, double _z, std::string _str);
	void Parse(std::string _string);

	CPolynomial operator+(CMonomial _monomial);
	CPolynomial operator-(CMonomial _monomial);
	CPolynomial operator*(CMonomial _monomial);
	CPolynomial operator/(CMonomial _monomial);

	CPolynomial operator=(CPolynomial _polynomial);

	CPolynomial operator+(CPolynomial _polynomial);
	CPolynomial operator-(CPolynomial _polynomial);
	CPolynomial operator*(CPolynomial _polynomial);
	CPolynomial operator*(double _coefficient);
	CPolynomial operator/(CPolynomial _polynomial);

	CPolynomial getDerivative(CPolynomial _polynomial);
};

#endif
