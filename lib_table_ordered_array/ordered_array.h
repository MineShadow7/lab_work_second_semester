#ifndef LIB_TABLEORDEREDARRAY_TABLE_H_
#define LIB_TABLEORDEREDARRAY_TABLE_H_

template<typename Type>
class COrderedTableArray : public ITable<Type> {
 private:
	 Type* data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif
