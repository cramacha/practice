#include <iostream>
#include "../../utils/tree.h"

using namespace std;

bool
is_bst_impl(node<int> *pn, int min, int max)
{
	if (pn == NULL)
		return (true);
	int val = pn->val;
	if (val < min || val > max)
		return (false);
	return (is_bst_impl(pn->left, min, val)
			&& is_bst_impl(pn->right, val, max));
}

bool
is_bst(node<int> *pn)
{
	if (pn == NULL)
		return (true);

	return (is_bst_impl(pn, INT_MIN, INT_MAX));
}

int
main(int argc, char **argv)
{
	tree<int> pt;
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++)
		pt.insert(rand() % n - 1);
	pt.print_tree();
	cout << "is_bst: " << is_bst(pt.root) << endl;
	pt.root->left->val = INT_MAX;
	pt.print_tree();
	cout << "is_bst: " << is_bst(pt.root) << endl;
	return (0);
}
