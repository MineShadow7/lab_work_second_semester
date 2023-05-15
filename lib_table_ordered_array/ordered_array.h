#ifndef LIB_TABLEORDEREDARRAY_TABLE_H_
#define LIB_TABLEORDEREDARRAY_TABLE_H_

#include "../lib_i_table/table.h"
#include "../lib_polynomial/polynomial.h"

template<typename Type>
class COrderedTableArray{
private:
	Type* data;
	int size;
	int capacity;
	int stringToInt(std::string _str) {
		int tempInt = 0;
		for (int i = 0; i < _str.size(); i++) {
			tempInt += _str[i];
		}
		return tempInt;
	}
public:
	COrderedTableArray() {
		size = 0;
		capacity = 20;
		data = new Type[capacity];
	}
	void insert(Type obj) {
		if (size < capacity) {
			int i = size - 1;
			while (i >= 0 && stringToInt(data[i].first) > stringToInt(obj.first)) {
				data[i + 1].first = data[i].first;
				data[i + 1].second = data[i].second;
				i--;
			}
			data[i + 1].first = obj.first;
			data[i + 1].second = obj.second;
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
			int i = size - 1;
			while (i >= 0 && stringToInt(data[i].first) > stringToInt(obj.first)) {
				data[i + 1].first = data[i].first;
				data[i + 1].second = data[i].second;
				i--;
			}
			data[i + 1].first = obj.first;
			data[i + 1].second = obj.second;
			size++;
		}
	}
	void remove(Type obj) {
		int i = 0;
		while (i < size && data[i].second != obj.second) {
			i++;
		}
		if (i < size) {
			for (int j = i; j < size - 1; j++) {
				data[j].first = data[j + 1].first;
				data[j].second = data[j + 1].second;
			}
			size--;
		}
	}
	Type find(std::string key) {
		int left = 0;
		int right = size - 1;
		while (left <= right) {
			int middle = (left + right) / 2;
			if (data[middle].first == key) {
				return data[middle];
			}
			else if (stringToInt(data[middle].first) < stringToInt(key)) {
				left = middle + 1;
			}
			else {
				right = middle - 1;
			}
		}
		return data[key];
	}
	bool contains(Type obj) {
		int left = 0;
		int right = size - 1;
		while (left <= right) {
			int middle = (left + right) / 2;
			if (data[middle].first == obj.first) {
				return true;
			}
			else if (stringToInt(data[middle].first) < stringToInt(obj.first)) {
				left = middle + 1;
			}
			else {
				right = middle - 1;
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
};

#endif
