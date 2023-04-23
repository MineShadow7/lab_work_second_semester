#ifndef LIB_TABLETREE_TABLE_H_
#define LIB_TABLETREE_TABLE_H_
#include <string>
#include "../lib_i_table/table.h"

template<typename Type>
class CTreeTable : public ITable<Type> {
 private:
	 Type* data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif
