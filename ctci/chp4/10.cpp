#include <iostream>
#include "../../utils/tree.h"

using namespace std;

node<int> *
find_node(node<int> *t1, node<int> *t2)
{
	if (t1 == NULL)
		return (NULL);

	if (t1->val == t2->val)
		return (t2);

	node<int> *left = find_node(t1->left, t2);
	node<int> *right = find_node(t1->right, t2);

	return (left == NULL? right: left);
}

bool
is_subtree_impl(node<int> *t1, node<int> *t2)
{
	if (t1 == NULL && t2 == NULL)
		return (true);
	if (t1 == NULL || t2 == NULL)
		return (false);
	if (t1->val != t2->val)
		return (false);
	bool left = is_subtree_impl(t1->left, t2->left);
	bool right = is_subtree_impl(t1->right, t2->right);
	return (left && right);
}

bool
is_subtree(node<int> *t1, node<int> *t2)
{
	node<int> *pn;
	if ((pn = find_node(t1, t2)) == NULL)
			return (false);
	return (is_subtree_impl(pn, t2));
}

int
main(int argc, char **argv)
{
	tree<int> t1, t2;
	for (int i = 0; i < 20; i++)
		t1.insert(i);
	t1.print_tree();
	t2.insert(3);
	t2.insert(5);
	t2.insert(8);
	t2.print_tree();	
	bool ret = is_subtree(t1.root, t2.root);
	cout << ((ret == true)? "is subtree" : "is not subtree")
		<< endl;
	return (0);
}
