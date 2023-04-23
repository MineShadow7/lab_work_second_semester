#ifndef LIB_TABLELINEARARRAY_TABLE_H_
#define LIB_TABLELINEARARRAY_TABLE_H_
#include <string>
#include "../lib_i_table/table.h"

template<typename Type>
class CLinearTableArray : public ITable<Type> {
 private:
	Type* data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif
