// Copyright 2023 Vinokurov Ivan

#ifndef LIB_ITABLE_TABLE_H_
#define LIB_ITABLE_TABLE_H_

#include <string>
#include <vector>

template<typename Type>
class ITable 
{
 public:
	 virtual void insert(const Type obj) = 0;
	 virtual void remove(const Type obj) = 0;
	 virtual bool contains(const Type obj) = 0;
	 virtual Type find(const std::string key) = 0;
};

#endif
