#ifndef TREE_H
#define TREE_H

#include <queue>
#include <iostream>

using namespace std;

template <typename T>
class node
{
	public:
		T val;
		node<T> *parent;
		node<T> *left;
		node<T> *right;
		node<T>(void);
		~node<T>(void);
		node<T>(T);
};

template <typename T>
node<T>::node()
{
	left = right = parent = NULL;
}

template <typename T>
node<T>::node(T input)
{
	val = input;
	left = right = parent = NULL;
}

template <typename T>
node<T>::~node()
{
	left = right = parent = NULL;
}

template <typename T>
static int get_balance(node<T> *);

template <typename T>
static int get_height(node<T> *);

template <typename T>
static void rotate_left(node<T> **);

template <typename T>
static void rotate_right(node<T> **);

template <typename T>
static void perform_balance(node<T> **);

template <typename T>
static int
get_balance(node<T> *pn)
{
	if (pn == NULL)
		return (0);
	return (get_height(pn->left) - get_height(pn->right));
}

template <typename T>
static int
get_height(node<T> *pn)
{
	if (pn == NULL)
		return (0);

	return (1 + max(get_height(pn->left), get_height(pn->right)));
}

template <typename T>
void
rotate_left(node<T> **ppn)
{
	node<T> *root, *right;
	if ((root = *ppn) == NULL)
		return;

	right = root->right;
	root->right = right->left;
	right->left = root;
	*ppn = right;	
}

template <typename T>
void
rotate_right(node<T> **ppn)
{
	node<T> *root, *left;
	if ((root = *ppn) == NULL)
		return;

	left = root->left;
	root->left = left->right;
	left->right = root;
	*ppn = left;
}

template <typename T>
void
perform_balance(node<T> **ppn)
{
	node<T> *root;
	if ((root = *ppn) == NULL)
		return;
	int balance = get_balance(root);
	
	/*  left heavy */
	if (balance == 2)
	{
		/*  Double rotation to prevent imbalance again. */
		if (get_balance(root->right) == -1)
			rotate_left(&root->right);
		rotate_right(ppn);
	}
	/*  right heavy */
	else if (balance == -2)
	{
		if (get_balance(root->left) == 1)
			rotate_right(&root->left);
		rotate_left(ppn);
	}	
}

template <typename T>
class tree
{
	public:
		node<T> *root;
		void insert(T);
		void print_tree(void);
		tree<T>(void);
		~tree<T>(void);
	private:
		void insert_impl(node<T> **, node<T> *);
		void print_impl(node<T> *, int);
};

template <typename T>
tree<T>::tree()
{
	root = NULL;
}

template <typename T>
void
tree<T>::print_impl(node<T> *pn, int depth)
{
	if (pn == NULL)
		return;
	for (int i = 0; i < depth; i++)
		cout << " ";
	cout << pn->val << endl;
	print_impl(pn->right, depth + 1);
	print_impl(pn->left, depth + 1);
}

template <typename T>
void
tree<T>::print_tree()
{
	print_impl(root, 0);
}

template <typename T>
tree<T>::~tree()
{
	queue<node<T>*> q;
	if (root == NULL)
		return;

	q.push(root);
	while (!q.empty())
	{
		node<T> *front = q.front();
		q.pop();
		if (front->left)
			q.push(front->left);
		if (front->right)
			q.push(front->right);
		delete front;
	}
	root = NULL;
}

template <typename T>
void
tree<T>::insert_impl(node<T> **ppn, node<T> *pn)
{
	node<T> *root, **child;

	if ((root = *ppn) == NULL)
	{
		*ppn = pn;
		return;
	}
	child = (pn->val < root->val)? &root->left: &root->right;
	insert_impl(child, pn);
	perform_balance(ppn);
}

template <typename T>
void
tree<T>::insert(T inp)
{
	node<T> *input = new node<T>(inp);
	insert_impl(&root, input);	
}

#endif /*  TREE_H */
