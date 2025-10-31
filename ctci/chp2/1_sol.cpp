/*
 * Write a function to remove duplicate elements in an unsorted linked list. Follow up: How would you solve it without a temporary array?
 */
#include <stdlib.h>
#include <iostream>
#include <list>
#include <map>

using namespace std;

void print_list(list<int> &l) {
	for (auto &elem: l) {
		cout << elem << " ";
	}
	cout << endl;
}

void remove_dups1(list<int> &l) {
	map<int, bool> m;
	list<int>::iterator it1;
	for (it1 = l.begin(); it1 != l.end(); it1++) {
		/* 
		if (m.find(*it1) != m.end()) {
			l.erase(it1);
		}
		else
			m[*it1] = true;
		*/
		cout << " elem = " << *it1 << endl;
		//l.erase(it1);
		print_list(l);
	}	
}

void remove_dups2(list<int> &l) {
	l.sort();
	list<int>::iterator i, n;
	for (i = l.begin(); i!= l.end(); i++) {
		n = next(i, 1);
		if ((i != l.end() && (*n == *i)))
			l.erase(i);
	}	
}


int main(int argv, char **argc) {
	list<int> l;
	int len = atoi(argc[1]);
	for (int i = 0; i < len; i++) {
		l.push_front(i);
	}
	print_list(l);
	cout << "adding duplicate " << endl;
	l.push_front(0);
	print_list(l);
	cout << "removing dups" << endl;
	remove_dups1(l);
	print_list(l);

	cout << "adding duplicate " << endl;
	l.push_front(1);
	cout << "removing dups2" << endl;
	remove_dups2(l);
	print_list(l);
	return (0);
}
