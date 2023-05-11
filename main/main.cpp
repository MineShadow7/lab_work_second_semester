// Copyright 2022 Marina Usova

#include <stdio.h>
#include <string>

#include "hash_vector.h"
#include "../lib_polynomial/polynomial.h"
#include "../lib_table_linear_list/linear_list.h"


int main() {

    // Testing Monoms.
    int* deg = new int(3);
    deg[0] = 1;
    deg[1] = 2;
    deg[2] = 3;
    double coef = 3.0;
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



    // Создаем объект таблицы и тестовые объекты
    CLinearTableList<CPolynomial> table;

    double coef1 = 4;
    int* deg1 = new int(3);
    deg1[0] = 1;
    deg1[1] = 2;
    deg1[2] = 3;

    double coef2 = 5;
    int* deg2 = new int(3);
    deg2[0] = 4;
    deg2[1] = 5;
    deg2[2] = 6;

    double coef3 = 6;
    int* deg3 = new int(3);
    deg3[0] = 7;
    deg3[1] = 8;
    deg3[2] = 9;


    CMonomial testmonom1(coef1, deg1);
    CMonomial testmonom2(coef2, deg2);
    CMonomial testmonom3(coef3, deg3);


    CList<CMonomial> list1;
    CList<CMonomial> list2;
    CList<CMonomial> list3;
    list1.push_back(testmonom1);
    list2.push_back(testmonom2);
    list3.push_back(testmonom3);

    CPolynomial polynomial1(list1);
    CPolynomial polynomial2(list2);
    CPolynomial polynomial3(list3);

    std::cout << polynomial1.toString() << std::endl;
    std::cout << polynomial2.toString() << std::endl;
    std::cout << polynomial3.toString() << std::endl;


    // Вставляем элементы

    table.insert(polynomial1);
    table.insert(polynomial2);
    table.insert(polynomial3);


    if (table.contains(polynomial1)) {
        std::cout << "Found object 1!" << std::endl;
    }
    else
        std::cout << "Couldn't find object 1..." << std::endl;

    // Удаляем элемент

    table.remove(polynomial2);

    // Ищем элемент по ключу
    try {
        CPolynomial found = table.find(polynomial2.toString());
        std::cout << found.toString() << std::endl;
    }
    catch (const std::out_of_range) {
        std::cout << "Caught and Exception, code works as intendent." << std::endl;
    }

    CHashTableMix<CPolynomial> MyHashTable2(20);

    // Заполняем таблицу значениями

    MyHashTable2.insert(polynomial1);
    MyHashTable2.insert(polynomial2);
    MyHashTable2.insert(polynomial3);

    // Найти полином 1 и вывести его значение 4x^1 * y^2 * z^3
    CPolynomial value = MyHashTable2.find(polynomial1.toString());
    std::cout << "Value of polinomial1 is " << value.toString() << std::endl;

    // Удалить полином 2. Его больше не должно быть в таблице
    MyHashTable2.remove(polynomial2);

    // Проверяем есть ли в таблице полином 2. Его не должно быть в таблице
    if (MyHashTable2.contains(polynomial2)) {
        std::cout << "Polinom 2 is in the table" << std::endl;
    }
    else {
        std::cout << "Polinom 2 is not in the table" << std::endl;
    }

    CPolynomial test;
    std::string expression = "(2x^2y) + (3x^2yz) + (4xy^2)";
    test.Parse(expression);
    std::cout << test.toString() << std::endl;
    std::cout << test.findResult(2, 3, 4, expression) << std::endl;


    //Example of inner workings of Polynomial. Basic HOW-TO-DO-WORK with it.
    std::string userstring = "(2x^2y) + (3x^2yz) + (4xy^2)";
    double x, y, z;
    std::cout << "Hello! Let's calculate Polynomial strings. Format of string: (Monomial expr) +-*/ (Monomial expr) +-*/ ..." << std::endl;
    std::cout << "Your Polynomial string: " << userstring;
    CPolynomial usertest;
    usertest.Parse(userstring);
    std::cout << std::endl << "This is how the class contains the Monoms of string Polynomial: " << usertest.toString() << std::endl;
    std::cout << "Now let's calculate the result of said Polynomial string: " << std::endl;
    std::cout << "Input x: ";
    std::cin >> x;
    std::cout << std::endl;
    std::cout << "Input y: ";
    std::cin >> y;
    std::cout << std::endl;
    std::cout << "Input z: ";
    std::cin >> z;
    std::cout << std::endl;
    std::cout << "The result of " << userstring << " In point " << x << " " << y << " " << z << " " << "is: " << usertest.findResult(x, y, z, userstring);
    return 0;
}
