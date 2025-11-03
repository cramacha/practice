#include <iostream>
#include <math.h>
#include <queue>
#include <map>

using namespace std;

template <typename T>
class node {
public:
	T val;
	node *left;
	node *right;

	node<T>();
	node<T>(T);
	~node<T>();
};

template <typename T>
node<T>::node() {}

template <class T>
node<T>::node(T val) {
	this->val = val;
	left = nullptr;
	right = nullptr;
}


template <typename T>
node<T>::~node() {
	val.~T();
	left = nullptr;
	right = nullptr;
}

template <typename T>
static int get_height(node<T> *pn);

template <typename T>
static int get_balance(node<T> *pn);

template <typename T>
static void perform_balance(node<T> **ppn);

template <typename T>
static void rotate_left(node<T> **ppn);

template <typename T>
static void rotate_right(node<T> **ppn);

template <typename T>
class tree {
public:
	node<T> *root;

	tree<T>(node<T> *);
	~tree<T>();

	void insert_impl(node<T> **ppn, node<T> *pn);
	void inorder_print(node<T> *);
	void insert(T val);
};

template <typename T>
tree<T>::tree(node<T> *inp) {
	root = inp;
}

template <typename T>
tree<T>::~tree() {
	queue<node<T> *> q;
	map<T, bool> mp;

	if (root == nullptr)
		return;

	q.push(root);
	while (!q.empty()) {
		node<T> *front = q.front();
		q.pop();

		if (front->left) {
			q.push(front->left);
		}

		if (front->right) {
			q.push(front->right);
		}

		cout << "deleting: " << front->val <<  " ";
		delete front;
		front = nullptr;
	}
	root = nullptr;
}

template <typename T>
void
tree<T>::insert_impl(node<T> **ppn, node<T> *pn) {
	node<T> *root, **child;
	if ((root = *ppn) == nullptr) {
		*ppn = pn;
		return;
	}

	child = (pn->val < root->val)? &root->left: &root->right;
	insert_impl(child, pn);
	perform_balance(ppn);
}

template <typename T>
void
tree<T>::insert(T val) {
	node<T> *pn = new node<T>(val);
	insert_impl(&root, pn);
}

template <typename T>
void
tree<T>::inorder_print(node<T> *pn) {
	if (pn == nullptr) {
		cout << endl;
		return;
	}

	inorder_print(pn->left);
	cout << pn->val << " ";
	inorder_print(pn->right);
}

template <typename T>
static int get_height(node<T> *pn) {
	if (pn == nullptr) {
		return (0);
	}
	return (1 + get_height(pn->left) + get_height(pn->right));
}

template <typename T>
static int get_balance(node<T> *pn) {
	int left_height = get_height(pn->left);
	int right_height = get_height(pn->right);
	return (abs(right_height - left_height) < 2);
}

template <typename T>
static void rotate_right(node<T> **ppn) {
	node<T> *root, *left;

	if ((root = *ppn) == nullptr) {
		return;
	}

	left = root->left;
	root->left = left->right;
	left->right = root;
	*ppn = left;
}

template <typename T>
static void rotate_left(node<T> **ppn) {
	node<T> *root, *right;

	if ((root = *ppn) == nullptr) {
		return;
	}

	right = root->right;
	root->right = right->left;
	right->left = root;
	*ppn = right;
}

template <typename T>
static void perform_balance(node<T> **ppn) {
	node<T> *root;
	if ((root = *ppn) == nullptr) {
		return;
	}
	int balance = get_balance(root);

	// left heavy.
	if (balance == 2) {
		// double rotation
		if (get_balance(root->right) == -1)
			rotate_left(&root->right);
		rotate_right(ppn);

	} else if (balance == -2) {
		// right heavy.
		// double rotation
		if (get_balance(root->left) == 1)
			rotate_right(&root->left);
		rotate_left(ppn);
	}
}

int main(int argc, char **argv) {
	node<int> *root = new node<int>(5);
	tree<int> *t = new tree<int>(root);
	
	t->insert(3);
	t->inorder_print(root);
	t->insert(6);
	t->inorder_print(root);
	t->insert(1);
	t->inorder_print(root);
	delete t;
	return (0);
} 