#include "../lib_polynomial/polynomial.h"
#include <map>
#include "../lib_stack/stack.h"

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
    for (int i = 0; i < 3; i++)
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

std::string CMonomial::toString()
{
    std::stringstream ss;

    if (coefficient != 0 || coefficient != 1)
        ss << coefficient;
    if (degree[0] != 0)
        ss << "x^" << degree[0];
    if (degree[1] != 0)
        ss << "*" << "y^" << degree[1];
    if (degree[2] != 0)
        ss << "*" << "z^" << degree[2] << " ";
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
    while (!cpylist.isEmpty())
    {
        CMonomial monom;
        monom = cpylist.pop_front();
        if (!first && monom.getcoefficient() >= 0)
        {
            oss << " ";
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

double CPolynomial::findResult(double _x, double _y, double _z, std::string _str)
{
    double result = 0;
    CList<CMonomial> cpylist;
    cpylist.cpy(list);
    int i = 0;
    char op;
    CMonomial monom1;
    CMonomial monom2;
    monom1 = cpylist.pop_front();
    result = countMonom(monom1, _x, _y, _z);
    while (i < _str.size() - 1) {
        while (!isOperator(_str[i]) && i < _str.size() - 1) {
            i++;
        }
        op = _str[i];
        if (!cpylist.isEmpty())
            monom2 = cpylist.pop_front();
        else
            break;
        switch (op)
        {
        case '+':
            result += countMonom(monom2, _x, _y, _z);
            break;
        case '-':
            result -= countMonom(monom2, _x, _y, _z);
            break;
        case '*':
            result *= countMonom(monom2, _x, _y, _z);
            break;
        case '/':
            result += countMonom(monom2, _x, _y, _z);
            break;
        }
        i++;
    }
    return result;
}

void CPolynomial::Parse(std::string _string)
{
    std::stringstream ss(_string);
    std::stack<char> st;
    CMonomial m;
    char c;
    char prevc;
    while (ss >> c) {
        if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            st.pop();
            if (st.empty()) {
                list.push_back(m);
                m = CMonomial();
            }
        }
        else if (isdigit(c)) {
            ss.putback(c);
            double coefficient;
            ss >> coefficient;
            m.coefficient = coefficient;
        }
        else if (isalpha(c)) {
            int index = 0;
            while (isalpha(c)) {
                switch (c) {
                case 'x':
                    index = 0;
                    prevc = c;
                    break;
                case 'y':
                    index = 1;
                    prevc = c;
                    break;
                case 'z':
                    index = 2;
                    prevc = c;
                    break;
                }
                m.degree[index] = m.degree[index] + 1;
                ss >> c;
            }
            ss.putback(c);
        }
        else if (c == '^') {
            int degree = 0;
            ss >> degree;
            int index = 0;
            
            switch (prevc) {
            case 'x':
                index = 0;
                break;
            case 'y':
                index = 1;
                break;
            case 'z':
                index = 2;
                break;
            }
            m.degree[index] = degree; // изменяем степень нужной переменной
        }
    }
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

CPolynomial CPolynomial::operator=(CPolynomial _polynomial)
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
            new_list.push_back(monom2);
        }
        else
        {
            CMonomial monom3 = monom1 + monom2;
            if (monom3.getcoefficient() != 0)
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
        }
        else
        {
            CMonomial monom3 = monom1;
            monom3.coefficient = monom3.coefficient - monom2.coefficient;
            if (monom3.getcoefficient() != 0)
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
        monom2.coefficient = -monom2.coefficient;
        new_list.push_back(monom2);
    }
    return CPolynomial(new_list);
}

CPolynomial CPolynomial::operator*(CPolynomial _polynomial)
{
    CPolynomial result;
    if (list.isEmpty() || _polynomial.list.isEmpty())
    {
        return result;
    }
    CList<CMonomial> cpylist;
    cpylist.cpy(list);
    while (!cpylist.isEmpty() && !_polynomial.list.isEmpty())
    {

        CMonomial monom1;
        CMonomial monom2;
        CMonomial resultmonom;
        monom1 = cpylist.pop_back();
        monom2 = _polynomial.list.pop_back();
        resultmonom = monom1 * monom2;
        result.list.push_back(resultmonom);
    }
    return result;
}

CPolynomial CPolynomial::operator*(double _coefficient)
{
    CPolynomial result = *this;
    CList<CMonomial> cpylist;
    cpylist.cpy(list);
    while (!cpylist.isEmpty())
    {
        CMonomial monom1;
        CMonomial resultmonom;
        monom1 = cpylist.pop_back();
        monom1.coefficient* _coefficient;
        resultmonom = monom1;
        result.list.push_back(resultmonom);
    }
    return result;
}

CPolynomial CPolynomial::operator/(CPolynomial _polynomial)
{
    CPolynomial result;
    if (_polynomial.list.isEmpty())
        throw std::invalid_argument("Division by Zero.");
    if (_polynomial.list.size == 1 &&
        (_polynomial.list.pop_front().degree[0] == 0 &&
            _polynomial.list.pop_front().degree[1] == 0 &&
            _polynomial.list.pop_front().degree[2] == 0))
    {
        CMonomial divMon = _polynomial.list.pop_back();
        CList<CMonomial> cpylist;
        cpylist.cpy(list);
        while (!cpylist.isEmpty())
        {
            CMonomial monom1;
            CMonomial resultmonom;
            monom1 = cpylist.pop_back();
            resultmonom = monom1 / divMon;
            result.list.push_back(resultmonom);
        }
    }
    else
    {
        CPolynomial divident = *this;
        while (divident.list.size > 0 && (divident.list.getHead().degree[0] >= _polynomial.list.getHead().degree[0] &&
            divident.list.getHead().degree[1] >= _polynomial.list.getHead().degree[1] &&
            divident.list.getHead().degree[2] >= _polynomial.list.getHead().degree[2]))
        {
            CMonomial chastnoe = divident.list.pop_back() / _polynomial.list.pop_back();
            result.list.push_back(chastnoe);
            CPolynomial product = _polynomial * chastnoe;
            divident = divident - product;
        }
    }
    return result;
}

CPolynomial CPolynomial::getDerivative(CPolynomial _polynomial)
{
    CPolynomial result = *this;
    CList<CMonomial> cpylist;
    cpylist.cpy(list);
    while (!cpylist.isEmpty())
    {
        CMonomial monom1;
        CMonomial resultmonom;
        monom1 = cpylist.pop_back();
        monom1 = monom1.getDerivative(monom1);
        result.list.push_back(monom1);
    }
    return result;
}

std::string CPolynomial::ToRPN(std::string expression) {
    std::stack<char> s;
    std::string postfix = "";
    std::map<char, int> variables;
    variables['x'] = 1;
    variables['y'] = 2;
    variables['z'] = 3;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') {
            continue;
        }

        if (isdigit(expression[i]) || isVariable(expression[i])) {
            postfix += expression[i];
            continue;
        }

        if (isOperator(expression[i])) {
            while (!s.empty() && s.top() != '(' && GetPrecedence(s.top()) >= GetPrecedence(expression[i])) {
                postfix += s.top();
                s.pop();
            }
            s.push(expression[i]);
            continue;
        }

        if (expression[i] == '(') {
            s.push(expression[i]);
            continue;
        }

        if (expression[i] == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
            continue;
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

double CPolynomial::countMonom(CMonomial monom, double _x, double _y, double _z)
{
    double result = 0;
    double coef = monom.getcoefficient();
    int x = monom.degree[0];
    int y = monom.degree[1];
    int z = monom.degree[2];
    result += coef * pow(_x, x) * pow(_y, y) * pow(_z, z);
    return result;
}


int CPolynomial::GetPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '^') {
        return 3;
    }
    return 0;
}

bool CPolynomial::isVariable(char c) {
    if (c == 'x' || c == 'y' || c == 'z') {
        return true;
    }
    return false;
}

bool CPolynomial::isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        return true;
    }
    return false;
}

#pragma endregion
