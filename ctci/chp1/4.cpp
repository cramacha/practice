#include <iostream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

bool
is_palindrome_perm(string &inp)
{
	int i;
	int odd_count = 0;
	map<char, int> m;
	for (i = 0; i < inp.size(); i++) {
		if (!isalpha(inp[i]))
			continue;
		if (m.find(inp[i]) != m.end())
			m[inp[i]]++;
		else
			m[inp[i]] = 1;
	}

	for (auto &elem: m) {
		if (elem.second % 2 == 1)
			odd_count++;
	}
	return (odd_count <= 1);
}

int
main(int argc, char **argv)
{
	/*
	 * e.g. malayalam.
	 *
	 * inp = yaallmmaa
	 */
	string inp(argv[1]);
	cout << is_palindrome_perm(inp) << endl;
	return (0);
}
