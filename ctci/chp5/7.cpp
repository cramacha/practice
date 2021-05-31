#include <iostream>

using namespace std;

void
shift(int n)
{
	/*
	 * e.g. n = 1010
	 * oddmask = 1010..
	 * evenmask = 0101..
	 *
	 * rightshift = 1010 >> 1 = 0101
	 * leftshift = 0000
	 * result = leftshift | rightshift = 0101.
	 */
	unsigned int oddmask = 0xAAAAAAAA;
	unsigned int evenmask = 0x55555555;
	unsigned int rightshift = (n & oddmask) >> 1;
	unsigned int leftshift = (n & evenmask) << 1;
	cout << (rightshift | leftshift) << endl;
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	shift(n);
	return (0);
}
