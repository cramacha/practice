#include <iostream>
#include <vector>
#include <set>

using namespace std;

ostream &
operator << (ostream &out, const vector<int> &v)
{
	int i;
	for (i = 0; i < v.size(); i++)
		out << v[i] << " ";
	out << endl;
	return (out);
}

ostream &
operator << (ostream &out, const set<vector<int> > &inp)
{
	for (auto &elem: inp) {
		out << elem << endl;
	}
	return (out);
}

void
perm_impl(vector<int> &v, set<vector<int> > &res, int off)
{
	int i;
	if (off >= v.size()) {
		res.insert(v);
		return;
	}

	for (i = off; i < v.size(); i++) {
		swap(v[i], v[off]);
		perm_impl(v, res, off + 1);
		swap(v[i], v[off]);
	}
}

void
perm(vector<int> &v)
{
	set<vector<int> > res;
	perm_impl(v, res, 0);
	cout << res << endl;
}

void
ncr_impl(vector<int> &v, vector<int> &tmp, set<vector<int> > &res, int off, int r)
{
	int i;

	if (tmp.size() == r) {
		res.insert(tmp);
		return;
	}

	for (i = off; i < v.size(); i++) {
		tmp.push_back(v[i]);
		ncr_impl(v, tmp, res, off + 1, r);
		tmp.pop_back();
	}
}

void
ncr(vector<int> &v, int r)
{
	set<vector<int> > res;
	vector<int> tmp;
	ncr_impl(v, tmp, res, 0, r);
	cout << res << endl;
}

int
main(int argc, char **argv)
{
	vector<int> v;
	int n = atoi(argv[1]);
	int r = atoi(argv[2]);
	int i;

	for (i = 0; i < n; i++)
		v.push_back(rand() % n);
	cout << "Input" << endl;
	cout << v << endl;
	cout << "Perm" << endl;
	perm(v);
	cout << "ncr" << endl;
	ncr(v, r);
	return (0);
}
