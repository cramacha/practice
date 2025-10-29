#include <iostream>
#include <cstdlib>
#include <map>
#include <cstring>

using namespace std;

void is_perm(char *str, int len) {
	map<char, int> m;
	int odd_count = 0;
	for (int i = 0; i < len; i++) {
		char elem = str[i];
		if (m.find(elem) != m.end())
			m[elem]++;
		else
			m[elem] = 1;
	}

	// at most 1 odd value for a key.
	for (auto &elem: m) {
		if ((elem.second % 2) == 1)
			odd_count++;
	}

	bool ret = (odd_count <= 1);
	cout << "pal perm: " << ret << endl;
}


int main(int argv, char **argc) {
	const char *inp = "malayalam";
	int len = strlen(inp);
    char *str = (char *) malloc(sizeof (inp) * len);
	(void) memcpy(str, inp, len);
	is_perm(str, len); 	
	return (0);
}
