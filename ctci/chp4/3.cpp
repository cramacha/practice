#include <iostream>
#include <vector>
#include "../../utils/tree.h"

using namespace std;

ostream&
operator <<(ostream &out, const vector<int> &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i] << " ";
	out << endl;
	return (out);
}

void
count_levels_impl(node<int> *pn, int depth, vector<vector<int> > &res)
{
	if (pn == NULL)
		return;

	if (depth == res.size())
	{
		vector<int> nv;
		res.push_back(nv);
	}
	res[depth].push_back(pn->val);
	count_levels_impl(pn->left, depth + 1, res);
	count_levels_impl(pn->right, depth + 1, res);
}

void
count_levels(node<int> *pn)
{
	vector<vector<int> > res;
	count_levels_impl(pn, 0, res);
	for (int i = 0; i < res.size(); i++)
		cout << res[i];
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	tree<int> t;
	int num;
	for (int i = 0; i < n; i++)
	{	
		num = rand() % (n - 1);
		cout << num << " ";
		t.insert(num);
	}
	cout << endl << "t.root = " << t.root->val << endl;
	t.print_tree();
	count_levels(t.root);	
	return (0);
}
