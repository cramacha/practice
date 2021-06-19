#include <iostream>
#include <string>

using namespace std;

bool
is_rotation(string &s1, string &s2)
{
	/*
	 * s1 = waterbottle
	 * s2 = erbottlewat
	 * s2 + s2 = erbottlewaterbottlewat
	 */
	string ss = s2 + s2;
	return (ss.find(s1) != string::npos);
}

int
main(int argc, char **argv)
{
	string s1(argv[1]), s2(argv[2]);
	cout << is_rotation(s1, s2) << endl;
	return (0);
}
