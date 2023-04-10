#ifndef LIB_TABLESORTEDARRAY_TABLE_H_
#define LIB_TABLESORTEDARRAY_TABLE_H_

template<typename Type>
class CSortedTableArray : public CTable<Type> {
 private:
	 Type* data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif