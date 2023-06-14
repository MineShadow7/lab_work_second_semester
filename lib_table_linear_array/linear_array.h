#ifndef LIB_TABLELINEARARRAY_TABLE_H_
#define LIB_TABLELINEARARRAY_TABLE_H_

#include "../lib_i_table/table.h"
#include "../lib_polynomial/polynomial.h"

template<typename Type>
class CLinearTableArray {
 private:
	Type* data;
	int size;
	int capacity;
 public:
	 CLinearTableArray() {
		 size = 0;
		 capacity = 20;
		 data = new Type[capacity];
	 }
	 void insert(Type obj) {
		 if (size < capacity) {
			 data[size].first = obj.first;
			 data[size].second = obj.second;
			 size++;
		 }
		 else {
			 int new_capacity = capacity * 2;
			 Type* new_data = new Type[new_capacity];
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
	 void remove(Type obj) {
		 for (int i = 0; i < size; i++) {
			 if (data[i].first == obj.first) {
				 for (int j = i; j < size - 1; j++) {
					 data[j].first = data[j + 1].first;
					 data[j].second = data[j + 1].second;
				 }
				 size--;
				 if (size == 0) {
					 delete[] data;
					 data = new Type[capacity];
				 }
				 break;
			 }
		 }
	}
	 Type find(std::string key) {
		 for (int i = 0; i < size; i++)
			 if (key == data[i].first)
				 return data[i];
	}
	bool contains(Type obj) {
		for (int i = 0; i < size; i++) {
			if (data[i].first == obj.first) {
				return true;
			}
		}
		return false;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			std::cout << data[i].first << "      " << data[i].second.toString() << std::endl;
		}
	}

	std::string printstring() {
		std::string res;
		for (int i = 0; i < size; i++) {
			res += data[i].first + "      " + data[i].second.toString() + "\n";
		}
		return res;
	}

	int getsize() {
		return size;
	}
};

#endif
