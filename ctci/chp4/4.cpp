#include <iostream>
#include <queue>
#include <vector>
#include <math.h>
#include <map>
#include "../../utils/tree.h"

using namespace std;

ostream&
operator <<(ostream &out, const vector<node<int> *> &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i]->val << " ";
	out << endl;
	return (out);
}

int
get_height(node<int> *pn)
{
	if (pn == NULL)
		return (0);
	return (1 + max(get_height(pn->left),
			   get_height(pn->right)));
}

/*
 * The runtime of this is O(2^h) where h is height of tree.
 */
bool
is_balance1(node<int> *pn)
{
	int left_height = get_height(pn->left);
	int right_height = get_height(pn->right);
	return (abs(left_height - right_height) < 2);	
}

bool
is_power_of_two(int num, int depth)
{
	return (pow(2,depth) == num); 
}

/*
 * This checks whether the number of nodes in the previous depth
 * is a power of 2. If it is not, then return early. The runtime of
 * this is O(n).
 */
bool
is_balance2(node<int> *pn)
{
	queue<node<int> *> q;
	int depth = 0;
	map<node<int> *, int> depth_map;
	vector<vector<node<int> *> > vnodes;	
	
	if (pn == NULL)
		return (false);
	q.push(pn);
	depth_map[pn] = 0;
	
	while (!q.empty())
	{
		node<int> *pt = q.front();
		q.pop();
		depth = depth_map[pt];
		if (pt->left)
		{
			q.push(pt->left);
			depth_map[pt->left] = depth + 1;
		}
		if (pt->right)
		{
			q.push(pt->right);
			depth_map[pt->right] = depth + 1;
		}
		if (depth == vnodes.size())
		{
			vector<node<int> *> vn;
			vnodes.push_back(vn);
			if (depth > 0 &&
					!is_power_of_two(vnodes[depth - 1].size(), depth - 1))
				return (false);
		}
		vnodes[depth].push_back(pt);
	}
	return (true);
}

int
main(int argc, char **argv)
{
	tree<int> t;
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++)
		t.insert(rand() % (n - 1));
	t.print_tree();
	cout << "is_balance1: " << is_balance1(t.root) << endl;
	cout << "is_balance2: " << is_balance2(t.root) << endl;
	t.root->left = NULL;
	t.print_tree();
	cout << "is_balance1: " << is_balance1(t.root) << endl;
	cout << "is_balance2: " << is_balance2(t.root) << endl;
	return (0);
}
