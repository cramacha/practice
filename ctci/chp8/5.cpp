#include <iostream>

using namespace std;

#define MAX(x, y)	((x > y) ? x : y)
#define MIN(x, y)	((x < y) ? x : y)
#define ABS(x)	((x < 0) ? (-x): x) 

int
recursive_multiply_impl(int smaller, int bigger)
{
	if (smaller == 0)
		return (0);
	if (smaller == 1)
		return (bigger);
	
	int s = smaller >> 1;
	int side1 = recursive_multiply_impl(s, bigger);
	int side2 = side1;
	if (smaller % 2 == 1)
		return (side1 + side1 + side2);
	
	return (side1 + side2);	
}

void
recursive_multiply(int a, int b)
{
	int smaller = MIN(ABS(a), ABS(b));
	int bigger = MAX(ABS(a), ABS(b));
	int sign = 1;
	if ((a > 0 && b < 0) || (a < 0 && b > 0))
		sign = -1;
	cout << " Input: " << smaller << " " << bigger << endl;
	int product = recursive_multiply_impl(smaller, bigger);
	product = (sign > 0 ? product: 0 - product);
	cout << " Product: " << product << endl;
}

int main(int argc, char **argv)
{
	recursive_multiply(atoi(argv[1]), atoi(argv[2]));
	return (0);
}
