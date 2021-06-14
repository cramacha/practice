#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

ostream&
operator <<(ostream &out, const vector<int> &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i] << " ";
	out << endl;
	return (out);
}

ostream&
operator <<(ostream &out, const vector<vector<int> > &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i] << endl;
	return (out);
}

bool
find_path(vector<vector<int> > &adj, int start, int end)
{
	queue<int> q;
	map<int, bool> mp;	

	if (start < 0 || start > adj.size() - 1
			|| end < 0 || end > adj.size() - 1)
		return (false);

	q.push(start);

	while (!q.empty()) {
		int node = q.front();
		q.pop();
		vector<int> neighbors = adj.at(node);
		for (int i = 0; i < neighbors.size(); i++) {
			int neighbor = neighbors.at(i);

			/*  We found the end. */
			if (neighbor == end)
				return (true);
			
			/*  We visited this fellow before. */
			if (mp.find(neighbor) != mp.end())
				continue;

			q.push(neighbor);	
		}
		mp[node] = true;
	}
	return (false);
}

int
main(int argc, char **argv)
{
	vector<vector<int> > adj;

	for (int i = 0; i < 6; i++) {
		vector<int> al;
		adj.push_back(al);
	}

	adj.at(0).push_back(1);
	adj.at(0).push_back(2);
	adj.at(0).push_back(3);
	adj.at(2).push_back(3);
	adj.at(2).push_back(4);
	adj.at(3).push_back(4);
	adj.at(4).push_back(5);

	cout << "Printing graph: " << adj << endl;
	bool ret = find_path(adj, 0, 5);
	ret = find_path(adj, 4, 3);
	return (0);
}
