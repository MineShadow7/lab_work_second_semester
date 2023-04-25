//Copyright 2023 Andrey Karagodin and Ivan Vinokurov.
#ifndef LIB_TABLELINEARLIST_TABLE_H_
#define LIB_TABLELINEARLIST_TABLE_H_
#include <string>
#include "../lib_list/list.h"
#include "../lib_i_table/table.h"

template<typename Type>
class CLinearTableList : public ITable<Type> {
 private:
	CList<Type> data;
 public:
	 CLinearTableList() {}
	void insert(Type obj) override
    {
		data.push_back(obj);
	}
	void remove(Type obj) override
    {
        CList<Type> cpy;
        cpy.cpy(data);
        Type currentObject;
        int index = 0;
        while (!cpy.isEmpty())
        {
            currentObject = cpy.pop_back();
            if (currentObject == obj)
                data.remove(index);
            index++;
        }
	}
    bool contains(const Type obj) override
    {
        CList<Type> cpy;
        cpy.cpy(data);
        Type currentObject;
        while (!cpy.isEmpty())
        {
            currentObject = cpy.pop_back();
            if (currentObject == obj)
                return true;
        }
        return false;
	}
	Type find(std::string key) override
    {
        CList<Type> cpy;
        cpy.cpy(data);
        Type currentObject;
        while (!cpy.isEmpty())
        {
            
            // currentObject.first, потому что мы предполагаемо храним std::pair<string KEY, VALUE>.
            if (cpy.pop_back().first == key)
            {
                currentObject = cpy.pop_back();
                return currentObject;
            }
        }
        if(currentObject.second == NULL)
            throw std::out_of_range("Key not found");
        
	}
};

#endif
