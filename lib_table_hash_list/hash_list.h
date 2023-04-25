#ifndef LIB_TABLEHASHLIST_TABLE_H_
#define LIB_TABLEHASHLIST_TABLE_H_
#define SIZE 20
#include "../lib_i_table/table.h"
#include "../lib_list/list.h"
#include "../lib_polynomial/polynomial.h"

class CHashTableList {
private:
    CList<std::pair<CPolynomial, int>> arr[SIZE];

    int hashFunction(std::pair<CPolynomial, int> _data) {
        int key = 0;
        std::string temp = _data.first.toString();
        for (int i = 0; i < temp.size(); i++) {
            key += temp[i];
        }

        key = key % SIZE;

        key = abs(key);

        return key;
    }
public:
    void insert(std::pair<CPolynomial, int> _data) {

        int key = hashFunction(_data);

        arr[key].push_back(_data);
    }
    bool contains(std::pair<CPolynomial, int> _data) {

        int key = hashFunction(_data);

        CList<std::pair<CPolynomial, int>>* arrTemp = new CList<std::pair<CPolynomial, int>>();
        arrTemp->cpy(arr[key]);
        while (!arrTemp->isEmpty()) {
            std::pair<CPolynomial, int> tempData;
            tempData = arrTemp->pop_back();
            if (tempData == _data) {
                return true;
            }
        }
        return false;
    }
    void remove(std::pair<CPolynomial, int> _data) {
        int key = hashFunction(_data);
        int index = 0;
        CList<std::pair<CPolynomial, int>>* arrTemp = new CList<std::pair<CPolynomial, int>>();
        arrTemp->cpy(arr[key]);
        while (!arrTemp->isEmpty()) {
            if (arrTemp->pop_back() == _data) {
                break;
            }
            index++;
        }
        arr[key].remove(index);
    }
};

#endif
