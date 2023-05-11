//Copyright 2023 Andrey Karagodin and Ivan Vinokurov.
#ifndef LIB_TABLELINEARLIST_TABLE_H_
#define LIB_TABLELINEARLIST_TABLE_H_
#include <string>
#include "../lib_list/list.h"
#include "../lib_i_table/table.h"

template<typename Type>
class CLinearTableList : public ITable<Type> {
private:
    CList<std::pair<std::string, Type>> data;
public:
    CLinearTableList() {};

    void insert(Type obj) override
    {
        data.push_back(std::make_pair(obj.toString(), obj));
    }
    void remove(Type obj) override
    {
        CList<std::pair<std::string, Type>> cpy;
        cpy.cpy(data);
        Type currentObject;
        int index = 0;
        while (!cpy.isEmpty())
        {
            currentObject = cpy.pop_back().second;
            if (currentObject == obj)
                data.remove(index);
            index++;
        }
    }
    bool contains(const Type obj) override
    {
        CList<std::pair<std::string, Type>> cpy;
        cpy.cpy(data);
        std::pair<std::string, Type> currentObject;
        while (!cpy.isEmpty())
        {
            currentObject = cpy.pop_back();
            if (currentObject.second == obj)
                return true;
        }
        return false;
    }
    Type find(std::string key) override
    {
        CList<std::pair<std::string, Type>> cpy;
        cpy.cpy(data);
        std::pair<std::string, Type> currentObject;
        while (!cpy.isEmpty())
        {
            // currentObject.first, потому что мы предполагаемо храним std::pair<string KEY, POLINOM>.
            if (cpy.pop_back().first == key)
            {
                currentObject = cpy.pop_back();
                return currentObject.second;
            }
        }
        if (cpy.isEmpty() && currentObject.first != key)
            throw std::out_of_range("Key not found");
    }
    void print() {
        std::cout << "Table Linear List OBJ & KEY: " << std::endl;
        int polynum = 0;
        CList<std::pair<std::string, Type>> cpy;
        cpy.cpy(data);
        std::pair<std::string, Type> currentObject;
        while (!cpy.isEmpty())
        {
            currentObject = cpy.pop_back();
            std::cout << "obj" << polynum + 1 << " " << currentObject.first << std::endl;
            polynum++;
        }
    }
};

#endif
