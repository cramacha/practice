#include <iostream>
#include <string>
#include <set>

using namespace std;

ostream&
operator <<(ostream &out, set<string> &elements)
{
	for (auto &elem: elements)
		out << elem << endl;
	return (out);
}

void
insert_parens_inside(string input, set<string> &result)
{
	string temp;

	if (input.size() == 0)
		return;

	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '(')
		{
			string before = input.substr(0, i + 1);
			string after = input.substr(i + 1);
			temp = before + "()" + after;
			result.insert(temp);
		}
	}
}

set<string>
parens_impl(int n)
{
	set<string> result;
	if (n == 0)
	{
		result.insert("");
		return (result);
	}

	set<string> prev = parens_impl(n - 1);
	for (auto &elem : prev)
	{
		string prepend = "()" + elem;
		result.insert(prepend);
		insert_parens_inside(elem, result);
	}

	return (result);
}

void
parens(int n)
{
	set<string> result = parens_impl(n);
	cout << result << endl;
}

int main(int argc, char **argv)
{
	int n = atoi(argv[1]);

	parens(n);
	return (0);
}
