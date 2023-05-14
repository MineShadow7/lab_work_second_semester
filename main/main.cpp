// Copyright 2022 Marina Usova

#include <stdio.h>
#include <string>


#include "hash_vector.h"
#include "../lib_polynomial/polynomial.h"
#include "../lib_table_linear_list/linear_list.h"
#include "../lib_table_tree/tree.h"
#include "../lib_table_hash_list/hash_list.h"
#include "../lib_table_linear_array/linear_array.h"
#include "../lib_table_ordered_array/ordered_array.h"

int main() {
    
    //// Testing Monoms.
    //int* deg = new int(3);
    //deg[0] = 1;
    //deg[1] = 2;
    //deg[2] = 3;
    //double coef = 3;
    //CMonomial monom(coef, deg);
    //std::cout << monom.toString() << std::endl;

    //CMonomial monom2(coef, deg);
    //std::cout << monom2.toString() << std::endl;

    //if (monom == monom2)
    //    std::cout << "Equal" << std::endl;
    //else
    //    std::cout << "Not Equal" << std::endl;

    //CMonomial monom3;
    //std::cout << "Operator +" << std::endl;
    //monom3 = monom + monom2;
    //std::cout << monom3.toString() << std::endl;

    //std::cout << "Operator -" << std::endl;
    //monom3 = monom - monom2;
    //std::cout << monom3.toString() << std::endl;

    //std::cout << "Operator *" << std::endl;
    //monom3 = monom * monom2;
    //std::cout << monom3.toString() << std::endl;

    //std::cout << "Operator /" << std::endl;
    //monom3 = monom / monom2;
    //std::cout << monom3.toString() << std::endl;

    //CMonomial monom4;
    //monom4 = monom.getDerivative(monom);
    //std::cout << monom4.toString() << std::endl;

    //// Testing Polinoms.

    //CList<CMonomial> list;
    //list.push_back(monom);
    //list.push_back(monom2);
    //CPolynomial polynom(list);
    //std::cout << polynom.toString();
    //

    
    // Ñîçäàåì îáúåêò òàáëèöû
    CLinearTableList<std::pair<std::string, int>> table;

    // Âñòàâëÿåì ýëåìåíòû
    table.insert(std::pair<std::string, int>("key1", 12));
    table.insert(std::pair<std::string, int>("key2", 13));
    table.insert(std::pair<std::string, int>("key3", 14));

    std::pair<std::string, int> objtofind("key1", 12);
    if (table.contains(objtofind)) {
        std::cout << "Found object 1!" << std::endl;
    }else
        std::cout << "Couldn't find object 1..." << std::endl;

    // Óäàëÿåì ýëåìåíò
    std::pair<std::string, int> objtoremove("key2", 13);
    table.remove(objtoremove);

    // Èùåì ýëåìåíò ïî êëþ÷ó
    try {
        const std::pair<std::string, int> found = table.find("key2");
        std::cout << found.first << " " << found.second << std::endl;
    }
    catch (const std::out_of_range) {
        std::cout << "Caught and Exception, code works as intendent." << std::endl;
    }

    CHashTableMix<std::pair<std::string, int>> MyHashTable1(10);

    std::pair<std::string, int> obj1("key1", 13);
    std::pair<std::string, int> obj2("key2", 14);
    std::pair<std::string, int> obj3("key3", 15);
    
    MyHashTable1.insert(obj1);
    MyHashTable1.insert(obj2);
    MyHashTable1.insert(obj3);

    std::cout << "Value for key 1: " << MyHashTable1.find("key1").second << std::endl;
    std::cout << "Value for key 2: " << MyHashTable1.find("key2").second << std::endl;
    std::cout << "Value for key 3: " << MyHashTable1.find("key3").second << std::endl;

    MyHashTable1.remove(obj2);

    try {
        std::cout << "Value for key 15 after removal: " << MyHashTable1.find("key2").second << std::endl;

    }
    catch (const std::out_of_range) {
        std::cout << "Caught and Exception, code works as intendent." << std::endl;
    }

    
    CHashTableMix<std::pair<std::string, int>> MyHashTable2(20);

    // Äîáàâëÿåì íåñêîëüêî ýëåìåíòîâ
    std::pair<std::string, int> obj4("apple", 5);
    std::pair<std::string, int> obj5("banana", 3);
    std::pair<std::string, int> obj6("orange", 7);
    MyHashTable2.insert(obj4);
    MyHashTable2.insert(obj5);
    MyHashTable2.insert(obj6);

    // Ïîëó÷àåì çíà÷åíèå ïî êëþ÷ó
    std::pair<std::string, int> value = MyHashTable2.find("banana");
    std::cout << "Value of banana is " << value.second << std::endl;

    // Óäàëÿåì ýëåìåíò ïî êëþ÷ó
    MyHashTable2.remove(std::make_pair(std::string("orange"), 0));

    // Ïðîâåðÿåì, åñòü ëè ýëåìåíò â òàáëèöå
    if (MyHashTable2.contains(std::make_pair(std::string("orange"), 0))) {
        std::cout << "Orange is in the table" << std::endl;
    }
    else {
        std::cout << "Orange is not in the table" << std::endl;
    }

    //CTreeTable<std::pair<std::string, int>> tree;
    //std::pair<std::string, int> temp1{ "a", 1 };
    //std::pair<std::string, int> temp2{"b", 2 };
    //std::pair<std::string, int> temp3{ "c", 2 };
    //std::pair<std::string, int> temp4{ "d", 3 };
    //tree.insert(temp1);
    //tree.insert(temp2);
    //tree.insert(temp4);
    //tree.insert(temp3);
    //if (tree.contain(temp3)) {
    //    std::cout << "we are back" << std::endl;
    //}
    //else {
    //    std::cout << "it's over" << std::endl;
    //}
    //CPolynomial polynomial;
    //polynomial.Parse("(2x) + (2y^2)");
    //CLinearTableList<std::pair<std::string, CPolynomial>> tree;
    //std::pair<std::string, CPolynomial> temp1{ "a", polynomial };
    //std::pair<std::string, CPolynomial> temp2{"b", polynomial };
    //std::pair<std::string, CPolynomial> temp3{ "c", polynomial };
    //std::pair<std::string, CPolynomial> temp4{ "d", polynomial };
    //tree.insert(temp1);
    //tree.insert(temp2);
    //tree.insert(temp4);
    //tree.insert(temp3);
    //if (tree.contains(temp3)) {
    //    std::cout << "we are back" << std::endl;
    //}
    //else {
    //    std::cout << "it's over" << std::endl;
    //}

    //tree.print();

    CPolynomial test;
    std::string expression = "(-2x^2y) - (3x^2yz)";
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
