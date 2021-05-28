#include <iostream>

using namespace std;

class node
{
	public:
		int data;
		node *left;
		node *right;
		int lsize;
		node(int);
};

node::node(int num)
{
	data = num;
	left = right = NULL;
	lsize = 0;
}

class tree
{
	public:
		node* insert(int, node *);
		tree();
		int rank(int, node *);
		void track(int);
		void print(node *);
		node *root;
};

tree::tree()
{
	root = NULL;
}

void
tree::print(node *pn)
{
	if (pn == NULL)
		return;
	print(pn->left);
	cout << pn->data << " ";
	print(pn->right);
}

void
tree::track(int num)
{
	if (root == NULL)
		root = new node(num);
	else
		insert(num, root);
}

node*
tree::insert(int num, node *pn)
{
	node* new_node;
	if (pn == NULL)
	{	
		new_node = new node(num);
		return (new_node);
	}
	else if (pn->data < num)
	{
		pn->right = insert(num, pn->right);
	}
	else if (pn->data >= num)
	{
		pn->left = insert(num, pn->left);
		pn->lsize++;
	}
	return (pn); 
}

int
tree::rank(int num, node *pn)
{
	if (pn == NULL)
		return (0);
	if (pn->data == num)
		return (pn->lsize);
	else if (pn->data > num)
		return (rank(num, pn->left));
	else
	{
		int left_size = (pn->left != NULL)? pn->left->lsize: 0;
		return (1 + left_size + rank(num, pn->right));
	}
}

int
main(int argc, char **argv)
{
	tree *pt = new tree();
	pt->track(5);
	pt->track(1);
	pt->track(4);
	pt->track(4);
	pt->track(5);
	pt->track(9);
	pt->track(7);
	pt->track(13);
	pt->track(3);
	pt->print(pt->root);
	cout << endl;
	cout << "Rank of 4 is: " << pt->rank(4, pt->root) << endl;
	cout << "Rank of 5 is: " << pt->rank(5, pt->root) << endl;
	return (0);
}
