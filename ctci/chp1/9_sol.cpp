/*
 *
 * Write a function to determine if one string is a rotation of another. Example 
 * "waterbottle" and "erbottlewat".
 *
 */
#include <iostream>
#include <string>

using namespace std;

bool
is_rotation(string &s1, string &s2)
{
	/*
	 * s1 = water
	 * s2 = erwat
	 * ss = waterwater (s2 is found here)
	 *
	 * s1 = water
	 * s2 = ertaw
	 * ss = waterwater (s2 is not found here)
	 *
	 */
	string ss = s1 + s1;
	return (ss.find(s2) != string::npos);
}

int
main(int argc, char **argv)
{
	string s1(argv[1]);
	string s2(argv[2]);
	bool result = is_rotation(s1, s2);
	cout << s1 << " " << s2 << endl;
	cout << ((result == true)? " is rotation" : " not a rotation") << endl;
	return (0);
}
