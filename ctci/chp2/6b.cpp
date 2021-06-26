#include "../../utils/sll.h"

using namespace std;

bool
is_palin(list<int> &l)
{
	list<int> tmp;
	node<int> *pn, *pn2;
	int i;
	int size = l.size();

	/*
	 * l = {0, 1, 2, 1, 0}
	 * after loop:
	 * tmp = {2, 1, 0}
	 */
	for (i = 0; i < size/2; i++) {
		pn = l.get_head();
		tmp.push_front(pn->val);
		l.pop_front();
	}

	/*
	 * Remove the extra node if the size is odd, so we can proceed to compare 
	 * tmp and l node-by-node for equality.
	 *
	 * l = {1, 0}
	 * tmp = {1, 0}
	 */
	if (size % 2)
		l.pop_front();

	/*
	 * Break early at the first instance of a mismatch between l and tmp.
	 */
	for (pn2 = tmp.get_head(), pn = l.get_head();pn2 != NULL && pn != NULL; pn2 = pn2->next, pn = pn->next) {
		if (pn->val != pn2->val)
			return (false);
	}
	return (true);
}

int
main(int arc, char **argv)
{
	list<int> l;
	l.push_back(0);
	l.push_back(1);
	l.push_back(2);
	l.push_back(1);
	l.push_back(0);
	l.print();
	cout << "is_palin:" << is_palin(l) << endl;
	l.push_back(0);
	l.print();
	cout << "is_palin:" << is_palin(l) << endl;
	return (0);
}
