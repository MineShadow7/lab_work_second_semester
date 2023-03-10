#ifndef LIB_STACK_QUEUE_H_
#define LIB_STACK_QUEUE_H_

#include "../lib_datastructure/data_structure.h"
#include <iostream>

template <class Type> class Queue;

template <class Type>
class Queue : public DataStructure<Type> {
private:
    Type* data;
    int top1;
    int size;
    int end;

public:
    bool isFull() { if (end == size - 1) { return true; } else { return false; } };
    bool isEmpty() { if (end - top1 < 0) { return true; } else { return false; } };
    Queue(int _size) {
        if (_size < 1) {
            throw std::logic_error("Size can't be lower than 1");
        }
        size = _size;
        top1 = 0;
        end = -1;
        data = new Type[size];
    }
    ~Queue() {
        delete[] data;
        top1 = 0;
        end = -1;
        size = 0;
    }
    void push(const Type& val) {
        if (!isFull()) {
            end++;
            data[end] = val;
        }
        else {
            if (isFull() && top1 != 0) {
                for (int i = 0; i < top1; i++) {
                    for (int j = 0; j < size - 1; j++) {
                        data[j] = data[j + 1];
                    }
                }
                end = size - top1;
                data[end] = val;
                top1 = 0;
            }
            else {
                throw std::logic_error("ERROR in PUSH: Queue is full!");
            }
        }
    }
    Type pop() {
        Type val;
        if (!isEmpty()) {
            val = data[top1];
            top1++;
        }
        else {
            throw std::logic_error("ERROR in POP: Queue is empty!");
        }

        return val;
    }
    Type top() {
        if (isEmpty()) {
            throw std::logic_error("ERROR in TOP: Queue is Empty!");
        }
        return data[end];
    }
};

#endif