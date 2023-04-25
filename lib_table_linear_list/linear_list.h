#ifndef LIB_TABLELINEARLIST_TABLE_H_
#define LIB_TABLELINEARLIST_TABLE_H_
#include "../lib_i_table/table.h"
#include "../lib_list/list.h"

template<typename Type>
class CLinearTableList : public ITable<Type> {
 private:
	CList<Type> data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif
