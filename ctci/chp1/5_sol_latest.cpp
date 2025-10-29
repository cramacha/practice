/*
 *
 * Given two strings, write a function to determine if they are exactly one
 * edit away from each other, where an edit can be an addition of a single character,
 * the removal of one, or a modification of one (and only one).
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

bool edit_dist(string &s1, string &s2) {
	int len1 = s1.size();
	int len2 = s2.size();
	cout << "len1 = " << len1 << " len2 = " << len2 << endl;
	int smaller, larger;
	int i = 0, j = 0;
	bool strike_one = false;

	if (len1 <= len2) {
		smaller = len1;
		larger = len2;
	}
	else {
		smaller = len2;
		larger = len1;
	}

	if ((larger - smaller) > 1)
		return (false);

	while (i < smaller) {
		if (s1[i] != s2[j]) {
			if (strike_one)
				return (false);		
			strike_one = true;
		}
		i++;
		j++;
	}

	if (strike_one && (len1 != len2))
		return (false);
	return (true);
}


int main(int argv, char **argc) {
    string s1(argc[1]), s2(argc[2]);
	cout << "string1 = " << s1 << endl << " string2 = " << s2 << endl;
	bool ret = edit_dist(s1, s2);
	cout << "edit dist = " << ret << endl;
	return (0);
}
