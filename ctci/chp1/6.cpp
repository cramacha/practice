#include <queue>
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

string
compress1(string &s)
{
	string result;
	queue<pair<char, int> > q;
	pair<char, int> p;
	(void) bzero (&p, sizeof (p));
	int i = 1;
	p.first = s[0];
	p.second = 1;
	while (i <= s.size()) {
		if (s[i] == s[i - 1]) {
			p.second++;	
		} else {
			q.push(p);
			p.first = s[i];
			p.second = 1;
		}
		i++;
	}

	/*  Check if compressed string len is > original length. */
	if (2 * q.size() >= s.size())
		return (s);

	while (!q.empty()) {
		pair<char, int> p = q.front();
		result += p.first;
		result += to_string(p.second);
		q.pop();	
	}
	return (result);
}

int
main(int argc, char **argv)
{
	string s(argv[1]);
	cout << compress1(s) << endl;
	return (0);
}
