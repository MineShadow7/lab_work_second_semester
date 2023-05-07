#ifndef LIB_TABLEHASHVECTOR_TABLE_H_
#define LIB_TABLEHASHVECTOR_TABLE_H_
#include <iostream>
#include <string>
#include "../lib_i_table/table.h"

template<typename Type>
class CHashTableMix : public ITable<Type> {
private:
	size_t size;
	std::vector<std::pair<std::string, Type>>* data;

	size_t hashFunction(const std::string& obj) const {
		return std::hash<std::string>{}(obj) % size;
	}
public:
	explicit CHashTableMix(const size_t _size)
	{
		size = _size;
		data = new std::vector<std::pair<std::string, Type>>[size];
	}

	~CHashTableMix()
	{
		delete[] data;
	}

	void insert(Type obj) override {
		size_t index = hashFunction(obj.toString());
		std::pair<std::string, Type> newpair(obj.toString(), obj);
		data[index].push_back(newpair);
	}

	void remove(Type obj) override {
		size_t index = hashFunction(obj.toString());
		std::vector<std::pair<std::string, Type>> vec = data[index];
		if (vec.data()->second == obj)
		{
			data->erase(data->begin() + index);
		}
	}

	bool contains(Type obj) override {
		size_t index = hashFunction(obj.toString());
		std::vector<std::pair<std::string, Type>> vec = data[index];
		if (vec.data()->second == obj)
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
					return obj.second;
				}
			}
		}
		throw std::out_of_range("Key not found");
	}
};

#endif
