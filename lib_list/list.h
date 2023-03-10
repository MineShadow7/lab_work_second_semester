// Copyright 2022 Vinokurov Ivan

#ifndef LIB_STACK_LIST_H_
#define LIB_STACK_LIST_H_
#include <list>
#include <iostream>

template <class Type> class CNode;
template <class Type> class CList;

template <class Type>
class CNode {
	Type data;
	CNode* next;

public:
	CNode(Type _data) {
		data = _data;
		next = nullptr;
	}
	void setNext(CNode* _next) {
		next = _next;
	}
	void print() {
		std::cout << data << " -> ";
	}

	friend class CList<Type>;
};

template <class Type>
class CList {
	CNode<Type>* head;
	CNode<Type>* tail;
	size_t size;
public:
	CList() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	bool isEmpty() {
		if (head == nullptr)
			return true;
		else
			return false;
	}
	void clr() {
		while (head != nullptr)
			pop_front();
	}
	void cpy(const CList& obj) {
		clr();
		CNode<Type>* tempNode = obj.head;

		for (int i = 0; i < obj.size && tempNode->next != nullptr; i++)
		{
			push_back(tempNode->data);
			tempNode = tempNode->next;
		}
		if (obj.size != 0 && tempNode == obj.tail) {
			push_back(tempNode->data);
		}
		size = obj.size;
	}
	void push_back(Type _data) {
		CNode<Type>* new_node = new CNode<Type>(_data);
		if (head == nullptr) {
			head = new_node;
			tail = new_node;
		}
		else {
			tail->next = new_node;
			tail = new_node;
		}
		size++;
	}
	void push_front(Type _data) {
		CNode<Type>* new_node = new CNode<Type>(_data);
		if (head == nullptr) {
			head = new_node;
			tail = new_node;
		}
		else {
			new_node->next = head;
			head = new_node;
		}
		size++;
	}
	Type remove(int _i) {
		size_t len = 0;
		len = this->size;
		if (_i < 0 || _i > len - 1)
			throw("can't remove in nullptr");
		if (_i == 0) {
			size--;
			return this->pop_back();
		}
		else if (_i == size - 1) {
			size--;
			return this->pop_front();
		}
		else {
			CNode<Type>* _pos = head;
			CNode<Type>* _pos2 = head;
			for (int i = 0; i < _i-1; i++) {
				_pos2 = _pos2->next;
			}
			for (int i = 0; i < _i; i++) {
				_pos = _pos->next;
			}
			_pos2->next = _pos->next;
			CNode<Type>* toRet = _pos;
			Type tempType = toRet->data;
			delete _pos;
			size--;
			return tempType;
		}
	}
	void insert(int _i, Type _data) {
		size_t len = 0;
		len = this->size;
		if (_i < 0 || _i > len - 1)
			throw("can't insert in nullptr");
		else {
			CNode<Type>* _pos = head;
			for (int i = 0; i < _i; i++) {
				while (_pos->next != tail) {
					_pos = _pos->next;
				}
			}
			CNode<Type>* new_node = new CNode<Type>(_data);
			new_node->next = _pos->next;
			_pos->next = new_node;
			if (new_node->next == nullptr) {
				tail = new_node;
			}
		}
		size++;
	}

	Type pop_front() {
		CNode<Type>* toRet = head;
		Type tempType = toRet->data;
		if (!(head == nullptr)) {
			CNode<Type>* toDel = head;
			head = head->next;
			delete toDel;
			return tempType;
		}
		if (head == nullptr) {
			tail = nullptr;
			return tempType;
		}
		size--;
	}
	Type pop_back() {
		CNode<Type>* toRet = tail;
		Type temp = toRet->data;
		if (head != tail) {
			CNode<Type>* toDel = head;
			while (toDel->next != tail) {
				toDel = toDel->next;
			}
			delete tail;
			tail = toDel;
			return temp;
		}
		else {
			tail = nullptr;
			head = nullptr;
			return temp;
		}
		size--;
	}

};


#endif