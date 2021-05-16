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
build_cur(vector<string> &cur, vector<string> &prev, char c)
{
	for(auto &perm: prev)
	{
		perm = c + perm;
		cur.push_back(perm);
	}
}

vector<string>
permutations_impl(string input)
{
	vector<string> cur;
	if (input.size() == 0)
	{
		return (vector<string>({""}));
	}
	
	for (int i = 0; i < input.size(); i++)
	{
		char c = input[i];
		string before = input.substr(0, i);
		string after = input.substr(i + 1);
		vector <string> prev = permutations_impl(before + after);
		build_cur(cur, prev, c);
	}

	return (cur);
}

void
permutations(string &input)
{
	vector<string> result = permutations_impl(input);
	cout << "result:" << endl << result << endl;
}

int
main(int argc, char **argv)
{
    string inp(argv[1]);
	permutations(inp);
	return (0);
}
