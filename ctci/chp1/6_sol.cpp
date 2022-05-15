/*
 * Write a function to compress a string, replacing all duplicates of a given 
 * character with the number of times it occurs consecutively and then a single 
 * instance of the character instead. If the compressed string is longer than 
 * the original, then just return the original.
 */
#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <cassert>

using namespace std;

string
compress(string &s)
{
	pair <char, int> p;
	queue <pair <char, int> > q;
	int i = 1;
	int len = s.size();
	string result;
	(void) bzero(&p, sizeof (p));

	p.first = s[0];
	p.second = 1;

	while (i < len)
	{
		if (s[i] == s[i - 1])
			p.second++;
		else
		{
			q.push(p);
			p.first = s[i];
			p.second = 1;		
		}
		i++;
	}

	q.push(p);

	while (!q.empty())
	{
		pair <char, int> elem = q.front();
		result += elem.first;
		result += to_string(elem.second);
		q.pop();
	}
	
	return ((result.size() > len)? s: result);
}

int
main(int argc, char **argv)
{
	string s(argv[1]);
	string result = compress(s);
	cout << "orig = " << s << endl << " result = " << result << endl;
	return (0);
}
