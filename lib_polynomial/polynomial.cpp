#include "../lib_polynomial/polynomial.h"

#pragma region MonomRealization

bool CMonomial::checkequality(CMonomial m_monomial)
{
    return (degree[0] == m_monomial.degree[0] && degree[1] == m_monomial.degree[1] && degree[2] == m_monomial.degree[2]);
}

CMonomial::CMonomial()
{
    coefficient = 0.0;
    for(int i = 0; i < 2; i++)
    {
        degree[i] = 0;
    }
}

CMonomial::CMonomial(const CMonomial& monomial)
{
    coefficient = monomial.coefficient;
    for (int i = 0; i < 2; i++)
    {
        degree[i] = monomial.degree[i];
    }
}

CMonomial::CMonomial(double _coefficient, int* _degree)
{
    coefficient = _coefficient;
    for (int i = 0; i < 2; i++)
    {
        degree[i] = _degree[i];
    }
}

std::string CMonomial::toString()
{
    std::stringstream ss;
    ss << coefficient;
    if (degree[0] != 0)
        ss << "x^" << degree[0];
    if (degree[1] != 0)
        ss << "y^" << degree[1];
    if (degree[2] != 0)
        ss << "z^" << degree[2];
    return ss.str();
}

bool CMonomial::operator==(CMonomial _monomial)
{
    if (checkequality(_monomial))
        return true;
    else
    {
        return false;
    }
}

bool CMonomial::operator!=(CMonomial _monomial)
{
    return !(*this == _monomial);
}

CMonomial& CMonomial::operator=(CMonomial& _monomial)
{
    coefficient = _monomial.coefficient;
    degree[0] = _monomial.degree[0];
    degree[1] = _monomial.degree[1];
    degree[2] = _monomial.degree[2];
    return *this;
}

CMonomial CMonomial::operator+(CMonomial _monomial)
{
    if (checkequality(_monomial))
        return CMonomial(coefficient + _monomial.coefficient, degree);
    else
        throw std::invalid_argument("Invalid Arguments: Cannot add monoms with different degrees");
}

CMonomial CMonomial::operator-(CMonomial _monomial)
{
    if(checkequality(_monomial))
    
        return CMonomial(coefficient - _monomial.coefficient, degree);
    else
        throw std::invalid_argument("Invalid Arguments: Cannot subtract monoms with different degrees");
}

CMonomial CMonomial::operator*(CMonomial _monomial)
{
    return CMonomial(coefficient * _monomial.coefficient, 
        new int[3]{ degree[0] + _monomial.degree[0],
            degree[1] + _monomial.degree[1],
            degree[2] + _monomial.degree[2] });
}

CMonomial CMonomial::operator*(double _coefficient)
{
    return CMonomial(coefficient * _coefficient, degree);
}

CMonomial CMonomial::operator/(CMonomial _monomial)
{
    return CMonomial(coefficient / _monomial.coefficient, 
        new int[3]{ degree[0] - _monomial.degree[0],
            degree[1] - _monomial.degree[1],
            degree[2] - _monomial.degree[2] });
}

CMonomial CMonomial::getDerivative(CMonomial _monomial)
{
    int newDegree[] = { degree[0], degree[1], degree[2] };
    if (_monomial.degree[0] > 0) {
        newDegree[0]--;
        return CMonomial(coefficient * _monomial.degree[0], newDegree);
    }
    else if (_monomial.degree[1] > 0) {
        newDegree[1]--;
        return CMonomial(coefficient * _monomial.degree[1], newDegree);
    }
    else if (_monomial.degree[2] > 0) {
        newDegree[2]--;
        return CMonomial(coefficient * _monomial.degree[2], newDegree);
    }
    else
        throw std::invalid_argument("Can't solve derivative with invalid arguments.");
};

#pragma endregion

#pragma region PolinomRealization
CPolynomial::CPolynomial() { };

CPolynomial::CPolynomial(CList<CMonomial> _list)
{
    list.cpy(_list);
}

CPolynomial::CPolynomial(const CPolynomial& _polynomial)
{
    list.cpy(_polynomial.list);
}

CPolynomial::~CPolynomial() { };

CPolynomial& CPolynomial::operator=(CPolynomial& _polynomial)
{
    CList<CMonomial> cpy;
    cpy.cpy(list);
    for (int i = 0; i < cpy.size(); i++) {
        cpy.remove(i) == _polynomial.list.remove(i);
    }
}


#pragma endregion
