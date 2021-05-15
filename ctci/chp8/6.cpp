#include <iostream>
#include <stack>

using namespace std;

ostream&
operator <<(ostream &out, stack<int> &st)
{
	stack<int> tmp = st;

	while (!tmp.empty())
	{
		out << tmp.top() << " ";
		tmp.pop();
	}
	out << endl;
	return (out);
}

void
move_top(stack<int> &orig, stack<int> &dest)
{
	if (orig.empty())
		return;

	int top = orig.top();
	orig.pop();
	dest.push(top);	
}

void
towers_impl(stack<int> &orig, stack<int> &buf, stack<int> &dest, int n)
{
	if (n <= 0)
		return;
	towers_impl(orig, dest, buf, n - 1);
	move_top(orig, dest);
	towers_impl(buf, orig, dest, n - 1);
}

void
towers(stack<int> &s1, int n)
{
	stack<int> s2, s3;
	towers_impl(s1, s2, s3, n);
	cout << "stack 1 : " << s1 << endl;
	cout << "stack 3 : " << s3 << endl;
}

int main(int argc, char **argv)
{
	int n = atoi(argv[1]);

	stack<int> s1;
	for (int i = n; i >= 1; i--)
		s1.push(i);
	
	cout << "input: " << s1 << endl;
	towers(s1, n);
	return (0);
}
