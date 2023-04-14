#ifndef LIB_TABLEHASHVECTOR_TABLE_H_
#define LIB_TABLEHASHVECTOR_TABLE_H_

template<typename Type>
class CHashTableMix : public ITable<Type> {
 private:
	std::vector<std::pair<Type, Type>> data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif
