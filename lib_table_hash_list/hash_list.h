#ifndef LIB_TABLEHASHLIST_TABLE_H_
#define LIB_TABLEHASHLIST_TABLE_H_
#define SIZE 20
#include "../lib_i_table/table.h"
#include "../lib_list/list.h"
#include "../lib_polynomial/polynomial.h"

template<typename Type>
class CHashTableList {
private:
    CList<Type> arr[SIZE];

    size_t hashFunction(const Type& obj) const {
        return std::hash<std::string>{}(obj.first) % SIZE;
    }

public:
    void insert(Type obj) {

        int key = hashFunction(obj);

        arr[key].push_back(obj);
    }
    bool contains(Type obj) {

        int key = hashFunction(obj);

        CList<Type>* arrTemp = new CList<Type>();
        arrTemp->cpy(arr[key]);
        while (!arrTemp->isEmpty()) {
            Type tempData;
            tempData = arrTemp->pop_back();
            if (tempData == obj) {
                return true;
            }
        }
        return false;
    }
    Type find(std::string key) {
        CList<Type>* arrTemp = new CList<Type>();
        arrTemp->cpy(arr[key]);
        while (!arrTemp->isEmpty()) {
            Type tempData;
            tempData = arrTemp->pop_back();
            if (tempData == obj) {
                return tempData;
            }
        }
        throw std::out_of_range("Key not found");
    }
    void remove(Type obj) {
        int key = hashFunction(obj);
        int index = 0;
        CList<Type>* arrTemp = new CList<Type>();
        arrTemp->cpy(arr[key]);
        while (!arrTemp->isEmpty()) {
            if (arrTemp->pop_back() == obj) {
                break;
            }
            index++;
        }
        arr[key].remove(index);
    }
};

#endif
