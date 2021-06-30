#include <iostream>
#include "../../utils/stack.h"

using namespace std;

/*
 * This chooses the smallest element in main stack s1.
 */
void
sort_impl(stack<int> &s1, stack<int> &s2, int total, int *smaller)
{
	*smaller = s1.top();
	s1.pop();
	while (total > 0) {
		int top = s1.top();
		if (top < *smaller)
			*smaller = top;
		s1.pop();
		s2.push(top);
		total--;		
	}
	s1.push(*smaller);
}

/*
 * This pushes all the elements from auxiliary stack s2 to s1.
 */
void
push_remaining(stack<int> &s1, stack<int> &s2)
{
	while (s2.size() > 0) {
		int top = s2.top();
		s2.pop();
		s1.push(top);
	}
}

/*
 * Main function to sort. We use an auxiliary stack to assist us in sorting.
 *
 * e.g. s1 = {3, 2, 1}, s2 = {}
 * 
 * 1. After sort_impl function, s1 = {1}, s2 = {2, 3}
 * 2. After push_remaining function, s1 = {1, 2, 3}, s2 = {}
 * 3. Repeat for remaining unsorted elements in s1 (2 and 3).
 */
void
sort(stack<int> &s1)
{
	stack<int> s2;
	int total = s1.size() - 1;
	int *smaller = new int;

	while (total > 0) {
		sort_impl(s1, s2, total, smaller);
		push_remaining(s1, s2);
		cout << s1 << endl;
		total--;
	}
}

int
main(int argc, char **argv)
{
	stack<int> s1;
	int i;
	int n = atoi(argv[1]);
	for (i = n; i >= 0; i--)
		s1.push(i);
	cout << s1 << endl;
	sort(s1);
	cout << s1 << endl;
	
	return (0);
}
