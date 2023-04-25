#ifndef LIB_TABLELINEARARRAY_TABLE_H_
#define LIB_TABLELINEARARRAY_TABLE_H_
#include "../lib_i_table/table.h"
#include "../lib_polynomial/polynomial.h"

class CLinearTableArray {
 private:
	std::pair<CPolynomial, int>* data;
	int size;
	int capacity;
 public:
	 CLinearTableArray() {
		 size = 0;
		 capacity = 20;
		 data = new std::pair<CPolynomial, int>[capacity];
	 }
	 void insert(std::pair<CPolynomial, int> obj) {
		 if (size < capacity) {
			 data[size].first = obj.first;
			 data[size].second = obj.second;
			 size++;
		 }
		 else {
			 int new_capacity = capacity * 2;
			 std::pair<CPolynomial, int>* new_data = new std::pair<CPolynomial, int>[new_capacity];
			 for (int i = 0; i < size; i++) {
				 new_data[i].first = data[i].first;
				 new_data[i].second = data[i].second;
			 }
			 delete[] data;
			 data = new_data;
			 capacity = new_capacity;
			 data[size].first = obj.first;
			 data[size].second = obj.second;
			 size++;
		 }
	}
	 void remove(std::pair<CPolynomial, int> obj) {
		 for (int i = 0; i < size; i++) {
			 if (data[i].second == obj.second) {
				 for (int j = i; j < size - 1; j++) {
					 data[j].first = data[j + 1].first;
					 data[j].second = data[j + 1].second;
				 }
				 size--;
				 break;
			 }
		 }
	}
	 std::pair<CPolynomial, int> find(int key) {
		 for (int i = 0; i < size; i++)
			 if (key == data[i].second)
				 return data[i];
	}
	bool contains(std::pair<CPolynomial, int> obj) {
		for (int i = 0; i < size; i++) {
			if (data[i] == obj) {
				return true;
			}
		}
		return false;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			std::cout << data[i].first.toString() << " ";
		}
		std::cout << std::endl;
	}
};

#endif
