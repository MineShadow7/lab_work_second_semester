#ifndef LIB_TABLETREE_TABLE_H_
#define LIB_TABLETREE_TABLE_H_
#include "../lib_i_table/table.h"
#include "../lib_polynomial/polynomial.h"

template <class Type>
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

	friend class CTreeTable;
};

class CTreeTable {
 private:
	 CNodeTree<std::pair<CPolynomial, int>>* root;

	 int calcHeight(CNodeTree<std::pair<CPolynomial, int>>* p) {
		 if (p->left && p->right) {
			 if (p->left->height < p->right->height)
				 return p->right->height + 1;
			 else return  p->left->height + 1;
		 }
		 else if (p->left && p->right == NULL) {
			 return p->left->height + 1;
		 }
		 else if (p->left == NULL && p->right) {
			 return p->right->height + 1;
		 }
		 return 0;
	 }
	 int bf(CNodeTree<std::pair<CPolynomial, int>>* n) {
		 if (n->left && n->right) {
			 return n->left->height - n->right->height;
		 }
		 else if (n->left && n->right == NULL) {
			 return n->left->height;
		 }
		 else if (n->left == NULL && n->right) {
			 return -n->right->height;
		 }
	 }
	 CNodeTree<std::pair<CPolynomial, int>>* llrotation(CNodeTree<std::pair<CPolynomial, int>>* n) {
		 CNodeTree<std::pair<CPolynomial, int>>* p;
		 CNodeTree<std::pair<CPolynomial, int>>* tp;
		 p = n;
		 tp = p->left;

		 p->left = tp->right;
		 tp->right = p;

		 return tp;
	 }


	 CNodeTree<std::pair<CPolynomial, int>>* rrrotation(CNodeTree<std::pair<CPolynomial, int>>* n) {
		 CNodeTree<std::pair<CPolynomial, int>>* p;
		 CNodeTree<std::pair<CPolynomial, int>>* tp;
		 p = n;
		 tp = p->right;

		 p->right = tp->left;
		 tp->left = p;

		 return tp;
	 }


	 CNodeTree<std::pair<CPolynomial, int>>* rlrotation(CNodeTree<std::pair<CPolynomial, int>>* n) {
		 CNodeTree<std::pair<CPolynomial, int>>* p;
		 CNodeTree<std::pair<CPolynomial, int>>* tp;
		 CNodeTree<std::pair<CPolynomial, int>>* tp2;
		 p = n;
		 tp = p->right;
		 tp2 = p->right->left;

		 p->right = tp2->left;
		 tp->left = tp2->right;
		 tp2->left = p;
		 tp2->right = tp;

		 return tp2;
	 }

	 CNodeTree<std::pair<CPolynomial, int>>* lrrotation(CNodeTree<std::pair<CPolynomial, int>>* n) {
		 CNodeTree<std::pair<CPolynomial, int>>* p;
		 CNodeTree<std::pair<CPolynomial, int>>* tp;
		 CNodeTree<std::pair<CPolynomial, int>>* tp2;
		 p = n;
		 tp = p->left;
		 tp2 = p->left->right;

		 p->left = tp2->right;
		 tp->right = tp2->left;
		 tp2->right = p;
		 tp2->left = tp;

		 return tp2;
	 }
	 CNodeTree<std::pair<CPolynomial, int>>* inpre(CNodeTree<std::pair<CPolynomial, int>>* p) {
		 while (p->right != NULL)
			 p = p->right;
		 return p;
	 }

	 CNodeTree<std::pair<CPolynomial, int>>* insuc(CNodeTree<std::pair<CPolynomial, int>>* p) {
		 while (p->left != NULL)
			 p = p->left;

		 return p;
	 }
 public:
	 CTreeTable() {
		 this->root = NULL;
	 }
	 CNodeTree<std::pair<CPolynomial, int>>* insert(CNodeTree<std::pair<CPolynomial, int>>* r, std::pair<CPolynomial, int> data) {

		 if (r == NULL) {
			 CNodeTree<std::pair<CPolynomial, int>>* n;
			 n = new CNodeTree<std::pair<CPolynomial, int>>;
			 n->data.first = data.first;
			 n->data.second = data.second;
			 r = n;
			 r->left = r->right = NULL;
			 r->height = 1;
			 return r;
		 }
		 else {
			 if (data.second < r->data.second)
				 r->left = insert(r->left, data);
			 else
				 r->right = insert(r->right, data);
		 }

		 r->height = calcHeight(r);

		 if (bf(r) == 2 && bf(r->left) == 1) {
			 r = llrotation(r);
		 }
		 else if (bf(r) == -2 && bf(r->right) == -1) {
			 r = rrrotation(r);
		 }
		 else if (bf(r) == -2 && bf(r->right) == 1) {
			 r = rlrotation(r);
		 }
		 else if (bf(r) == 2 && bf(r->left) == -1) {
			 r = lrrotation(r);
		 }

		 return r;
	 }
	 CNodeTree<std::pair<CPolynomial, int>>* remove(CNodeTree<std::pair<CPolynomial, int>>* p, std::pair<CPolynomial, int> data) {

		 if (p->left == NULL && p->right == NULL) {
			 if (p == this->root)
				 this->root = NULL;
			 delete p;
			 return NULL;
		 }

		 CNodeTree<std::pair<CPolynomial, int>>* t;
		 CNodeTree<std::pair<CPolynomial, int>>* q;
		 if (p->data.second < data.second) {
			 p->right = remove(p->right, data);
		 }
		 else if (p->data > data) {
			 p->left = remove(p->left, data);
		 }
		 else {
			 if (p->left != NULL) {
				 q = inpre(p->left);
				 p->data.first = q->data.first;
				 p->data.second = q->data.second;
				 p->left = remove(p->left, q->data);
			 }
			 else {
				 q = insuc(p->right);
				 p->data.first = q->data.first;
				 p->data.second = q->data.second;
				 p->right = remove(p->right, q->data);
			 }
		 }

		 if (bf(p) == 2 && bf(p->left) == 1) { p = llrotation(p); }
		 else if (bf(p) == 2 && bf(p->left) == -1) { p = lrrotation(p); }
		 else if (bf(p) == 2 && bf(p->left) == 0) { p = llrotation(p); }
		 else if (bf(p) == -2 && bf(p->right) == -1) { p = rrrotation(p); }
		 else if (bf(p) == -2 && bf(p->right) == 1) { p = rlrotation(p); }
		 else if (bf(p) == -2 && bf(p->right) == 0) { p = llrotation(p); }


		 return p;
	}
	std::pair<CPolynomial, int> find(int key);
};

#endif
