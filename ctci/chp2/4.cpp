#include <list>
#include <iostream>

using namespace std;

void
print(list<int> &l)
{
	for (auto &elem: l)
		cout << elem << " ";
	cout << endl;
}

void
partition(list<int> &l, int val)
{
	list<int>::iterator it1;

	for (it1 = l.begin(); it1 != l.end(); it1++) {
		if (*it1 < val) {
			l.erase(it1);
			l.push_front(*it1);
		}
	}
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	int val = 1;
	list<int> l;
	for (int i = 0; i < n; i++)
		l.push_front(i);
	print(l);
	cout << "val = " << val << endl;
	print(l);
	partition(l, val);
	print(l);
	return (0);
}
