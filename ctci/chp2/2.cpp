#include <list>
#include <iostream>

using namespace std;

void
print_list(list<int> &l)
{
	for (auto &elem: l)
		cout << elem << " ";
	cout << endl;	
}

void
find_kth_to_last(list<int> &l, int k)
{
	list<int>::iterator it1 = l.begin();
	list<int>::iterator it2 = next(it1, k);

	for (; it1 != l.end(); it1++, it2++);

	cout << "kth to last: " << *it2 << endl;
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	list<int> l;
	for (int i = 0; i < n; i++)
		l.push_front(i);
	print_list(l);
	find_kth_to_last(l, k);
	return (0);
}
