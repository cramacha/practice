#include <iostream>

using namespace std;

void
merge(int *m, int *n, int j, int i)
{
	int k;

	/*  Mask with all bits 1 to left of j
	 *  and remaining 0 */
	int lmask = ~0 << j;

	/*  Mask with all bits to left of i as 0. */
	int rmask = (1 << i) - 1;

	/*  Get a combined mask. */
	int mask = lmask | rmask;

	/*  Reset bits j to i in n. */
	*n &= mask;

	/*  Shift m by i bits. */
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
