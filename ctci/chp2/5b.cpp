#include "../../utils/sll.h"

using namespace std;

void
reverse(list<int> &l1)
{
	list<int> *tmp = new list<int>();
	node<int> *pn = l1.head;
	while (pn != NULL)
	{
		tmp->push_front(pn->val);
		pn = pn->next;
		l1.pop_front();
	}
	l1.head = tmp->head;
}

void
sum_lists(list<int> &l1, list<int> &l2, list<int> &sumlist)
{
	int sum = 0, carry = 0;
	node<int> *pn1, *pn2;
	reverse(l1);
	reverse(l2);
	l1.print();
	l2.print();

	pn1 = l1.get_head();
	pn2 = l2.get_head();

	while (pn1 != NULL && pn2 != NULL) {
		sum = carry + pn1->val + pn2->val;
		carry = sum / 10;	
		sum = sum % 10;
		sumlist.push_back(sum);
		pn1 = pn1->next;
		pn2 = pn2->next;
	}

	while (pn1 != NULL) {
		sum = carry + pn1->val;
		carry = sum / 10;	
		sum = sum % 10;
		sumlist.push_back(sum);
		pn1 = pn1->next;
	}

	while (pn2 != NULL) {
		sum = carry + pn2->val;
		carry = sum / 10;	
		sum = sum % 10;
		sumlist.push_back(sum);
		pn2 = pn2->next;
	}

	if (carry)
		sumlist.push_back(carry);
}

int
main(int argc, char **argv)
{
	list<int> l1, l2, sum;
	int i;
	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[2]);
	for (i = 0; i < n1; i++)
		l1.push_back(i + 1);
	for (i = 0; i < n2; i++)
		l2.push_back((i + 1) * 3);

	l1.print();
	l2.print();
	sum_lists(l1, l2, sum);
	sum.print();
	return (0);
}
