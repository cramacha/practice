#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

bool
edit1(string &s1, string &s2)
{
	bool strike = false;
	int len1 = s1.size();
	int len2 = s2.size();
	string smaller = (len1 > len2)? s2: s1;
	string larger = (len1 > len2)? s1: s2;
	int i = 0, j = 0;
	while (i < smaller.size())	{
		if (smaller[i] != larger[j]) {	
			/*  There is more than 1 character different. */
			if (strike)
				return (false);

			strike = true;
			if (len1 == len2)
				i++;
			j++;
			continue;
		}
		i++;
		j++;
	}

	return (true);
}

bool
edit_same_len(string &s1, string &s2)
{
	int diff = 0;
	for (int i = 0; i < s1.size(); i++) {
		if (s1[i] != s2[i] && ++diff > 1)
			return (false);
	}
	return (true);
}

bool
edit_diff_len(string &s1, string &s2)
{
	for (int i = 0, j = 0; i < s1.size() && j < s2.size(); i++, j++) {
		if ((s1[i] != s2[j]) && (((++j) - i) > 1))
			return (false);
	}
	return (true);
}

bool
edit2(string &s1, string &s2)
{
	if (s1.size() == s2.size())
		return (edit_same_len(s1, s2));
	else
		return (edit_diff_len(s1, s2));
}

int
main(int argc, char **argv)
{
	string s1(argv[1]), s2(argv[2]);

	int len1 = s1.size();
	int len2 = s2.size();

	if (abs(len1 - len2) > 1)
		return (false);

	cout << "edit algo 1: " << edit1(s1, s2) << endl;
	cout << "edit algo 2: " << edit2(s1, s2) << endl;
	return (0);
}

