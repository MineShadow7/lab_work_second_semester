// Copyright 2022 Vinokurov Ivan

#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

#include "../lib_i_datastructure/data_structure.h"
#include <iostream>

template <class Type> class Stack;

template <class Type>
class Stack : public DataStructure<Type> {
private:
    Type* data;
    int top1;
    int size;

public:
    bool isFull() { if (top1 == size - 1) { return true; } else { return false; } };
    bool isEmpty() { if (top1 == -1) { return true; } else { return false; } };
    Stack(int _size) {
        if (_size < 1) {
            throw std::logic_error("Size can't be lower than 1");
        }
        size = _size;
        top1 = -1;
        data = new Type[size];
    }
    Stack() {
        size = 1;
        top1 = -1;
        data = new Type[size];
    }
    ~Stack() {
        delete[] data;
        top1 = -1;
        size = 0;
    }
    void push(const Type& val) {
        if (!isFull()) {
            top1++;
            data[top1] = val;
        }
        else {
            throw std::logic_error("ERROR in PUSH: Stack is full!");
        }
    }
    Type pop() {
        Type val;
        if (!isEmpty()) {
            val = data[top1];
            top1--;
        }
        else {
            throw std::logic_error("ERROR in POP: Stack is empty!");
        }

        return val;
    }
    Type top() {
        if (isEmpty()) {
            throw std::logic_error("ERROR in TOP: Stack is Empty!");
        }
        return data[top1];
    }
};

#endif