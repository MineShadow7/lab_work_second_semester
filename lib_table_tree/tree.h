#ifndef LIB_TABLETREE_TABLE_H_
#define LIB_TABLETREE_TABLE_H_

#include "../lib_i_table/table.h"
#include "../lib_polynomial/polynomial.h"

template <class Type> class CNodeTree;
template <class Type> class CTreeTable;

template <typename Type>
class CNodeTree {
public:
	Type data;
	CNodeTree* left;
    CNodeTree* right;
	int height;

public:
	CNodeTree() {
		left = nullptr;
		right = nullptr;
		height = 0;
	}
	CNodeTree(Type _data) {
		data = _data;
		left = nullptr;
		right = nullptr;
	}

	friend class CTreeTable<Type>;
};

template <typename Type>
class CTreeTable {
private:
    CNodeTree<Type>* root;
    int size;

    void print(CNodeTree<Type>* node) {
        if (node == nullptr) {
            return;
        }

        print(node->left);
        std::cout << node->data.first << "   " << node->data.second.toString() << std::endl;
        print(node->right);
    }

    std::string printstring(CNodeTree<Type>* node) {
        if (node == nullptr) {
            return "";
        }
        std::string res;
        res += printstring(node->left);
        res += node->data.first + "      " + node->data.second.toString() + "\n";
        res += printstring(node->right);
        return res;
    }




    int stringToInt(std::string _str) {
        int tempInt = 0;
        for (int i = 0; i < _str.size(); i++) {
            tempInt += _str[i];
        }
        return tempInt;
    }

    int getHeight(CNodeTree<Type>* node) {
            if (node == nullptr) {
                return 0;
            }
        return node->height;
    }
    int getBalanceFactor(CNodeTree<Type>* node) {
        return getHeight(node->right) - getHeight(node->left);
    }
    void updateHeight(CNodeTree<Type>* node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    CNodeTree<Type>* rotateRight(CNodeTree<Type>* node) {
        CNodeTree<Type>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }
    CNodeTree<Type>* rotateLeft(CNodeTree<Type>* node) {
        CNodeTree<Type>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }
    CNodeTree<Type>* balance(CNodeTree<Type>* node) {
        updateHeight(node);

        if (getBalanceFactor(node) == 2) {
            if (getBalanceFactor(node->right) < 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        if (getBalanceFactor(node) == -2) {
            if (getBalanceFactor(node->left) > 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        return node;
    }

    CNodeTree<Type>* remove(CNodeTree<Type>* node, Type key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (stringToInt(key.first) < stringToInt(node->data.first)) {
            node->left = remove(node->left, key);
        }
        else if (stringToInt(key.first) > stringToInt(node->data.first)) {
            node->right = remove(node->right, key);
        }
        else {
            CNodeTree<Type>* left = node->left;
            CNodeTree<Type>* right = node->right;

            if (right == nullptr) {
                delete node;
                return left;
            }

            CNodeTree<Type>* min = findMin(right);
            min->right = removeMin(right);
            min->left = left;

            delete node;
            return balance(min);
        }

        return balance(node);
    }

    CNodeTree<Type>* findMin(CNodeTree<Type>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    CNodeTree<Type>* findParent(Type key) {
        if (node->left == nullptr) {
            return node->right;
        }
        node->left = removeMin(node->left);
        return balance(node);
    }

public:
    CTreeTable() {
        root = nullptr;
        size = 0;
    }

    ~CTreeTable() {
    }

    void insert(Type key) {
        CNodeTree<Type>* node = new CNodeTree<Type>(key);

        if (root == nullptr) {
            root = node;
            return;
        }

        CNodeTree<Type>* parent = root;

        while (true) {
            if (stringToInt(key.first) < stringToInt(parent->data.first)) {
                if (parent->left == nullptr) {
                    parent->left = node;
                    size++;
                    break;
                }
                parent = parent->left;
            }
            else if (stringToInt(key.first) > stringToInt(parent->data.first)) {
                if (parent->right == nullptr) {
                    parent->right = node;
                    size++;
                    break;
                }
                parent = parent->right;
            }
            else {
                delete node;
                return;
            }
        }
    }

    void remove(Type key) {
        root = remove(root, key);
        size--;
    }

    bool contains(Type key) {
        CNodeTree<Type>* node = root;
        while (node != nullptr) {
            if (stringToInt(key.first) == stringToInt(node->data.first)) {
                return true;
            }
            else if (stringToInt(key.first) < stringToInt(node->data.first)) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return false;
    }

    Type find(std::string key) {
        CNodeTree<Type>* node = root;
        while (node != nullptr) {
            if (stringToInt(key) == stringToInt(node->data.first)) {
                return (node->data);
            }
            else if (stringToInt(key) < stringToInt(node->data.first)) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        CPolynomial poly();
        std::pair<std::string, CPolynomial> nothing;
        return nothing;
    }

    void print() {
        print(root);
    }
    
    std::string printstring() {
        return printstring(root);
    }

    int getsize() {
        return size + 1;
    }
};

#endif
