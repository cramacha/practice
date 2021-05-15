#include <iostream>
#include <string>
#include <vector>

using namespace std;

ostream&
operator <<(ostream &out, vector<string> &arr)
{
	for (int i = 0; i < arr.size(); i++)
		out << arr[i] << endl;
	return (out);
}

void
permutations_impl(string input, string prefix, vector<string> &result)
{
	if (input.size() == 0) 
	{ 
		result.push_back(prefix);
		return;
	}

	for (int i = 0; i < input.size(); i++)
	{
		char c = input[i];
		string before = input.substr(0, i);
		string after = input.substr(i + 1);
		permutations_impl(before + after, prefix + c, result); 
	}
}

void
permutations(string &input)
{
	vector<string> result;
	string prefix;
	permutations_impl(input, prefix, result);
	cout << result;
}

int
main(int argc, char **argv)
{
	string input(argv[1]);

	permutations(input);
	return (0);
}
