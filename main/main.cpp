// Copyright 2022 Marina Usova

#include <stdio.h>
#include "../lib_polynomial/polynomial.h"


int main() {

    // Testing Monoms.
    int* deg = new int(3);
    deg[0] = 1;
    deg[1] = 2;
    deg[2] = 3;
    double coef = 3;
    CMonomial monom(coef, deg);
    std::cout << monom.toString() << std::endl;

    CMonomial monom2(coef, deg);
    std::cout << monom2.toString() << std::endl;

    if (monom == monom2)
        std::cout << "Equal" << std::endl;
    else
        std::cout << "Not Equal" << std::endl;

    CMonomial monom3;
    std::cout << "Operator +" << std::endl;
    monom3 = monom + monom2;
    std::cout << monom3.toString() << std::endl;

    std::cout << "Operator -" << std::endl;
    monom3 = monom - monom2;
    std::cout << monom3.toString() << std::endl;

    std::cout << "Operator *" << std::endl;
    monom3 = monom * monom2;
    std::cout << monom3.toString() << std::endl;

    std::cout << "Operator /" << std::endl;
    monom3 = monom / monom2;
    std::cout << monom3.toString() << std::endl;

    CMonomial monom4;
    monom4 = monom.getDerivative(monom);
    std::cout << monom4.toString() << std::endl;

    // Testing Polinoms.

    CList<CMonomial> list;
    list.push_back(monom);
    list.push_back(monom2);
    CPolynomial polynom(list);
    std::cout << polynom.toString();

    return 0;
}
