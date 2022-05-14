/*
 * Given a string, write a function to determine if it is a permutation of a palindrome.
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

/*
 * E.g. "yaallmmaa" --> "malayalam".
 * and "baab" or "abba".
 *
 * Put all characters in a map, and check if only one or less key-value has odd count.
 */
bool
is_perm(string &s)
{
	int odd_count = 0;
	map<char, int> m;

	for (auto &elem: s)
	{
		if (m.find(elem) != m.end())
			m[elem]++;
		else
			m[elem] = 1;
	}

	for (auto &elem: m)
	{
		if (elem.second % 2 == 1)
			odd_count++;
	}

	return (odd_count <= 1);
}

int
main(int argc, char **argv)
{

	string s(argv[1]);
	cout << (is_perm(s) == 1? "Permutation" : "No permutation") << endl;
	return (0);
}
