#include <iostream>
#include <numeric>
#include <vector>
#include "../../utils/tree.h"

using namespace std;

ostream&
operator <<(ostream &out, const vector<node<int> *> &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i]->val << " ";
	return (out);
}

int
sum_elements(vector<node<int> *> &inp)
{
	/*  Dont need anything fancy actually, a simple for loop works too.
	 *  But here the lambda expression is needed to add an int (starting value 
	 *  0) with a node<int> *'s val. Dont forget to include <numeric>.
	 *  Refer:
	 *	https://stackoverflow.com/questions/18253223/sum-of-non-integer-elements-in-stdvector
	 */
	return accumulate(inp.begin(), inp.end(), 0,
			[](int a, const node<int> *b) {
				return (a + b->val);
			});
}

void
path_sum_impl(node<int> *root, vector<vector<node<int> *> > &v,
		int total, int depth)
{
	int i;
	if (root == NULL)
		return;

	if (depth == v.size()) {
		vector<node<int> *> nv;
		v.push_back(nv);
	}

	for (i = 0; i <= depth; i++)
		v[i].push_back(root);

	for (i = 0; i <= depth; i++) {
		if (sum_elements(v[i]) == total)
			cout << v[i] << endl;		
	}
	
	path_sum_impl(root->left, v, total, depth + 1);
	path_sum_impl(root->right, v, total, depth + 1);
}

void
path_sum(node<int> *root, vector<vector<node<int> *> > &v, 
		int total)
{
	path_sum_impl(root, v, total, 0);	
}

int
main(int argc, char **argv)
{
	tree<int> t;
	vector<vector<node<int> *> > v;
	int n = atoi(argv[1]);
	int total = atoi(argv[2]);
	for (int i = 0; i < n; i++)
		t.insert(i);
	t.print_tree();
	path_sum(t.root, v, total);
	return (0);
}
