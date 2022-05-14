/*
 * Algorithm to determine whether or not a string consists of entirely unique characters.
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

bool
is_uniq_map(string &s)
{
	map<char, int> m;
	for (auto &elem: s)
	{
		if (m.find(elem) != m.end())
			return (false);
		else
			m[elem] = 1;
	}
	return (true);
}

bool
is_uniq_sort(string &s)
{
	int i;
	sort(s.begin(), s.end());
	for (i = 1; i <= s.size(); i++)
	{
		if (s[i] == s[i - 1])
			return (false);
	}
	return (true);
}


int
main(int argc, char **argv)
{
	string s(argv[1]);
	cout << "original: " << s << endl;
	cout << "is_uniq_map: " << is_uniq_map(s) << " is_uniq_sort: " << is_uniq_sort(s) << endl;	
	return (0);
}
