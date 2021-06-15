#include <iostream>
#include <vector>
#include <map>
#include "../../utils/tree.h"

using namespace std;

ostream&
operator <<(ostream &out, const vector<node<int> *> &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i]->val << " ";
	return (out);
}

ostream&
operator <<(ostream &out, const vector<vector<node<int> *> > &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i] << " ";
	out << endl;
	return (out);
}

void
count_levels(node<int> *root, vector<vector<node<int> *> > &v)
{
	int depth;
	map<node<int> *, int> levels;
	queue<node<int> *> q;
	if (root == NULL)
		return;
	q.push(root);
	levels[root] = 0;
	while (!q.empty())
	{
		node<int> *pt = q.front();
		q.pop();
		depth = levels[pt];
		if (pt->left) {
			levels[pt->left] = depth + 1;
			q.push(pt->left);
		}
		if (pt->right) {
			levels[pt->right] = depth + 1;
			q.push(pt->right);
		}	
		if (depth == v.size()) {
			vector<node<int> *> nv;
			v.push_back(nv);		
		}
		v[depth].push_back(pt);
	}
}

void
permute_impl(vector<vector<node<int> *> > &v, int offset, int depth)
{
	if (offset == v[depth].size() - 1) {
		cout << "Printing permutation: " << endl;
		cout << v << endl;
		return;
	}	

	for (int i = offset + 1; i < v[depth].size(); i++)
	{
		swap(v[depth].at(i), v[depth].at(offset));
		permute_impl(v, i, depth);
		swap(v[depth].at(i), v[depth].at(offset));
	}
}

void
permute(vector<vector<node<int> *> > &v)
{
	for (int i = 0; i < v.size(); i++)
		permute_impl(v, 0, i);
}

int
main(int argc, char **argv)
{
	tree<int> t;
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++)
		t.insert(rand() % n - 1);
	t.print_tree();
	vector<vector<node<int> *> > v;
	count_levels(t.root, v);
	permute(v);
	return (0);
}
