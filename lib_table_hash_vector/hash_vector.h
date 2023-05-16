#ifndef LIB_TABLEHASHVECTOR_TABLE_H_
#define LIB_TABLEHASHVECTOR_TABLE_H_
#include <iostream>
#include <string>
#include "../lib_i_table/table.h"
#include "../lib_polynomial/polynomial.h"

template<typename Type>
class CHashTableMix : public ITable<Type> {
private:
	size_t size;
	std::vector<Type>* data;

	size_t hashFunction(const Type& obj) const {
		return std::hash<std::string>{}(obj.first) % size;
	}
public:
	explicit CHashTableMix(const size_t _size)
	{
		size = _size;
		data = new std::vector<Type>[size];
	}

	~CHashTableMix()
	{
		delete[] data;
	}

	void insert(Type obj) override {
		size_t index = hashFunction(obj);
		Type newpair = obj;
		data[index].push_back(newpair);
	}

	void remove(Type obj) override {
		size_t index = hashFunction(obj);
		std::vector<Type>& vec = data[index];
		for (auto it = vec.begin(); it != vec.end(); ++it) {
			if (it->second == obj.second) {
				vec.erase(it);
				break;
			}
		}
	}

	bool contains(Type obj) override {
		size_t index = hashFunction(obj);
		std::vector<Type>& vec = data[index];
		if (vec.data()->second == obj.second)
		{
			return true;
		}
		return false;
	}

	Type find(std::string key) override {
		for (size_t i = 0; i < size; i++) {
			auto& vec = data[i];
			for (auto& obj : vec) {
				if (obj.first == key) {
					return obj;
				}
			}
		}
		throw std::out_of_range("Key not found");
	}

	void print() {
		std::cout << "Table Hash Vector Mix OBJ & KEY: " << std::endl;
		int polynum = 0;
		for (size_t i = 0; i < size; i++) {
			auto& vec = data[i];
			for (auto& obj : vec) {
				std::cout << "obj" << polynum + 1 << " " << obj.first << "   " << obj.second.toString() << std::endl;
				polynum++;
			}
		}
	}

	std::string printstring() {
		std::string res;
		for (size_t i = 0; i < size; i++) {
			auto& vec = data[i];
			for (auto& obj : vec) {
				res += obj.first;
				res += "      ";
				res += obj.second.toString();
				res += "\n";
			}
		}
		return res;
	}

	int getsize() {
		int ressize = 0;
		for (size_t i = 0; i < size; i++) {
			auto& vec = data[i];
			for (auto& obj : vec) {
				ressize++;
			}
		}
		return ressize;
	}
};

#endif
