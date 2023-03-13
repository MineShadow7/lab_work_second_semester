// Copyright 2023 Vinokurov Ivan

#ifndef LIB_TABLES_TABLES_H_
#define LIB_TABLES_TABLES_H_

#include <vector>
#include "../lib_list/list.h"

template<typename Type>
class CTable {
 public:
	 virtual int insert(Type obj);
	 virtual int remove(Type obj);
	 virtual Type find(std::string key);
};

template<typename Type>
class CTreeTable : public CTable<Type> {
 private:
	 std::vector data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

template<typename Type>
class COrderedTableArray : public CTable<Type> {
 private:
	 Type* data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

template<typename Type>
class CHashTableList : public CTable<Type> {
 private:
	CList data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

template<typename Type>
class CHashTableMix : public CTable<Type> {
 private:
	std::vector data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

template<typename Type>
class CSortedTableArray : public CTable<Type> {
 private:
	 Type* data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

template<typename Type>
class CLinearTableList : public CTable<Type> {
 private:
	CList<Type> data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

template<typename Type>
class CLinearTableArray : public CTable<Type> {
 private:
	Type* data;
 public:
	int insert(Type obj);
	int remove(Type obj);
	Type find(std::string key);
};

#endif