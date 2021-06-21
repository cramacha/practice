#include <iostream>
#include <list>

using namespace std;

void
print(list<int> &l)
{
	for (auto &elem: l)
		cout << elem << " ";
	cout << endl;
}

void
delete_node(list<int> &l, int val)
{
	list<int>::iterator it1;
	list<int>::iterator n;

	for (it1 = l.begin(); it1 != l.end(); it1++) {
		n = next(it1, 1);
		if (n != l.end() && *n == val) {
			l.erase(n);
		}
	}	
}

int
main(int argc, char **argv)
{
	list<int> l;
	int val;
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++)
		l.push_back(i);
	print(l);
	val = rand() % n - 1;
	cout << "val: " << val << endl;
	delete_node(l, val);
	print(l);
	return (0);
}
