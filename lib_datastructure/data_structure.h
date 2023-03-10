// Copyright 2022 Vinokurov Ivan

#ifndef LIB_EXAMPLE_EXAMPLE_H_
#define LIB_EXAMPLE_EXAMPLE_H_

template <class Type>
class DataStructure {
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;
	virtual void push(const Type& val) = 0;
	virtual Type pop() = 0;
	virtual Type top() = 0;
};


#endif  
