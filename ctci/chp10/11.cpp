#include <iostream>
#include <vector>

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
generate(int n, vector<int> &inp)
{
	for (int i = 0; i < n; i++)
		inp[i] = rand() % n;
}

int
biggest_of_three(vector<int> &inp, int i)
{
	int ret = max(inp[i], inp[i - 1]);
	int end_index = (i + 1) % inp.size();
	int maxnum = max(inp[end_index], ret);
	if (maxnum == inp[i])
		return (i);
	else
		return ((maxnum == inp[i - 1])? i - 1: end_index);
}

void
peaks(vector<int> &inp)
{
	int biggest;
	for (int i = 1; i < inp.size(); i+=2)
	{
		biggest = biggest_of_three(inp, i);
		if (biggest != i)
			swap(inp[i], inp[biggest]);
	}
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	vector<int> inp(n, 0);
	generate(n, inp);
	cout << inp;
	peaks(inp);
	cout << inp;
	return (0);
}
