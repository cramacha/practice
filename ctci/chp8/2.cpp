#include <iostream>
#include <vector>
#include <set>

using namespace std;

ostream&
operator <<(ostream &out, const vector<pair<int, int> > &vp)
{
	for (auto &it: vp)
	{
		cout << it.first << " " << it.second << endl;
	}
	
	return (out);
}

ostream&
operator <<(ostream &out, const set<pair<int, int> > &sp)
{
	for (set<pair<int, int> >::iterator it = sp.begin(); it != sp.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}

	return (out);
}

void
find_path_impl(set<pair<int, int> > &obstacles, set<pair<int, int> > &visited, vector<pair<int, int> > &path, pair<int, int> &loc, int rows, int cols)
{
	int row = loc.first;
	int col = loc.second;

	if (row < 0 || row > rows - 1 || col < 0 || col > cols - 1)
		return;

	if (row == rows - 1 && col == cols - 1) 
	{
		cout << "Path found! " << endl;
		cout << path << endl;
		return;
	}

	if (visited.find(loc) != visited.end() 
			|| obstacles.find(loc) != obstacles.end()) {
		return;
	}
	
	visited.insert(loc);
	path.push_back(loc);
	
	loc.first++;
	find_path_impl(obstacles, visited, path, loc, rows, cols);

	loc.first--;
	find_path_impl(obstacles, visited, path, loc, rows, cols);
	
	loc.second++;
	find_path_impl(obstacles, visited, path, loc, rows, cols);
	
	loc.second--;
	find_path_impl(obstacles, visited, path, loc, rows, cols);
	
	path.pop_back();
}

void
find_path(set<pair<int, int> > &obstacles, int rows, int cols)
{
	vector<pair<int, int> > path;
	pair<int, int> start(0, 0);
	set<pair<int, int> > visited;
	find_path_impl(obstacles, visited, path, start, rows, cols);
}

int main(int argc, char **argv)
{
	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);

	set<pair<int, int> > obstacles;
	cout << "Total rows: " << rows << " and columns: " << cols << endl;

	// Setup obstacles.
	for (int i = 0; i < rows; i++)
	{
		pair<int, int> obstacle_point(rand() % rows, rand() % cols);
		if (obstacles.find(obstacle_point) == obstacles.end()) {
			obstacles.insert(obstacle_point);
		}
	}

	cout << "Printing obstacles" << endl;
	cout << obstacles << endl;

	cout << "Finding path" << endl;
	find_path(obstacles, rows, cols);
	return (0);
}
