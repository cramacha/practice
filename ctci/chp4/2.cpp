#include <iostream>
#include <vector>
#include <algorithm>
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
bst(vector<int> &inp, node<int> **ppn, int left, int right)
{
	if (left >= right)	{
		if (left == right)
			*ppn = new node<int>(inp[left]);
		return;
	}
	int mid = (left + right) >> 1;
	*ppn = new node<int>(inp[mid]);
	bst(inp, &(*ppn)->left, left, mid - 1);
   	bst(inp, &(*ppn)->right, mid + 1, right);	
}

void
create_minimal_bst(vector<int> &inp)
{
	tree<int> t;
	bst(inp, &t.root, 0, inp.size() - 1);
	t.print_tree();
}

int
main(int argc, char **argv)
{
	int i;
	int n = atoi(argv[1]);
	vector<int> inp(n);
	
	for (i = 0; i < n; i++)
		inp[i] = rand() % (n - 1);
	sort(inp.begin(), inp.end());
	cout << inp;
	create_minimal_bst(inp);
	return (0);
}
