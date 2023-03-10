// Copyright 2022 Vinokurov Ivan

#ifndef LIB_LSQ_LSQ_H_
#define LIB_LSQ_LSQ_H_

#include "../lib_list/list.h"
#include <iostream>

template <class Type> class Stack;
template <class Type> class Queue;
template <class Type> class QueuePrIn;
template <class Type> class QueuePrOut;

template <class Type>
class Stack {
private:
    CList<Type> list;
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
    }
    ~Stack() {
        top1 = -1;
        size = 0;
    }
    void push(const Type& val) {
        if (!isFull()) {
            top1++;
            list.push_back(val);
        }
        else {
            throw std::logic_error("ERROR in PUSH: Stack is full!");
        }
    }
    Type pop() {
        Type val;
        if (!isEmpty()) {
            val = list.pop_back();
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
        CList<Type> temp;
        temp = list;
        Type val = temp.pop_back();
        return val;
    }
};

template <class Type>
class Queue {
private:
    CList<Type> list;
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
    }
    ~Queue() {
        top1 = 0;
        end = -1;
        size = 0;
    }
    void push(const Type& val) {
        if (!isFull()) {
            end++;
            list.push_front(val);
        }
        else {
            if (isFull() && top1 != 0) {
                end = size - top1;
                list.push_front(val);
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
            val = list.pop_back();
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
        CList<Type> temp;
        temp = list;
        Type val = temp.pop_back();
        return val;
    }
};

template <class Type>
class QueuePrIn {
private:
    CList<std::pair<Type, int>> list;
    int top1;
    int size;
    int end;
public:
    bool isFull() { if (end == size - 1) { return true; } else { return false; } };
    bool isEmpty() { if (end - top1 < 0) { return true; } else { return false; } };
    QueuePrIn(int _size) {
        if (_size < 1) {
            throw std::logic_error("Size can't be lower than 1");
        }
        size = _size;
        top1 = 0;
        end = -1;
    }
    ~QueuePrIn() {
        top1 = 0;
        end = -1;
        size = 0;
    }
    void push(const std::pair<Type, int>& val) {
        CList<std::pair<Type, int>> tempList;
        std::pair<Type, int> tempVal;
        int i = -1;
        tempList.cpy(list);
        if (!isFull()) {
            if (val.second == 1) {
                list.push_back(val);
            }
            else if (val.second == 2 && isEmpty() || val.second == 3 && isEmpty()) {
                list.push_back(val);
            }
            else if (val.second == 3) {
                list.push_front(val);
            }
            else if (val.second > tempVal.second) {
                while (val.second > tempVal.second && !tempList.isEmpty()) {
                    tempVal = tempList.pop_back();
                    i++;
                }
                list.insert(i, val);
            }
            else {
                list.push_front(val);
            }
            end++;
        }
        else {
            if (isFull() && top1 != 0) {
                end = size - top1;
                list.push_front(val);
                top1 = 0;
            }
            else {
                throw std::logic_error("ERROR in PUSH: Queue is full!");
            }
        }
    }
    std::pair<Type, int> pop() {

        std::pair<Type, int> val;
        if (!isEmpty()) {
            val = list.pop_back();
            top1++;
        }
        else {
            throw std::logic_error("ERROR in POP: Queue is empty!");
        }

        return val;
    }
    std::pair<Type, int> top() {
        if (isEmpty()) {
            throw std::logic_error("ERROR in TOP: Queue is Empty!");
        }
        CList<std::pair<Type, int>> temp;
        temp = list;
        std::pair<Type, int> val = temp.pop_back();
        return val;
    }
};

template <class Type>
class QueuePrOut {
private:
    CList<std::pair<Type, int>> list;
    int top1;
    int size;
    int end;
public:
    bool isFull() { if (end == size - 1) { return true; } else { return false; } };
    bool isEmpty() { if (end - top1 < 0) { return true; } else { return false; } };
    QueuePrOut(int _size) {
        if (_size < 1) {
            throw std::logic_error("Size can't be lower than 1");
        }
        size = _size;
        top1 = 0;
        end = -1;
    }
    ~QueuePrOut() {
        top1 = 0;
        end = -1;
        size = 0;
    }
    void push(const std::pair<Type, int>& val) {
        if (!isFull()) {
            end++;
            list.push_front(val);
        }
        else {
            if (isFull() && top1 != 0) {
                end = size - top1;
                list.push_front(val);
                top1 = 0;
            }
            else {
                throw std::logic_error("ERROR in PUSH: Queue is full!");
            }
        }
    }
    std::pair<Type, int> pop() {
        int _i = -1;
        std::pair<Type, int> val;
        if (!isEmpty()) {
            CList<std::pair<Type, int>> tempList;
            std::pair<Type, int> tempVal;
            tempVal = std::make_pair(0, 0);
            tempList.cpy(list);
            while (!tempList.isEmpty() && tempVal.second != 1) {
                tempVal = tempList.pop_back();
                _i++;
                if (tempVal.second == 1) {
                    val = list.remove(_i);
                    top1++;
                    return val;
                }
            }
            _i = -1;
            tempVal = std::make_pair(0, 0);
            tempList.cpy(list);
            while (!tempList.isEmpty() && tempVal.second != 2) {
                tempVal = tempList.pop_back();
                _i++;
                if (tempVal.second == 2) {
                    val = list.remove(_i);
                    top1++;
                    return val;
                }
            }
            _i = -1;
            tempVal = std::make_pair(0, 0);
            tempList.cpy(list);
            while (!tempList.isEmpty() && tempVal.second != 3) {
                tempVal = tempList.pop_back();
                _i++;
                if (tempVal.second == 3) {
                    val = list.remove(_i);
                    top1++;
                    return val;
                }
            }
        }
        else {
            throw std::logic_error("ERROR in POP: Queue is empty!");
        }

        return val;
    }
    std::pair<Type, int> top() {
        if (isEmpty()) {
            throw std::logic_error("ERROR in TOP: Queue is Empty!");
        }
        CList<std::pair<Type, int>> temp;
        temp = list;
        std::pair<Type, int> val = temp.pop_back();
        return val;
    }
};

#endif