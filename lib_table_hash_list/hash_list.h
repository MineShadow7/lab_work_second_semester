#ifndef LIB_TABLEHASHLIST_TABLE_H_
#define LIB_TABLEHASHLIST_TABLE_H_
#include <string>
#include "../lib_list/list.h"
#include "../lib_i_table/table.h"

template<typename Type>
class CHashTableList : public ITable<Type> {
 private:
	CList<std::pair<Type, Type>> data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif