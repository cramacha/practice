/*
 * Given a string S, find the length of the minimum balanced fragment.
 *
 * If no fragment is available, return -1.
 *
 * Example, aaABaab. Output is 5, "ABaab"
 *
 * Definition of balanced: A fragment should have the lowercase and 
 * corresponding uppercase character for all pairs. The number of repititions 
 * doesnt matter.
 *
 * Another example, azACB, output is -1 because z, C, B dont have their 
 * counterparts.
 * 
 * Assumptions: Alphabet set is [a-z] and [A-Z]
 */

#include <vector>
#include <ctype.h>
#include <string>
#include <iostream>

using namespace std;

int CHARSET_SIZE = 52;

bool
check_pairs(vector<bool> &char_map)
{
	int i;
	int j;
	for (i = 0, j = CHARSET_SIZE/2 ; i < CHARSET_SIZE/2 && j < CHARSET_SIZE; i++, j++) {
		if (char_map[i] != char_map[j])
			return (false);
	}
	return (true);
}

/*
 * We parse a substring, and set their availability as true/false in a 
 * vector (of size 52 - 26 lowercase and remaining uppercase characters). We 
 * then parse each one and check for mismatch.
 */
bool
is_balanced(string &s, int i, int j, vector<bool> &char_map)
{
	int k = 0;
	int l = 0;
	char upper;
	for (k = i; k <=j; k++) {
		if (islower(s[k]))
			char_map[s[k] % 'a'] = true;
		else
			char_map[(s[k] % 'A') + 26] = true;
	}

	return (check_pairs(char_map));
}

int
solution(string &s)
{
	int local_min = INT_MAX;
	int global_min = INT_MAX;
	int len = s.size() - 1;
	vector<bool> char_map(CHARSET_SIZE, false);
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j <= len; j++) {
			if (is_balanced(s, i, j, char_map)) {
				local_min = j - i + 1;
				global_min = min(local_min, global_min);
			}
			fill(char_map.begin(), char_map.end(), false);
		}
	}
	return ((global_min == INT_MAX)? -1: global_min);
}

int
main(int argc, char **argv)
{
	string s = "ABaab";
	int min = solution(s);
	cout << "min length = " << min << endl;
	return (0);
}
