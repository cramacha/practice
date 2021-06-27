#include "qsort.h"

int
main(int argc, char **argv)
{
	vector<int> inp(atoi(argv[1]));

	for (int i = 0; i < inp.size(); i++)
		inp[i] = rand() % inp.size() - 1;
	cout << inp;
	qsort(inp);
	cout << inp;
	return (0);
}


