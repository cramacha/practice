#include <iostream>
#include "../../utils/tree.h"

using namespace std;

void
link_up(node<int> *pn)
{
	if (pn == NULL)
		return;
	if (pn->left) {
		pn->left->parent = pn;
		link_up(pn->left);
	}
	if (pn->right) {
		pn->right->parent = pn;
		link_up(pn->right);
	}
}

node<int>*
find_min(node<int> *pn)
{
	if (pn->left == NULL)
		return (pn);

	return (find_min(pn->left));
}

node<int>*
first_right_parent(node<int> *pn)
{
	if (pn == NULL)
		return (NULL);
	node<int> *parent = pn->parent;
	if (parent->left == pn)
		return (parent);
	return (first_right_parent(parent));
}

void
successor(node<int> *pn, node<int> **ppn)
{
	if (pn == NULL) {
		*ppn = NULL;
		return;
	}
	if (pn->right == NULL)
		*ppn = first_right_parent(pn);
	else
		*ppn = find_min(pn->right);
}

void
in_order_print(node<int> *pn)
{
	if (pn == NULL)
		return;
	in_order_print(pn->left);
	cout << pn->val << " ";
	in_order_print(pn->right);
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	tree<int> t;
	node<int> *res;
	for (int i = 0; i < n; i++)
		t.insert(rand() % n - 1);
	
	t.print_tree();
	link_up(t.root);
	in_order_print(t.root);
	successor(t.root, &res);
	cout << endl << "in-order successor of: " << t.root->val
		<< " is: " << res->val << endl;
	successor(t.root->right, &res);
 	cout << endl << "in-order successor of: " << t.root->right->val
		<< " is: " << res->val << endl;
	return (0);
}
