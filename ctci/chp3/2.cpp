#include "../../utils/stack.h"

/*
 * To get min in O(1) from this stack data structure:
 *
 * 1. Create 2 stacks - original and minimum stack. The latter
 *    maintains min in O(1) time.
 * 2. For push operation, always push to original stack. Push to
 *    minimum stack if value is less than its top. Increment its top's
 *    counter if val is equal to its top. (This handles duplicate 
 *    elements)
 * 3. For pop operation, always pop from original stack. Pop from
 *    minimum stack if the latters top is less than original stack's top.
 */

ostream&
operator <<(ostream& out, const stack<pair<int, int> > &s)
{
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < s.data[i].second; j++)
			out << s.data[i].first << " ";
	}
	out << endl;
	return (out);
}

void
push(stack<int> &orig, stack<pair<int, int> > &mins, int val)
{
	orig.push(val);

	if (mins.size() == 0 || val < mins.top().first) {
		mins.push(make_pair(val, 1));
		return;
	}

	if (val > mins.top().first)
		return;

	if (val == mins.top().first) {
		int top = mins.top().second;
		mins.data.back().second++;
	}
}

void
pop(stack<int> &orig, stack<pair<int, int> > &mins)
{
	if (orig.size() == 0)
		return;
	int top = orig.top();
	orig.pop();

	/*  
	 *  Orig's top will never be < mins top because of the way
	 *  we have implemented the push operation above.
	 */
	if (top > mins.top().first)
		return;

	if (top == mins.top().first && --mins.data.back().second == 0)
		mins.pop();
}

void
print_mins(stack<pair<int, int> > &mins)
{
	cout << mins.top().first << " ";
}

int
main(int argc, char **argv)
{
	stack<int> orig;
	stack<pair<int, int> > mins;
	int i;
	int n = atoi(argv[1]);
	for (i = 0; i < n; i++)
	   push(orig, mins, i);

	cout << "orig: " << orig << endl;	
	cout << "mins: " << mins << endl;

	/*
	 * The objective of this while loop is to print the min after
	 * popping every element of the orig stack.
	 */
	while (orig.size() > 0) {
		print_mins(mins);
		pop(orig, mins);	
	}
	cout << endl;
	return (0);
}
