#include <iostream>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <string.h>

using namespace std;

/*
 *	Given file of 1 billion unique ints (with a missing int),
 *	and 10MB memory, find missing int:
 *
 *	(1) First choose a range_size for an int array which can store
 *	all the ints.
 *		range_size >= (2^31/2^21) --> 10MB translates to 2^23 bytes
 *					or 2^23/2^2(size of int) elements
 *				   >= 2^10
 *	(2) Divide array into blocks and count number of elements
 *		in each block by reading file.
 *	(3) Find block with missing int.
 *	(4) Create bitvector for this identified block.
 *	(5) Find missing int in bitvector.				   
 *
 */

#define TYPE_SIZE ((sizeof (uint8_t)) * 8)

class bitvector
{
	public:
		bitvector(int);
		~bitvector();
		void set(int);
		uint8_t **get_bv();
		int get_size();
	private:
		int size;
		uint8_t **byte;
};

bitvector::bitvector(int input_size)
{
	size = input_size;
	byte = new uint8_t*[size];
}

bitvector::~bitvector()
{
	for (int i = 0; i < size; i++)
	{
		if (byte[i] != NULL)
			delete byte[i];
	}
	delete byte;
}

uint8_t**
bitvector::get_bv()
{
	return (byte);
}

int
bitvector::get_size()
{
	return (size);
}

void
bitvector::set(int num)
{
	int index = size / num;
	int bitnumber = num % 8;
	
	if (byte[index] == NULL)
		byte[index] = new uint8_t;
	*byte[index] |= (1 << bitnumber);	
}

void
read_and_store(string filename, bitvector *bv, 
		int block_index, int range_size)
{
	ifstream stream(filename);
	int num;
	string line;
	int start_range = range_size * block_index;
	int end_range = start_range + range_size;
	
	if (!stream.is_open())
		return;
	
	while (getline(stream, line))
	{
		istringstream(line) >> num;
		if (num >= start_range 
				&& num <= end_range)
			/*  
			 *  This bitvector only stores elements within
			 *  the range. So get that numbers' offset within the
			 *  range first before setting it in the bitvector.
			 */
			bv->set(end_range - num);				
	}
}

void
get_block_count(int **blocks, string filename, int range_size)
{
	ifstream stream(filename);
	string line;
	int num;
		
	if (!stream.is_open())
		return;
	
	while (getline(stream, line))
	{
		istringstream(line) >> num;
		blocks[num / range_size]++;		
	}
}

int
get_missing_block(int **blocks, int total_blocks, 
		int range_size)
{
	for (int i = 0; i < total_blocks; i++)
	{
		if (*blocks[i] < range_size)
			return (i);
	}
	return (-1);
}

int
get_missing_int_impl(bitvector *bv, int i, int j)
{
	uint8_t *current_byte = bv->get_bv()[i];
	if (current_byte != NULL
			&& ((*current_byte & (1 << j)) == 0))
			return (j);
	return (-1);
}

int
get_missing_int(bitvector *bv)
{
	int num;
	for (int i = 0; i < bv->get_size(); i++)
	{
		for (int j = 0; j < TYPE_SIZE; j++)
		{
			if ((num = get_missing_int_impl(bv, i, j)) != -1)
					return (num);
		}
	}
	return (-1);
}

int
main(int argc, char **argv)
{
	bitvector *bv = new bitvector(INT_MAX);
	string file(argv[1]);
	
	/*  2 ^ 20 elements in a block. */
	int range_size = (1 << 20);  
	int block_count = INT_MAX / range_size;
	int **blocks = new int*[block_count];
	if (blocks == NULL)
		return (0);
	for (int i = 0; i < block_count; i++)
	{
		blocks[i] = new int;
		(void) bzero(blocks[i], sizeof (int *));
	}
	
	get_block_count(blocks, file, range_size);
	int missing_block = get_missing_block(blocks, 
			block_count, range_size);	
	read_and_store(file, bv, missing_block, range_size);
	int missing_num = get_missing_int(bv);
	cout << "missing_num: " << missing_num << endl;
	delete bv;
	return (0);
}

