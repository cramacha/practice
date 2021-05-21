#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

ostream&
operator <<(ostream &out, vector<int> &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i] << " ";
	out << endl;
	return (out);
}

void
initialize(vector<int> &inp, int n)
{
	for (int i = 0; i < n; i++)
		inp[i] = rand() % n;
}

void
merge(vector<int> &a, vector<int> &b, int n)
{
	int last_a = n - 1;
	int last_b = b.size() - 1;
	int last_merged = last_a + last_b + 1;
	
	while (last_b >=0)
	{
		if (a[last_a] < b[last_b])
		{
			a[last_merged] = a[last_a];
			last_a--;
		} 
		else
		{
			a[last_merged] = b[last_b];
			last_b--;
		}
		last_merged--;
	}
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	vector<int> A(n * 2);
	vector<int> B(n);
	initialize(A, n);
	initialize(B, n);
	cout << A << B << endl;
	sort(A.begin(), A.end(), std::greater<int>());
	sort(B.begin(), B.end(), std::greater<int>());
	cout << A << B << endl;
	merge(A, B, n);
	cout << A << endl;
	return (0);
}
