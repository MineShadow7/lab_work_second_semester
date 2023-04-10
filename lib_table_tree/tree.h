#ifndef LIB_TABLETREE_TABLE_H_
#define LIB_TABLETREE_TABLE_H_

template<typename Type>
class CTreeTable : public CTable<Type> {
 private:
	 Type* data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif