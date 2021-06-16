#include <iostream>
#include <queue>

#include "../../utils/tree.h"

using namespace std;

node<int> *
random(node<int> *root, int n)
{
	int i = 0;
	node<int> *ret;
	int random_node = rand() % (n - 1);
	queue<node<int> *> q;
	q.push(root);

	while (i <= random_node) {
		node<int> *pn = q.front();
		q.pop();
		if (pn->left)
			q.push(pn->left);
		if (pn->right)
			q.push(pn->right);
		ret = pn;
		i++;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	int i;
	tree<int> t;
	for (i = 0; i < n; i++)
		t.insert(i);

	for (i = 0; i < n; i++) {
		node<int> *rn = random(t.root, n);
		cout << "random node: " << rn->val << endl;
	}
	return (0);
}
