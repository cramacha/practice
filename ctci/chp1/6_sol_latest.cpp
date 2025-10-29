/*
 * Write a function to compress a string, replacing all duplicates of a given 
 * character with the number of times it occurs consecutively and then a single 
 * instance of the character instead. If the compressed string is longer than 
 * the original, then just return the original.
 */
#include <iostream>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

string compress(string &s1) {
	pair <char, int> p;
	queue<pair<char, int> > q;
	string ret;
	int i = 1;
	int len = s1.size();
	assert(len > 0);
	(void) bzero(&p, sizeof(p));

	p.first = s1[0];
	p.second = 1;

	while (i < len) {
		if (s1[i] == s1[i - 1])
			p.second++;
		else {
			q.push(p);
			cout << p.first << p.second << endl;
			p.first = s1[i];
			p.second = 1;
		}
		i++;
	}
	
	q.push(p);

	while (!q.empty()) {
		pair<char, int> fr = q.front();
		ret += fr.first + to_string(fr.second);
		q.pop();
	}	

	return ((s1.size() < ret.size())? s1: ret);	
}

int main(int argv, char **argc) {
	string s1(argc[1]);
	cout << "Input = " << s1 << endl;
	cout << "Output = " << compress(s1) << endl;	
}
