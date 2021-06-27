#ifndef QSORT_H
#define QSORT_H

#include <iostream>
#include <vector>

using namespace std;

ostream&
operator <<(ostream &out, vector<int> &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i] << " ";
	out << endl;
	return (out);
}

void
qsort_impl(vector<int> &inp, int start, int end)
{
	int last;
	if (start >= end)
		return;
	swap(inp[start], inp[(start + end)/2]);
	last = start;
	for (int i = start + 1; i <= end; i++)
	{
		if (inp[i] < inp[start])
		{
			last++;
			swap(inp[i], inp[last]);
		}
	}
	swap(inp[start], inp[last]);
	qsort_impl(inp, start, last - 1);
	qsort_impl(inp, last + 1, end);
}
	
void
qsort(vector<int> &inp)
{
	qsort_impl(inp, 0, inp.size() - 1);
}

#endif /*  QSORT_H */
