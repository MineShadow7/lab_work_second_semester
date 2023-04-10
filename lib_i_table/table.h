// Copyright 2023 Vinokurov Ivan

#ifndef LIB_ITABLE_TABLE_H_
#define LIB_ITABLE_TABLE_H_

#include <vector>
#include "../lib_list/list.h"

template<typename Type>
class CTable {
 public:
	 virtual int insert(Type obj);
	 virtual int remove(Type obj);
	 virtual Type find(std::string key);
};

#endif