/*
 * Given two strings, write a function to determine if they are exactly one
 * edit away from each other, where an edit can be an addition of a single character,
 * the removal of one, or a modification of one (and only one).
 */
#include <iostream>
#include <string>

using namespace std;

bool
is_one_edit(string &s1, string &s2)
{
	bool strike_one = false;
	int i = 0;
	int j = 0;
	int len1 = s1.size() - 1;
	int len2 = s2.size() - 1;
	string smaller = (len1 >= len2)? s2 : s1;
	string larger = (len1 >= len2)? s1: s2;
	while (i <= smaller.size())
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
		{
			/*
			 * Only 1 edit is allowed so return false;
			 */
			if (strike_one)
				return (false);

			strike_one = true;

			if (len1 == len2)
			{
				i++;
				j++;
			}
			else
			{
				/*
				 * Move pointer to larger string further up to check the next 
				 * character.
				 */
				j++;
				continue;
			}
		}
	}
	return (true);
}

int
main(int argc, char **argv)
{
	string s1(argv[1]);
	string s2(argv[2]);
	bool result = is_one_edit(s1, s2);
	cout << s1 << endl << s2 << endl;
	cout << ((result == 1)?  "Yes": "No") << endl;
	return (0);
}
