#include <iostream>
#include <list>
#include <math.h>

using namespace std;

void
print(list<int> &l)
{
	for (auto &elem: l)
		cout << elem << " ";
	cout << endl;
}

/*
 * Logic is:
 *
 * 1) Identify smaller and larger list
 * 2) Move larger by X where X is delta between size of both.
 * 3) Check each element of smaller and larger and find intersection.
 */
bool
intersect_list(list<int> &l1, list<int> &l2, int *intersect)
{
	int i;
	list<int> s, l;
	list<int>::iterator i1;
	list<int>::iterator i2;

	int len1 = l1.size();
	int len2 = l2.size();
	
	if (len1 > len2) {
		s = l2;
		l = l1;
	} else {
		s = l1;
		l = l2;
	}
	
	int delta = abs(len1 - len2);

	/*  
	 *  This needs to be <= so that larger can move forward to the same head as 
	 *  smaller.
	 */
	for (i1 = l.begin(), i = 0; i <= delta; i1++, i++);

	for (i2 = s.begin(); i1 != l.end() && i2 != l.end(); i1++, i2++) {
		if (*i1 == *i2) {
			*intersect = *i1;
			return (true);
		}
	}
	return (false);

}

int
main(int argc, char **argv)
{
	int intersect;
	list<int> l1, l2;
	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[2]);
	int i;

	for (i = 0; i < n1; i++)
		l1.push_back(i + 3);

	for (i = 0; i < n2; i++)
		l2.push_back((i + 1 * 9));
		
	print(l1);
	list<int>::iterator it2;
	it2 = next(l2.begin(), 3);
	*it2 = 3;
	it2 = next(it2, 1);
	*it2 = 4;
	it2 = next(it2, 1);
	*it2 = 5;
	it2 = next(it2, 1);
	*it2 = 6;

	print(l2);
	bool ret = intersect_list(l1, l2, &intersect);
	cout << "ret = " << ret << endl;
	return (0);
}
