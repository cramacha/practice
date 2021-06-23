#include "../../utils/sll.h"

int
main(int argc, char **argv)
{
	list<int> l;

	/*  push and pop methods. */
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_front(1);

	l.print();
	l.pop_front();
	l.pop_front();

	l.print();
	l.pop_front();
	l.pop_front();
	l.print();
	
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_front(1);

	l.print();
	
	l.pop_back();
	l.pop_back();
	
	l.print();
	l.pop_back();	
	l.pop_front();
	
	l.print();
	l.pop_front();

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_front(1);

	l.print();
	l.reverse();
	l.print();
	node<int> *pn = l.at(2);
	cout << pn->val << endl;

	return (0);
}
