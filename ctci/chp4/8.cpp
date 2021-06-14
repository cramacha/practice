#include <iostream>
#include <vector>
#include <stack>
#include "../../utils/tree.h"

using namespace std;

bool
find_node(node<int> *pfind, node<int> *pn, stack<node<int> *> &s)
{
	if (pn == NULL)
		return (false);
	if (pn->val == pfind->val)
		return (true);
	s.push(pn);
	return (find_node(pfind, pn->left, s) 
			|| find_node(pfind, pn->right, s));
}

void
ancestor(node<int> *pn1, node<int> *pn2, node<int> *root, node<int> **ppn)
{
	stack<node<int> *> s1, s2;
	node<int> *top1, *top2;
	if (!find_node(pn1, root, s1) || !find_node(pn2, root, s2))
		return;
		
	while (s1.size() > s2.size())
		s1.pop();

	while (s2.size() > s1.size())
		s2.pop();

	while (s1.top() != s2.top()) {
		s1.pop();
		s2.pop();
	}
	*ppn = s1.top();
}

int
main(int argc, char **argv)
{
	tree<int> t;
	node<int> *parent;
	vector<int> v;
	int num;
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++) {
		num = rand() % n - 1;
		v.push_back(num);
		t.insert(num);
	}
	t.print_tree();
	int num1 = v.at(4);
	int num2 = v.at(6);
	node<int> *n1 = new node<int>(num1);
	node<int> *n2 = new node<int>(num2);
	cout << "n1 = " << n1->val 
		<< " n2 = " << n2->val << endl;
	ancestor(n1, n2, t.root, &parent);
	if (parent == NULL)
		cout << "Ancestor not found" << endl;
	else
		cout << "Ancestor of " << num1 << " and " << num2
			<< " is " << parent->val << endl;
	return (0);
}
