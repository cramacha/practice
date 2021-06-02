#include <iostream>
#include <string.h>

using namespace std;

typedef uint8_t BYTE;

void
print_screen(uint8_t *screen, int w , int y)
{
	/*  
	 *  ostream& operator<<(ostream&, unsigned char) will only
	 *  output visible character values. So convert to unsigned int
	 *  before printing.
	 */
	for (int i = 0; i < w * y; i++)
		cout << unsigned(screen[i]) << endl;	
}

void
fill(BYTE *screen, int w, int x1, 
		int x2, int y)
{
	int first_full_byte = x1 / 8;
	int last_full_byte = x2 / 8;
	int first_off = x1 % 8;
	int last_off = x2 % 8;
	int first_full_offset = (w / 8) * y + x1/8; 
	int last_full_offset = (w / 8) * y + x2/8;

	/*  Check if first full byte is in the next byte. */
	if (first_off != 0 && first_full_byte < y)
		first_full_byte++;
	
	/*  Check if last full byte is in the prev byte. */
	if (last_off != 0 && last_full_byte > 0)
		last_full_byte--;

	/*  Set all full bytes in one go. */
	for (int b = first_full_byte; b < last_full_byte; b++)
		screen[(w / 8) * y + b] = 0xFF;

	/*
	 * e.g first_off = 5
	 * first_mask = 000..011111
	 *
	 * last_off = 4
	 * last_mask = 111..10000
	 */
	unsigned int first_mask = (1 << first_off) - 1;
	unsigned int last_mask = ~0 << last_off;

	/*  Handle case when x1 and x2 are in the same byte. */
	if (x1/8 == x2/8)
	{	
		unsigned int mask = first_mask & last_mask;
		screen[first_full_offset] |= (first_mask & last_mask);
	}
	else 
	{	
		/*  Set bytes in first_bytes's offset */
		if (first_off != 0)
			screen[first_full_offset] |= first_mask;
		
		/*  Set bytes in last byte's offset. */
		if (last_off != 0)
			screen[last_full_offset] |= last_mask;
	}
}

int
main(int argc, char **argv)
{
	int i;
	int w = atoi(argv[1]);
	int x1 = atoi(argv[2]);
	int x2 = atoi(argv[3]);
	int y = atoi(argv[4]);
	
	BYTE *screen = new BYTE[w * y];
	(void) bzero(screen, sizeof (BYTE) * w * y);
	
	cout << "Screen before filling: " << endl;
	print_screen(screen, w, y);
	fill(screen, w, x1, x2, y);
	cout << "Screen after filling: " << endl;
	print_screen(screen, w, y);
	delete[] screen;
	return (0);
}
