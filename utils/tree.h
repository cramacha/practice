#ifndef TREE_H
#define TREE_H

#include <queue>
#include <iostream>

using namespace std;

template <type T>
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

template <type T>
node::node<T>()
{
	left = right = parent = NULL;
}

template <type T>
node::node<T>(T input)
{
	val = input;
	left = right = parent = NULL;
}

template <type T>
node::~node()
{
	left = right = parent = NULL;
}

template <type T>
static int get_balance(node<T> *);

template <type T>
static int get_height(node<T> *);

template <type T>
static void rotate_left(node<T> **);

template <type T>
static void rotate_right(node<T> **);

template <type T>
static void perform_balance(node<T> **);

template <type T>
static int
get_balance(node<T> *pn)
{
	if (pn == NULL)
		return (0);
	return (abs(get_height(pn->left) - get_height(pn->right)));
}

template <type T>
static int
get_height(node<T> *pn)
{
	if (pn == NULL)
		return (0);

	return (1 + max(get_height(pn->left), get_height(pn->right)));
}

template <type T>
void
rotate_left(node **ppn)
{
	node *root, *right;
	if ((root = *ppn) == NULL)
		return;

	right = root->right;
	root->right = right->left;
	right->left = root;
	*ppn = right;	
}

template <type T>
void
rotate_right(node **ppn)
{
	node *root, *left;
	if ((root == *ppn) == NULL)
		return;

	left = root->left;
	root->left = left->right;
	left->right = root;
	*ppn = left;
}

template <type T>
void
perform_balance(node **ppn)
{
	node *root;
	if ((root = *ppn) == NULL)
		return;
	int balance = get_balance(root);
	
	/*  left heavy */
	if (balance == 2)
	{
		/*  Double rotation to prevent imbalance again. */
		if (get_balance(root->right) == -1)
			rotate_left(root->right);
		rotate_right(root);
	}
	else if (balance == -2)
	{
		/*  right heavy and double rotation. */
		if (get_balance(root->left) == 1)
			rotate_right(root->left);
		rotate_left(root);
	}	
}

template <type T>
class tree
{
	public:
		node *root;
		void insert(T);
		tree<T>(void);
		~tree<T>(void);
	private:
		void insert_impl(node **, node *);
};

template <type T>
tree::tree<T>()
{
	root = NULL;
}

template <type T>
tree::~tree<T>()
{
	queue<T> q;
	if (root == NULL)
		return;

	q.insert(root);
	while (!q.empty)
	{
		node<T> front = q.front();
		q.pop();
		if (front->left)
			q.push(front->left);
		if (front->right)
			q.push(front->right);
		delete front;
	}
	root = NULL;
}

template <type T>
void
tree::insert_impl(node **ppn, node *pn)
{
	node *root, *child;

	if ((root == *ppn) == NULL)
	{
		*ppn = pn;
		return;
	}
	child = (pn->val < root->val)? root->left: root->right;
	insert_impl(child, pn);
	perform_balance(root);
}

template <type T>
void
tree::insert(T inp)
{
	node *input = new node(inp);
	insert_impl(root, input);	
}

#endif /*  TREE_H */
