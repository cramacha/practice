#include "../../utils/sll.h"

using namespace std;

void
erase(list<int> &l, node<int> *pn)
{
	node<int> *tmp, *next;
	node<int> *cur = l.head;
	while (cur != NULL) {
		next = cur->next;
		if(next == pn) {
			tmp = next;
			cur->next = next->next;
			delete tmp;
			break;
		}
		cur = cur->next;
	}
}

void
partition(list<int> &l, int val)
{
	node<int> *pn, *tmp;

	for (pn = l.head; pn != NULL; pn = tmp) {
		/* 
		 * Saving the next pointer here is important as
		 * the erase function below will delete pn and we
		 * will no longer have access to pn->next.
		 */
		tmp = pn->next;
		if (pn->val < val) {
			l.push_front(pn->val);
			erase(l, pn);
		}
	}	
}

int
main(int argc, char **argv)
{
	list<int> l;
	int n = atoi(argv[1]);
	int val = atoi(argv[2]);

	for (int i = n; i > 0; i--)
		l.push_back(i + 1);

	l.print();
	partition(l, val);
	l.print();
	return (0);
}
