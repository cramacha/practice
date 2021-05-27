#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

#define SIZE 32000

void
search_duplicates(bitset<SIZE> &bs, vector<int> &input)
{
	for (int i = 0; i < input.size(); i++)
	{
		if (bs.test(input[i]))
			cout << "Duplicate: " << input[i] << endl;
		else
			bs.set(input[i]);
	}	
}

int
main(int argc, char **argv)
{
	bitset<SIZE> bs;
	vector<int> input(SIZE);
	for (int i = 0; i < SIZE; i++)
		input[i] = i;
	int rand_index = rand() % (SIZE - 1);
	cout << "duplicate index: " << rand_index << endl;
	input[rand_index] = input[rand_index - 1];
	search_duplicates(bs, input);
	return (0);
}
