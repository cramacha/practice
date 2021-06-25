#include "../../utils/sll.h"
#include <math.h>

using namespace std;

bool
intersect_list(list<int> *l1, list<int> *l2, node<int> **ppn)
{
	int i;
	list<int> *s, *l;
	node<int> *pn1 = NULL, *pn2 = NULL;
	int delta = 0;
	int len1 = l1->size();
	int len2 = l2->size();

	/*  Find the smaller or larger of the lists. */
	if (len1 > len2) {
		s = l2;
		l = l1;
	} else {
		s = l1;
		l = l2;
	}
	
	/*  
	 * Advance larger by (len2 - len1) steps.
	 * Notice we are doing <= instead of <. This is to ensure that larger moves 
	 * to same head as smaller.
	 */
	delta = abs(len2 - len1);
	for (i = 0, pn1 = l->head; i <= delta; i++, pn1 = pn1->next);

	/*  Check whether each successive node of smaller and larger are the same. */
	for (pn2 = s->head; pn1 != NULL && pn2 != NULL 
			&& pn1->val != pn2->val; pn1 = pn1->next, pn2 = pn2->next);

	/*  In case there is no intersection. */
	if (pn1 == NULL || pn2 == NULL)
		return (false);

	*ppn = pn1;
	return (true);
}

int
main(int argc, char **argv)
{
	list<int> *l1 = new list<int>();
	list<int> *l2 = new list<int>();
	node<int> *intersect = new node<int>();
	int i;
	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[2]);

	for (i = 0; i < n1 ; i++)
		l1->push_back(i + 3);

	for (i = 0; i < n2; i++)
		l2->push_back(i + 1 * 9);

	node<int> *pn = l2->get_head();
	pn = pn->next->next->next;
	pn->val = 3;
	pn = pn->next;
	pn->val = 4;
	pn = pn->next;
	pn->val = 5;
	pn = pn->next;
	pn->val = 6;
	l1->print();
	l2->print();
	bool ret = intersect_list(l1, l2, &intersect);
	cout << "ret = " << ret << " intersect = " << intersect->val << endl;
	return (0);
}
