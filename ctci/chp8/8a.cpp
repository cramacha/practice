#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

ostream&
operator <<(ostream &out, vector<string> &arr)
{
	for (int i = 0; i < arr.size(); i++)
		out << arr[i] << endl;
	return (out);
}

void
perm_impl(string prefix, map<char, int> &mp, int rem, vector<string> &result)
{
	if (rem == 0)
	{
		result.push_back(prefix);
		return;
	}

	for (auto &elem : mp)
	{
		if (elem.second > 0)
		{
			elem.second--;
			perm_impl(prefix + elem.first, mp, rem - 1, result);
			elem.second++;
		}
	}
}

void
build_counts(string &inp, map<char, int> &mp)
{
	int key_count = 0;
	for (int i = 0; i < inp.size(); i++)
	{
		if (mp.find(inp[i]) != mp.end())
			mp[inp[i]]++;
		else
			mp[inp[i]] = 1;
	}
}

void
perm(string &input)
{	
	string prefix;
	vector<string> result;
	map<char, int> mp;
	build_counts(input, mp);
	perm_impl(prefix, mp, input.size(), result);
	cout << "result: " << result << endl;
}

int main(int argc, char **argv)
{
	string input(argv[1]);
	perm(input);
	return (0);
}
