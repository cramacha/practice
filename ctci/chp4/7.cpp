#include <iostream>
#include <vector>
#include <set>

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
operator <<(ostream &out, const set<int> &inp)
{
	for (auto &elem: inp)
		out << elem << " ";
	out << endl;
	return (out);
}

ostream&
operator <<(ostream &out, const vector<vector<int> > &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << i << " -->" << inp[i] << endl;
	return (out);
}

bool
build_order_impl(int project, vector<vector<int> > &deps,
		set<int> &visited, set<int> &built, vector<int> &order)
{	
	if (built.find(project) != built.end())
		return (true);
	
	if (visited.find(project) != visited.end())
		return (false);
	
	visited.insert(project);
	for (int i = 0; i < deps[project].size(); i++) {
		int dependency = deps[project].at(i);
		if (!build_order_impl(dependency, deps, visited,
				built, order))
			return (false);	
	}

	built.insert(project);
	order.push_back(project);
	return (true);
}

void
build_adj(vector<pair<int, int> > &deps, 
		vector<vector<int> > &adj)
{
	for (int i = 0; i < deps.size(); i++) {
		if (adj.size() == deps[i].first) {
			vector<int> nv;
			adj.push_back(nv);
		}
		adj[deps[i].first].push_back(deps[i].second);
	}
}

void
build_order(vector<pair<int, int> > &deps,
		vector<int> &projects, vector<int> &order)
{
	vector<vector<int> > adj;
	bool res;
	set<int> visited;
	set<int> built;
	build_adj(deps, adj);
	cout << adj;
	for (int i = 0; i < projects.size(); i++) {
		visited.clear();
		res = build_order_impl(projects[i], adj, visited, built, order);
		cout << projects[i] << " " << 
			((res == true)? "Yes!": "No!") << endl;
	}
}

void
build_input(vector<pair<int, int> > &deps,
	   vector<int> &projects)
{
	for (int i = 0; i < 7; i++)
		projects.push_back(i);

	/*  Here first depends on the second element of pair. */	
	deps.push_back(make_pair(0, 1));
	deps.push_back(make_pair(0, 2));
	deps.push_back(make_pair(1, 3));
	deps.push_back(make_pair(2, 5));
	deps.push_back(make_pair(3, 4));
	deps.push_back(make_pair(4, 6));
	deps.push_back(make_pair(5, 2));
}

int
main(int argc, char **argv)
{
	vector<pair<int, int> > deps;
	vector<int> projects;
	vector<int> order;
	build_input(deps, projects);	
	build_order(deps, projects, order);
	return (0);
}
