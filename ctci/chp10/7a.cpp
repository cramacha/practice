#include <iostream>
#include <ctype.h>
#include <sstream>
#include <fstream>

using namespace std;

/*
 *	Given input file of 4 billion ints and 1GB (8 billion bits)
 *	of available memory, we store the ints in a bitvector.
 *
 * 	We then traverse each bit of the bitvector and find the first
 * 	available 0 (This is the missing int).
 */

/*  Multiply by 8 to represent in bits. */
#define TYPE_SIZE (sizeof (uint8_t) * 8)  

class bitvector
{
	private:
		int size;
		uint8_t **byte;
	public:
		bitvector(int);
		~bitvector();
		void set(int);
		uint8_t **get_bv();
		int get_size();
};

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

bitvector::bitvector(int input_size)
{
	size = input_size;
	byte = new uint8_t *[size];
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

void
bitvector::set(int num)
{
	int index = num / TYPE_SIZE;
	if (byte[index] == NULL)
		byte[index] = new uint8_t;
	*byte[index] |= 1 << (num % 8);	
}

int
get_missing_int_impl(bitvector *bv, int i, int j)
{	
	int index = i / TYPE_SIZE;
	uint8_t	*current_byte = bv->get_bv()[index];
	if ((current_byte != NULL) 
			&& (*current_byte & (1 << j)) == 0)
		return ((i * TYPE_SIZE) + j);
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
			if ((num = get_missing_int_impl(bv, i, j)) >= 0)
				return (num);
		}		
	}
	return (-1);	
}

void
read_and_store(string filename, bitvector *bv)
{
	ifstream stream(filename);
	int num;
	string line;
	if (!stream.is_open())
		return;
	while (getline(stream, line))
	{
		istringstream(line) >> num;
		cout << "Storing : " << num << " in bit vector" << endl;
		bv->set(num);
	}
	stream.close();
}

int
main(int argc, char **argv)
{
	string filename(argv[1]);
	bitvector *bv = new bitvector(INT_MAX);
	read_and_store(filename, bv);
	int missing_num = get_missing_int(bv);
	cout << "missing num: " << missing_num << endl;
	delete bv;
	return (0);
}
