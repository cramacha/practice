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

typedef struct heap_elem {
	int val;

	/*  This stores the index of this val in its input array. */
	int index;
} heap_elem_t;

/*
 * For an explanation of this, see our utils/heap.h implementation.
 */
struct heap_elem_compare {
	bool operator()(const heap_elem_t &a, const heap_elem_t &b) {
		return (a.val <= b.val);
	}
};

template <>
struct heap_compare<heap_elem_t> {
	using type = heap_elem_compare;
};

template <class T>
using heap_cmp = typename heap_compare<T>::type;

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

/*  Purely STL implementation. */
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

/*
 *  Implementation using our custom heap.
 *  Logic is similar to the STL implementation.
 */
void
nway_merge_custom(int **input, vector<int> &res, int m, int n)
{
	/*
	 * We use an additional offsets array to store the positions of the
	 * next elements we would need to insert in the heap. Unlike the STL
	 * vector we cannot easily erase an element from the input array.
	 */
	int offsets[m];
	heap<heap_elem_t> *hp;
	int i, j;
	heap_elem_t p;
	heap_elem_t *hp_data;
	heap_cmp<heap_elem_t> cmp;

	if ((hp_data = (heap_elem_t *) malloc(m * sizeof (heap_elem_t))) == NULL) {
		free(hp_data);
		return;
	}
	(void) bzero(hp_data, m * sizeof (heap_elem_t));

	hp = new heap<heap_elem_t>(hp_data, n, cmp);

	if (hp == NULL) {
		delete hp;
		return;
	}
	(void) bzero(offsets, m * sizeof (int));

	for (i = 0; i < m; i++) {
		p.val = input[i][0];
		p.index = i;
		hp->insert(p);
		offsets[i]++;
	}

	while (!hp->empty()) {
		hp->remove(&p);
		i = p.index;
		res.push_back(p.val);
		if (offsets[i] < n) {
			j = offsets[i];
			p.val = input[i][j];
			hp->insert(p);
			offsets[i]++;
		}
	}
	cout << "Result2: " << endl << res << endl;
}

/*
 * Doing swap without additional variables for practice.
 */
void
swap(int *v, int i, int j)
{
	v[i] = (v[i] + v[j]) - (v[j] = v[i]);
}

/*
 * Quicksort impl.
 */
void
q_sort_impl(int *v, int start, int end)
{
	if (start >= end)
		return;
	int last = start;
	int i;
	int mid = (start + end) / 2;
	swap(v, last, mid);
	for (i = start + 1; i <= end; i++) {

		/*
		 * Easy to make a mistake with the last pointer here.
		 * We need to pre-increment it first before swapping.
		 */
		if (v[i] < v[start]) {
			swap(v, i, ++last);
		}
	}
	swap(v, start, last);
	q_sort_impl(v, start, last - 1);
	q_sort_impl(v, last + 1, end);
}

void
q_sort(int *v, int size)
{
	q_sort_impl(v, 0, size - 1);
}

void
print_array(int *vvector, int len)
{
	for (int i = 0; i < len; i++) {
		cout << vvector[i] << " ";
	}
	cout << endl << endl;
}

int
main(int argc, char **argv)
{
	vector<vector<int> > vv;
	int i, j;
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int **vvectors;
	vector<int> res;
	for (i = 0; i < m; i++) {
		vector<int> v;
		for (j = 0; j < n; j++)
			v.push_back(rand() % n);
		sort(v.begin(), v.end());
		vv.push_back(v);
	}

	if ((vvectors = (int **) malloc(m * sizeof (int *))) == NULL) {
		free(vvectors);
		return (0);
	}

	for (i = 0; i < m; i++) {
		vvectors[i] = (int *) malloc(n * sizeof (int));
		(void) bzero(vvectors[i], n * sizeof (int));
	}

	cout << "Input: " << endl << vv << endl;
	nway_merge(vv);

	cout << "Input2: " << endl;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			vvectors[i][j] = rand() % n;
		}
		q_sort(vvectors[i], n);
		print_array(vvectors[i], n);
	}
	nway_merge_custom(vvectors, res, m, n);
	free(vvectors);
	return (0);
}
