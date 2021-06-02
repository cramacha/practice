#include <iostream>

using namespace std;

char
get_bit(int val)
{
	return (((val & 1) == 1)? '1': '0');
}

void
print_binary(uint8_t input)
{
	cout << endl;
	for (int i = 8; i > 0; i--, input >>= 1)
	   cout << get_bit(input);
	cout << endl;	
}

uint8_t
reverse_stupid(uint8_t input)
{
	/*
	 * e.g  input  = 0001 0110
	 * 		output = 0000 1101
	 */
	uint8_t output = 0;
	int index = 7;
	for (int i = 0; i < 8; i++, index--)
	{
		int mask = input & 1;
		output |= (mask << index);
		input >>= 1;
	}
	return (output);
}

uint8_t
reverse_clever(uint8_t input)
{
	uint8_t b;
	b = (((input & 0xF0) >> 4) | (input & ~0xF0) << 4);
	b = (((b & 0xCC) >> 2) | (b & ~0xCC) << 2);
	b = (((b & 0xAA) >> 1) | (b & ~0xAA) << 1);
	return (b);
}

int
main(int argc, char **argv)
{
	uint8_t inp = 0xD;
	cout << "Input: ";
	print_binary(inp);
	uint8_t out = reverse_stupid(inp);
	cout << "Reverse simple: ";
	print_binary(out);
	cout << "Input: ";
	print_binary(inp);
	out = reverse_clever(inp);
	cout << "Reverse clever: ";
	print_binary(out);
	return (0);
}
