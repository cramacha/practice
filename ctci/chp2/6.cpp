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

bool
is_palin(list<int> &l)
{
	list<int>::iterator it;
	list<int> tmp;
	list<int>::iterator it2;
	int i = 0;
	int len = l.size();
	
	/*
	 * e.g. l = {0, 1, 2, 1, 0}
	 *
	 * We only need to loop through half the elements in
	 * the list.
	 * After completion of loop:
	 * l = {2, 1, 0}
	 * tmp = {1, 0}
	 *
	 */
	for (it = l.begin(); i < len/2; it++, i++) {
		tmp.push_front(*it);
		l.pop_front();
	}

	/*
	 * Need to pop the front element (2 - from above
	 * example) so that:
	 * l = {1, 0}
	 * tmp = {1, 0}
	 */
	if (len % 2)
		l.pop_front();

	for (it2 = tmp.begin(), it = l.begin();
			it2 != tmp.end(); it2++, it++) {
		if (*it != *it2)
			return (false);
	}
	return (true);
}

int
main(int argc, char **argv)
{
	list<int> l;
	l.push_back(0);
	l.push_back(1);
	l.push_back(2);
	l.push_back(1);
	l.push_back(0);
	print(l);
	cout << "is_palin:" << is_palin(l) << endl;
	l.push_back(0);
	print(l);
	cout << "is_palin:" << is_palin(l) << endl;
	return (0);
}
