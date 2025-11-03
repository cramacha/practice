#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <math.h>

using namespace std;


ostream&
operator <<(ostream &out, vector<vector<int> > vec) {
	int i, j;

	for (i = 0; i < vec.size(); i++) {
		out << i << " -> ";
		for (j = 0; j < vec.at(i).size(); j++) {
			out << vec.at(i).at(j) << " ";
		}
		out << endl;
	}

	return (out);
}

bool
find_paths(vector<vector<int> > adj, int start, int end) {
	queue<int> q;
	int front;
	int neighbor;
	int i;
	unordered_map<int, bool> mp;

	if (start < 0 || start > adj.size() || end > adj.size() 
			|| end < 0)
			return (false);

	q.push(start);

	while (!q.empty()) {
		front = q.front();
		q.pop();

		for (i = 0; i < adj.at(front).size(); i++) {
			neighbor = adj.at(front).at(i);

			if (neighbor == end)
				return (true);

			if (mp.find(neighbor) != mp.end())
				continue;

			q.push(neighbor);
		}
		mp[front] = true;
	}

	return (false);
}

int main(int argc, char **argv) {
	vector<vector<int> > vec;
	for (int i = 0; i < 9; i++) {
		vector<int> v;
		for (int j = 0; j < 9; j++) {
			v.push_back(rand() % 9);
		}
		vec.push_back(v);
	}

	cout << vec << endl;

	cout << find_paths(vec, 1, 4) << endl;
	return (0);
}