/*
 * Given two strings, check to see if one is a permutation of the other.
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

bool
is_perm(string &s1, string &s2)
{
	map<char, int> m;
	for (auto &elem: s1)
	{
		if (m.find(elem) != m.end())
			m[elem]++;
		else
			m[elem] = 1;
	}

	for (auto &elem: s2)
	{
		if (m.find(elem) != m.end())
		{
			if (m[elem] <= 1)
				m.erase(elem);
			else
				m[elem]--;
		}
	}

	return (m.empty());
}

int
main(int argc, char **argv)
{
	string s1(argv[1]);
	string s2(argv[2]);
	cout << "s1 = " << s1 << endl << " s2 = " << s2 << endl;
	bool result = is_perm(s1, s2);
	cout << ((result == 1)? "Permutation" : "Not permutations") << endl;
	return (0);
}
