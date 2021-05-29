#include <iostream>

using namespace std;

void
merge(int *m, int *n, int j, int i)
{
	int k;
	int mask = 0x7FFFFFFF;
	int reset_bit = 1 << j;

	/*  Flip bits j to i in mask */
	for (k = 0; k < (j - i); k++)
	{
		mask ^= reset_bit;
		reset_bit >>= 1;	
	}

	/*  Reset bits j to i in n. */
	*n &= mask;

	/*  Shift m by j bits. */
	*m <<= i;

	/*  Merge m in n. */
	*n |= *m;
}

int
main(int argc, char **argv)
{
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int j = atoi(argv[3]);
	int i = atoi(argv[4]);
	cout << "m =" << m << " n =" << n << " j =" 
		<< j << " i =" << i << endl;
	merge(&m, &n, j, i);
	cout << "n = " << n << endl;
	return (0);
}
