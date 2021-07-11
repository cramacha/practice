#include <iostream>

using namespace std;

char
get_bit(uint8_t input)
{
	return (((input & 1) == 1) ? '1' : '0');
}

void
print_binary(uint8_t input)
{
	int i;
	for (i = 8; i > 0; --i, input >>= 1)
		cout << get_bit(input);
	cout << endl;	
}

uint8_t
reverse(uint8_t input)
{
	uint8_t out;
	/*
	 * 0xFO = 11110000
	 * 0xCC = 11001100
	 * 0xAA = 10101010 
	 */
	out = (((0xF0 & input) >> 4) | (~0xF0 & input) << 4);
	out = (((0xCC & out) >> 2) | (~0xCC & out) << 2);
	out = (((0xAA & out) >> 1) | (~0xAA & out) << 1);
	return (out);
}

int
main(int argc, char **argv)
{
	uint8_t n = 0xA0;
	print_binary(n);
	uint8_t m = reverse(n);
   	print_binary(m);
	return (0);
}
