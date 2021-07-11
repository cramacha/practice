#include <iostream>
#include <vector>

using namespace std;

ostream &
operator <<(ostream &out, const vector<int> &v)
{
	int i;
	for (i = 0; i < v.size(); i++)
		out << v[i] << " ";
	out << endl;
	return (out);
}

bool
binsearch_impl(vector<int> &v, int elem, int left, int right)
{
	int mid;

	if (left > right)
		return (false);
	mid = (left + right) >> 1;
	if (v[mid] == elem)
		return (true);
	else if (v[mid] < elem)
		return (binsearch_impl(v, elem, mid + 1, right));
	else
		return (binsearch_impl(v, elem, left, mid - 1));
}


void
binsearch(vector<int> &v, int elem)
{
	bool ret = binsearch_impl(v, elem, 0, v.size() - 1);
	cout << ret << endl;
}

int
main(int argc, char **argv)
{
	vector<int> v;
	int n = atoi(argv[1]);
	int elem = atoi(argv[2]);
	int i;
	for (i = 0; i < n; i++)
		v.push_back(rand() % n);

	cout << v << endl;
	cout << "To search: " << elem << endl;
	binsearch(v, elem);
	return (0);
}
