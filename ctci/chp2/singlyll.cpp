#include "singlyll.h"

int main(int argc, char **argv) {
	node<int> *p = new node<int>(5);

	list<int> *l = new list<int>();

	l->push_back(5);
	l->print();

	l->push_back(2);
	l->push_back(3);
	l->print();

	l->push_front(1);
	l->print();

	l->pop_back();
	l->print();

	l->pop_front();
	l->print();

	cout << "found element: " << l->at(1)->val << endl;

	cout << "list size = " << l->size() << endl;

	l->ordered_insert(3);
	l->print();

	l->ordered_insert(1);
	l->print();

	list<int> *l2 = new list<int>();

	l2->push_back(5);
	l2->push_back(6);
	l2->push_back(7);

	l->append(*l2);
	l->print();

	
	l->pop_back();
	l->print();
	l->pop_back();
	l->print();
	l->pop_back();
	l->print();
	
	l->reverse();
	l->print();

	l->reverse();
	l->print();
	return (0);
}