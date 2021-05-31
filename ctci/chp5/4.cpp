#include <iostream>

using namespace std;

int
get_next(unsigned int n)
{
	unsigned int temp = n;
	unsigned int c1 = 0;
	unsigned int c0 = 0;
	unsigned int p;
	
	/*
	 * e.g 1010
	 *
	 * 1. c0 = 1
	 * 2. c1 = 1
	 *    p = c0 + c1 = 2
	 * 3. n = 1000 (mask, all 1s to left of p)
	 *		& 1010 = 1000
	 * 4. p = 2, so 1100
	 * 5. add c1 - 1 ones at the end, so 1100
	 */

	/*  1. Count trailing zeros. */
	while ((temp > 0) && ((temp & 1) == 0))
	{
		c0++;
		temp >>= 1;
	}

	/*  2. Count 1s after that. */
	while ((temp > 0) && ((temp & 1) == 1))
	{
		c1++;
		temp >>= 1;
	}

	/*  Position of first non trailing zero. */
	p = c0 + c1;

	/*  Check for invalid p. i.e. if it is > 31 or is 0. */
	if (p > 31 || p == 0)
		return (-1);
	
	/*  3. Mask with all bits 1 to left of p. */
	n = n & (~0 << p);

	/*  4. Set p to 1. */
	n |= (1 << p);

	/*  5. Add c1 - 1 1s at the end. */
	n |= ((1 << (c1 - 1)) - 1);
	
	return (n);	
}

int
get_prev(unsigned int n)
{
	unsigned int temp = n;
	unsigned int c1 = 0;
	unsigned int c0 = 0;
	unsigned int p;

	/*
	 * e.g. 1010
	 *
	 * 1. c0 = 1 and c1 = 0
	 * 2. p = 1
	 * 3. Reset all bits upto p, so n = 1000
	 * 4. Add c1 + 1 ones into mask = 0001
	 * 5. Shift mask c0 - 1 times = 0001
	 * 6. n | mask = 1001
	 */

	/*  1. First count trailing 1s. */
	while (temp > 0 && ((temp & 1) == 1))
	{
		c1++;
		temp >>= 1;
	}

	/* 2. Count 0s. */
	while (temp > 0 && ((temp & 1) == 0))
	{
		c0++;
		temp >>= 1;
	}

	/* 3. Position of first non-trailing 1. */
	p = c0 + c1;

	/* 4. Reset bits till p to 0. */
   	n &= (~0 << (p + 1));

	/* 5. Add c1 + 1 ones from p + 1 position. */
	unsigned int mask = (1 << (c1 + 1)) - 1;
	
	/* Move mask left by c0 - 1 bits. */
	mask <<= (c0 - 1);
	n |= mask;
	return (n);	
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	int next = get_next(n);
	int prev = get_prev(n);
	cout << "n = " << n << " next = " << next
		<< " prev = " << prev << endl;
	return (0);
}
