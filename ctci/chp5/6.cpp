#include <iostream>

using namespace std;

int
flip(int a, int b)
{
	/*
	 * e.g a = 1001, b = 0110
	 * a ^ b = 1111. This gives the number of bits which are
	 * different between a and b.
	 * 
	 * The bits can be counted in the Kernighan way i.e. n & n - 1
	 * This will keep resetting the least significant bit until we
	 * reach 0.
	 */
	unsigned int c;
	int count = 0;
	for (c = a ^ b; c != 0; c = c & c - 1)
		count++;
	return (count);
}

int
main(int argc, char **argv)
{
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int c = flip(a, b);
	cout << "a = " << a << " b = " << b
		<< " c = " << c << endl;
	return (0);
}
