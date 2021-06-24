#include <iostream>
#include "../../utils/sll.h"

using namespace std;

/*
 * This also detects the case when there is no cycle.
 */
bool
cycle(list<int> &l, node<int> **ppn)
{
	node<int> *slow = l.head, *fast = l.head;

	if (l.head == NULL || l.head->next == NULL)
		return (false);

	/*
	 *	l = {0, 1, 2, 3, 1}
	 *	slow  | fast
	 *
	 *	  0   | 0
	 *	  1   | 2
	 *	  2   | 1
	 *	
	 *	a) Fast and slow meet at 3.
	 *	b) Set slow to this meet point and fast to head.
	 *	c) Let them go one by one and they would meet at one point
	 *     (if cycle).
	 *	d) If fast has raced ahead to NULL then there is no cycle.
	 */
	
	for (; slow != NULL && fast != NULL && fast->next != NULL
			&& slow->next != fast->next->next;
			slow = slow->next, fast = fast->next->next);

	if (fast == NULL || fast->next == NULL)
		return (false);

	slow = slow->next;
	fast = l.head;

	for (; slow != NULL && fast != NULL
			&& slow != fast; slow = slow->next, fast = fast->next);

	*ppn = slow;
	return (true);
}

int
main(int argc, char **argv)
{
	list<int> l;
	node<int> *pn = NULL;
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++)
		l.push_back(i);
	l.print();
	bool ret = cycle(l, &pn);
	cout << ret << endl;

	/*  introduce a cycle */
	node<int> *tail = l.get_tail();
	node<int> *head = l.get_head();
	tail->next = head->next;
	ret = cycle(l, &pn);
	cout << ret << endl;
	return (0);
}
