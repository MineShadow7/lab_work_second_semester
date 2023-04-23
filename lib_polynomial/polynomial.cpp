#include "../lib_polynomial/polynomial.h"

#pragma region MonomRealization

bool CMonomial::checkequality(CMonomial m_monomial)
{
    return (degree[0] == m_monomial.degree[0] && degree[1] == m_monomial.degree[1] && degree[2] == m_monomial.degree[2]);
}

double CMonomial::getcoefficient()
{
    return coefficient;
}

CMonomial::CMonomial()
{
    coefficient = 0.0;
    for (int i = 0; i < 2; i++)
    {
        degree[i] = 0;
    }
}

CMonomial::CMonomial(const CMonomial& monomial)
{
    coefficient = monomial.coefficient;
    for (int i = 0; i < 3; i++)
    {
        degree[i] = monomial.degree[i];
    }
}

CMonomial::CMonomial(double _coefficient, int* _degree)
{
    coefficient = _coefficient;
    for (int i = 0; i < 3; i++)
    {
        degree[i] = _degree[i];
    }
}

CMonomial::~CMonomial()
{
}


std::string CMonomial::toString()
{
    std::stringstream ss;

    ss << coefficient;
    if (degree[0] != 0)
        ss << "x^" << degree[0] << "*";
    if (degree[1] != 0)
        ss << "y^" << degree[1] << "*";
    if (degree[2] != 0)
        ss << "z^" << degree[2] << " ";
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
    if (checkequality(_monomial))

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

CPolynomial::CPolynomial(const CPolynomial& _polynomial)
{
    list.cpy(_polynomial.list);
}

CPolynomial::CPolynomial(CList<CMonomial> _list)
{
    list.cpy(_list);
}

std::string CPolynomial::toString()
{
    std::ostringstream oss;
    bool first = true;
    CList<CMonomial> cpylist;
    cpylist.cpy(list);
    while(!cpylist.isEmpty())
    {
        CMonomial monom;
        monom = cpylist.pop_back();
        if(!first && monom.getcoefficient() >= 0)
        {
            oss << "+ ";
        }
        first = false;
        oss << monom.toString();
    }
    return oss.str();
}

bool CPolynomial::operator==(CPolynomial _polynomial)
{

    CList<CMonomial> cpy;
    cpy.cpy(list);
    bool equal = false;
    for (int i = 0; i < cpy.size; i++) {
        if (cpy.remove(i) == _polynomial.list.remove(i))
            equal = true;
        else
        {
            equal = false;
            break;
        }
    }
    return equal;
}

bool CPolynomial::operator!=(CPolynomial _polynomial)
{
    CList<CMonomial> cpy;
    cpy.cpy(list);
    bool equal = false;
    for (int i = 0; i < cpy.size; i++) {
        if (cpy.remove(i) == _polynomial.list.remove(i))
            equal = true;
        else
        {
            equal = false;
            break;
        }
    }
    return !equal;
}

double CPolynomial::findResult(double _x, double _y, double _z)
{
    double result = 0;
    CList<CMonomial> cpylist;
    cpylist.cpy(list);
    while (!cpylist.isEmpty())
    {
        CMonomial monom;
        monom = cpylist.pop_back();
        double coef = monom.getcoefficient();
        int x = monom.degree[0];
        int y = monom.degree[1];
        int z = monom.degree[2];
        result += coef * pow(_x, x) * pow(_y, y) * pow(_z, z);
    }
    return result;
}

void CPolynomial::Parse(std::string _string)
{
    CList<CMonomial> new_list;
    int pos = 0;
    while (pos < _string.size()) {
        CMonomial new_monomial;
        bool is_negative = false;
        if (_string[pos] == '+') {
            pos++;
        }
        else if (_string[pos] == '-') {
            is_negative = true;
            pos++;
        }
        if (_string[pos] >= '0' && _string[pos] <= '9') {
            std::string coef_str;
            while (pos < _string.size() && ((_string[pos] >= '0' && _string[pos] <= '9') || _string[pos] == '.')) {
                coef_str += _string[pos];
                pos++;
            }
            new_monomial.coefficient = stod(coef_str);
        }
        else if (_string[pos] == 'x' || _string[pos] == 'y' || _string[pos] == 'z') {
            new_monomial.coefficient = is_negative ? -1 : 1;
        }
        if (pos < _string.size() && _string[pos] == 'x') {
            pos++;
            if (pos < _string.size() && _string[pos] == '^') {
                pos++;
                int x_degree = 0;
                while (pos < _string.size() && _string[pos] >= '0' && _string[pos] <= '9') {
                    x_degree = x_degree * 10 + (_string[pos] - '0');
                    pos++;
                }
                new_monomial.degree[0] = x_degree;
            }
            else {
                new_monomial.degree[0] = 1;
            }
        }
        if (pos < _string.size() && _string[pos] == 'y') {
            pos++;
            if (pos < _string.size() && _string[pos] == '^') {
                pos++;
                int y_degree = 0;
                while (pos < _string.size() && _string[pos] >= '0' && _string[pos] <= '9') {
                    y_degree = y_degree * 10 + (_string[pos] - '0');
                    pos++;
                }
                new_monomial.degree[1] = y_degree;
            }
            else {
                new_monomial.degree[1] = 1;
            }
        }
        if (pos < _string.size() && _string[pos] == 'z') {
            pos++;
            if (pos < _string.size() && _string[pos] == '^') {
                pos++;
                int z_degree = 0;
                while (pos < _string.size() && _string[pos] >= '0' && _string[pos] <= '9') {
                    z_degree = z_degree * 10 + (_string[pos] - '0');
                    pos++;
                }
                new_monomial.degree[2] = z_degree;
            }
            else {
                new_monomial.degree[2] = 1;
            }
        }
        new_list.push_back(new_monomial);
    }
    list = new_list;
}

CPolynomial CPolynomial::operator+(CMonomial _monomial)
{
    CList<CMonomial> new_list;
    new_list.cpy(list);
    
    CList<CMonomial> cpy;
    cpy.cpy(list);
    while (!cpy.isEmpty()) {
        CMonomial monom;
        monom = cpy.pop_back();
        while (monom.degree[0] << _monomial.degree[0] ||
            (monom.degree[0] == _monomial.degree[0] && monom.degree[1] < _monomial.degree[1]) ||
            (monom.degree[0] == _monomial.degree[0] && monom.degree[1] == _monomial.degree[1] && monom.degree[2] < _monomial.degree[2])) {
            monom = cpy.pop_back();
        }
        if (!cpy.isEmpty() && (monom.degree[0] == _monomial.degree[0] && monom.degree[1] == _monomial.degree[1] && monom.degree[2] == _monomial.degree[2])) {
            monom = monom + _monomial;
        }
        else {
            new_list.push_back(_monomial);
        }
    }
    return CPolynomial(new_list);
}

CPolynomial CPolynomial::operator-(CMonomial _monomial)
{
    CList<CMonomial> new_list;
    new_list.cpy(list);

    CList<CMonomial> cpy;
    cpy.cpy(list);
    while (!cpy.isEmpty()) {
        CMonomial monom;
        monom = cpy.pop_back();
        while (monom.degree[0] << _monomial.degree[0] ||
            (monom.degree[0] == _monomial.degree[0] && monom.degree[1] < _monomial.degree[1]) ||
            (monom.degree[0] == _monomial.degree[0] && monom.degree[1] == _monomial.degree[1] && monom.degree[2] < _monomial.degree[2])) {
            monom = cpy.pop_back();
        }
        if (!cpy.isEmpty() && (monom.degree[0] == _monomial.degree[0] && monom.degree[1] == _monomial.degree[1] && monom.degree[2] == _monomial.degree[2])) {
            monom = monom - _monomial;
        }
        else {
            new_list.push_back(_monomial);
        }
    }
    return CPolynomial(new_list);
}

CPolynomial CPolynomial::operator*(CMonomial _monomial)
{
    CList<CMonomial> new_list;
    CList<CMonomial> cpylist;
    cpylist.cpy(list);
    while (!cpylist.isEmpty())
    {
        CMonomial monom;
        CMonomial newmonom;
        monom = cpylist.pop_back();
        newmonom = monom * _monomial;
        if (newmonom.getcoefficient() != 0) {
            new_list.push_back(newmonom);
        }
    }
    return CPolynomial(new_list);
}

CPolynomial CPolynomial::operator/(CMonomial _monomial)
{
    CList<CMonomial> new_list;
    CList<CMonomial> cpylist;
    cpylist.cpy(list);
    while (!cpylist.isEmpty())
    {
        CMonomial monom;
        CMonomial newmonom;
        monom = cpylist.pop_back();
        newmonom = monom / _monomial;
        if (newmonom.getcoefficient() != 0) {
            new_list.push_back(newmonom);
        }
    }
    return CPolynomial(new_list);
}

CPolynomial& CPolynomial::operator=(CPolynomial& _polynomial)
{
    list.cpy(_polynomial.list);
    return *this;
}


CPolynomial CPolynomial::operator+(CPolynomial _polynomial) {
    CList<CMonomial> new_list;
    CList<CMonomial> cpy;
    cpy.cpy(list);
    while (!cpy.isEmpty() && !_polynomial.list.isEmpty())
    {
        CMonomial monom1;
        CMonomial monom2;
        monom1 = cpy.pop_back();
        monom2 = _polynomial.list.pop_back();
        if(monom1.degree[0] > monom2.degree[0] || 
            (monom1.degree[0] == monom2.degree[0] && monom1.degree[1] > monom2.degree[1]) && 
            (monom1.degree[0] == monom2.degree[0] && monom1.degree[1] == monom2.degree[1] && 
                monom1.degree[2] > monom2.degree[2]))
        {
            new_list.push_back(monom1);
        }
        else if(monom1.degree[0] < monom2.degree[0] || 
            (monom1.degree[0] == monom2.degree[0] && monom1.degree[1] < monom2.degree[1]) && 
            (monom1.degree[0] == monom2.degree[0] && monom1.degree[1] == monom2.degree[1] && 
                monom1.degree[2] < monom2.degree[2]))
        {
            new_list.push_back(monom2);
        }else
        {
            CMonomial monom3 = monom1 + monom2;
            if(monom3.getcoefficient() != 0)
            {
                new_list.push_back(monom3);
            }
        }
        
    }
    while (!cpy.isEmpty())
    {
        CMonomial monom1;
        monom1 = cpy.pop_back();
        new_list.push_back(monom1);
    }
    while (!_polynomial.list.isEmpty())
    {
        CMonomial monom2;
        monom2 = _polynomial.list.pop_back();
        new_list.push_back(monom2);
    }
    return CPolynomial(new_list);
}

CPolynomial CPolynomial::operator-(CPolynomial _polynomial)
{
    CList<CMonomial> new_list;
    CList<CMonomial> cpy;
    cpy.cpy(list);
    while (!cpy.isEmpty() && !_polynomial.list.isEmpty())
    {
        CMonomial monom1;
        CMonomial monom2;
        monom1 = cpy.pop_back();
        monom2 = _polynomial.list.pop_back();
        if (monom1.degree[0] > monom2.degree[0] ||
            (monom1.degree[0] == monom2.degree[0] && monom1.degree[1] > monom2.degree[1]) &&
            (monom1.degree[0] == monom2.degree[0] && monom1.degree[1] == monom2.degree[1] &&
                monom1.degree[2] > monom2.degree[2]))
        {
            new_list.push_back(monom1);
        }
        else if (monom1.degree[0] < monom2.degree[0] ||
            (monom1.degree[0] == monom2.degree[0] && monom1.degree[1] < monom2.degree[1]) &&
            (monom1.degree[0] == monom2.degree[0] && monom1.degree[1] == monom2.degree[1] &&
                monom1.degree[2] < monom2.degree[2]))
        {
            
            CMonomial monom3 = monom2;
            monom3.coefficient = -monom3.coefficient;
            new_list.push_back(monom3);
        }else
        {
            CMonomial monom3 = monom1;
            monom3.coefficient = monom3.coefficient - monom2.coefficient;
            if(monom3.getcoefficient() != 0)
            {
                new_list.push_back(monom3);
            }
        }
    }
    while(!cpy.isEmpty())
    {
        CMonomial monom1;
        monom1 = cpy.pop_back();
        new_list.push_back(monom1);
    }
    while (!_polynomial.list.isEmpty())
    {
        CMonomial monom2;
        monom2 = _polynomial.list.pop_back();
        monom2.coefficient = -monom2.coefficient;
        new_list.push_back(monom2);
    }
    return CPolynomial(new_list);
}

#pragma endregion