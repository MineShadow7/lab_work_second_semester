#ifndef LIB_TABLEHASHVECTOR_TABLE_H_
#define LIB_TABLEHASHVECTOR_TABLE_H_
#include <iostream>
#include <string>
#include "../lib_i_table/table.h"

template<typename Type>
class CHashTableMix : public ITable<Type> {
private:
	size_t size;
	std::vector<Type>* data;

	size_t hashFunction(const std::string& obj) const {
		return std::hash<std::string>{}(obj) % size;
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
		size_t index = hashFunction(obj.second.toString());
		Type newpair = obj;
		data[index].push_back(newpair);
	}

	void remove(Type obj) override {
		size_t index = hashFunction(obj.second.toString());
		std::vector<Type> vec = data[index];
		if (vec.data()->second == obj.second)
		{
			data->erase(data->begin() + index);
		}
	}

	bool contains(Type obj) override {
		size_t index = hashFunction(obj.second.toString());
		std::vector<Type> vec = data[index];
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
};

#endif
