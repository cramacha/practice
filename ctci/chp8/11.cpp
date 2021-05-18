#include <iostream>
#include <vector>

using namespace std;

ostream&
operator <<(ostream& out, vector<pair<int, int> > &path)
{
	for (int i = 0; i < path.size(); i++)
		out << path[i].first << " " << path[i].second << endl;
	return (out);
}

int
make_change_impl(int total, vector<int> &change, int index,
	   vector<pair<int, int> > &path)
{
	int ways = 0;
	if (total == 0)
	{
		cout << path << endl;
		return (1);
	}	

	if (index == change.size())
	{
		return (0);
	}

	int change_amount = change[index];
	for (int i = 0; i * change_amount <= total; i++)
	{
		int remaining = total - (i * change_amount);
		path.push_back(make_pair(change_amount, i));
		ways += make_change_impl(remaining, change, index + 1, path);
		path.pop_back();
	}

	return (ways);	
}

int
make_change(int n, vector<int> &change)
{
	vector<pair<int, int> > path;
	return (make_change_impl(n, change, 0, path));
}

int
main(int argc, char **argv)
{
	vector<int> change = {25, 10, 5, 1};
	int n = atoi(argv[1]);
	int ways = make_change(n, change);
	cout << "ways = " << ways << " n = " << n << endl;
	return (0);
}
