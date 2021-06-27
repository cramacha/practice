#include "stack.h"

int
main(int argc, char **argv)
{
	stack<int> s;
	int i;
	int n = atoi(argv[1]);
	for (i = 0; i < n; i++)
		s.push(i);

	cout << s << endl;
	s.pop();
	cout << s << endl;
	cout << s.top() << endl;
	s.empty();
	
	cout << s << endl;
	return (0);
}
