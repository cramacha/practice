#include <iostream>
#include <string>
#include <set>

using namespace std;

ostream&
operator <<(ostream &out, set<string> &arr)
{
	for (auto &elem : arr)
		out << elem << endl;
	return (out);
}

void
parens_impl(int left_rem, int right_rem, string prefix, set<string> &result)
{
	if (left_rem <= 0 && right_rem <= 0)
	{
		result.insert(prefix);
		return;
	}

	if (right_rem < left_rem)
		return;

	if (left_rem > 0)
	{
		prefix = prefix + '(';
		parens_impl(left_rem - 1, right_rem, prefix, result);
	}
	
	if (right_rem > 0)
	{
		prefix = prefix + ')';
		parens_impl(left_rem - 1, right_rem - 1 , prefix, result);
	}
}

void
parens(int n)
{
	string prefix;
	set<string> result;
	parens_impl(n, n, prefix, result);
	cout << result << endl;
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	parens(n);
	return (0);
}
