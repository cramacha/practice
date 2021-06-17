#include <iostream>
#include <string>
#include <map>
#include <cassert>

using namespace std;

bool
is_perm(string &a, string &b)
{
	map<char, int> m;

	assert(a.size() == b.size());

	for (auto &elem: a) {
		if (m.find(elem) != m.end())
			m[elem]++;
		else
			m[elem] = 1;
	}

	for (auto &elem: b) {
		if (m.find(elem) != m.end()) {
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
	string a(argv[1]);
	string b(argv[2]);
	cout << "a: " << a 
		<< ((is_perm(a, b) == true)? " is perm of": " is not perm of")
		<< " of b: " << b << endl;
	return (0);
}
