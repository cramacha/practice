#include <string>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

bool
is_unique_map(string &inp)
{
	map<char, int> m;
	for (int i = 0; i < inp.size(); i++) {
		if (m.find(inp[i]) != m.end())	
			m[inp[i]]++;
		else
			m[inp[i]] = 1;
	}

	for (auto &elem: m) {
		if (elem.second > 1)
			return (false);
	}
	return (true);
}

bool
is_unique_sort(string &inp)
{
	sort(inp.begin(), inp.end());
	for (int i = 1; i < inp.size(); i++)
		if (inp[i] == inp[i - 1])
			return (false);
	return (true);	
}

int
main(int argc, char **argv)
{
	string inp(argv[1]);
	cout << "map way: is_unique:" << is_unique_map(inp) << endl;
	cout << "sort way: is_unique:" << is_unique_sort(inp) << endl;
	return (0);
}
