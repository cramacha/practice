#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

ostream&
operator <<(ostream &out, vector<string>& inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i] << " ";
	out << endl;
	return (out);
}

void
anagrams(vector<string> &input)
{
	map<string, vector<string> > anagram_map;
	vector<string> output;
	for (int i = 0; i < input.size(); i++)
	{
		string orig = input[i];
		sort(input[i].begin(), input[i].end());
		anagram_map[input[i]].push_back(orig);
	}

	for (auto &elem: anagram_map)
	{
		for (auto &anagram: elem.second)
			output.push_back(anagram);
	}

	cout << output << endl;
}

int
main(int argc, char **argv)
{
	vector<string> input({
		"abc",
		"nam",
		"tap",
		"cba",
		"man",
		"apt"
	});
	cout << input << endl;
	anagrams(input);
	return (0);
}
