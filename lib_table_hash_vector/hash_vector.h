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
		data[index].push_back(obj);
	}

	void remove(Type obj) override {
		size_t index = hashFunction(obj);
		auto& vec = data[index];
		auto it = std::find(vec.begin(), vec.end(), obj);
		if (it != vec.end()) {
			vec.erase(it);
		}
	}

	bool contains(Type obj) override {
		size_t index = hashFunction(obj);
		auto& vec = data[index];
		return std::find(vec.begin(), vec.end(), obj) != vec.end();
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
};

#endif