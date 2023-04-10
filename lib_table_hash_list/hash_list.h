#ifndef LIB_TABLEHASHLIST_TABLE_H_
#define LIB_TABLEHASHLIST_TABLE_H_

template<typename Type>
class CHashTableList : public ITable<Type> {
 private:
	CList data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif