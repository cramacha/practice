#include <iostream>

using namespace std;

void
flip(int num)
{
	int cur = 0;
	int prev = 0;
	int max_len = 0;
	while (num != 0)
	{
		if ((num & 1) == 0)
		{
			prev = ((num & 2) == 0 ? 0: cur);				
			cur = 0;
		}
		else
			cur++;
		num >>= 1;
		max_len = max(1 + prev + cur, max_len);
	}
	cout << max_len << endl;
}

int
main(int argc, char **argv)
{
	int num = atoi(argv[1]);
	flip(num);
	return (0);
}
