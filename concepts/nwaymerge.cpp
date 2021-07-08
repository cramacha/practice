#include "../utils/heap.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * This merges n sorted arrays using both the custom heap
 * implemented by us as well as the heap functionality
 * provided by STL.
 *
 * STL's heap implementation is a max heap.
 * We need a custom comparator to do a min heap.
 * Note that std::sort sorts in ascending order.
 */
bool
compare(const pair<int, int> &a, const pair<int, int> &b)
{
	/*  This is checking if a > b and not the other way around. */
	return (a.first > b.first);
}

ostream &
operator << (ostream &out, const vector<int> &a)
{
	for (int i = 0; i < a.size(); i++)
		out << a[i] << " ";
	out << endl;
	return (out);
}

ostream &
operator << (ostream &out, const vector<vector<int> > &a)
{
	for (int i = 0; i < a.size(); i++)
		out << a[i] << " ";
	out << endl;
	return (out);
}

void
nway_merge(vector<vector<int> > &vv)
{
	vector<int> res;
	vector<pair<int, int> > heap;
	int i, val;
	pair<int, int> tmp;

	for (i = 0; i < vv.size(); i++) {
		val = vv[i][0];
		pair<int, int> p = make_pair(val, i);
		heap.push_back(p);
		vv[i].erase(vv[i].begin());
	}
	make_heap(heap.begin(), heap.end(), compare);

	while (!heap.empty()) {
		tmp = heap[0];
		i = tmp.second;
		res.push_back(tmp.first);
		
		/*
		 * Note that we need to remove the last element after we have
		 * performed the pop_heap operation.
		 */
		pop_heap(heap.begin(), heap.end(), compare);
		heap.pop_back();
		
		if (!vv[i].empty()) {
			tmp.first = vv[i][0];
			heap.push_back(tmp);
			push_heap(heap.begin(), heap.end(), compare);
			vv[i].erase(vv[i].begin());
		}
	}

	cout << endl << "Result:" << endl << res << endl;
}

int
main(int argc, char **argv)
{
	vector<vector<int> > vv;
	int i, j;
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	for (i = 0; i < m; i++) {
		vector<int> v;
		for (j = 0; j < n; j++)
			v.push_back(rand() % n);
		sort(v.begin(), v.end());
		vv.push_back(v);
	}
	cout << "Input: " << endl << vv << endl;
	nway_merge(vv);
	return (0);
}
