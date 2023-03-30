#ifndef LIB_TABLELINEARLIST_TABLE_H_
#define LIB_TABLELINEARLIST_TABLE_H_

template<typename Type>
class CLinearTableList : public CTable<Type> {
 private:
	CList<Type> data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif