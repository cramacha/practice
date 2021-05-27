#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

/*
 *	Re-implementation of 7b using bitset STL.
 */

#define RANGE_SIZE (1 << 20)

void
block_counts(string filename, vector<int> &blocks)
{
	string line;
	int num;
	ifstream file(filename);
	if (!file.is_open())
		return;
	while (getline(file, line))
	{
		istringstream(line) >> num;
		blocks[num / RANGE_SIZE]++;
	}
	file.close();
}

int
get_missing_block(vector<int> &blocks)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		if (blocks[i] < RANGE_SIZE)
			return (i);
	}
	return (-1);
}

int
get_missing_bit(bitset<RANGE_SIZE> &bs)
{
	for (int i = 0; i < bs.size(); i++)
	{
		if (bs.test(i) == 0)
			return (i); 
	}
	return (-1);
}

void
read_and_store(string filename, bitset<RANGE_SIZE> &bs,
		int block_index)
{
	int start_index = RANGE_SIZE * block_index;
	int end_index = start_index + RANGE_SIZE;
	string line;
	int num;
	ifstream file(filename);
	if (!file.is_open())
		return;

	while (getline(file, line))
	{
		istringstream(line) >> num;
		if (num >= start_index && num <= end_index)
			bs.set(num);	
	}
	file.close();
}

int
main(int argc, char **argv)
{
	string filename(argv[1]);
	bitset<RANGE_SIZE> bs;
	vector<int> blocks(INT_MAX / RANGE_SIZE, 0);
	block_counts(filename, blocks);	
	int block_index = get_missing_block(blocks);
	if (block_index >= 0)
	{
		read_and_store(filename, bs, block_index);
		int bit = get_missing_bit(bs);
		cout << ((RANGE_SIZE * block_index) + bit) << endl;
	}
	return (0);
}
