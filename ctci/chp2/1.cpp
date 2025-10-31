#include <iostream>
#include <map>
#include <list>

using namespace std;

void
print_list(list<int> &l)
{
	for (auto &elem: l)
		cout << elem << " ";
	cout << endl;
}

void
remove_dups1(int n)
{
	map<int, bool> m;
	list<int> l;
	for (int i = 0; i < n; i++)
		l.push_front(i);
	l.push_front(0);
	print_list(l);
	
	auto it1 = l.begin();
	for (; it1 != l.end(); it1++) {
		if (m.find(*it1) != m.end()) 
			l.erase(it1);
		else
			m[*it1] = true;
	}
}

void
remove_dups2(list<int> &l)
{
	list<int>::iterator n;
	l.sort();
	for (list<int>::iterator i = l.begin(); i != l.end(); i++) {
		n = next(i, 1);
		if (n != l.end() && *n == *i)
			l.erase(i);
	}
	cout << endl;
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	remove_dups1(n);
	//print_list(l);
	/*
	l.push_front(0);
	print_list(l);
	remove_dups2(l);
	print_list(l);
	*/
	return (0);
}
