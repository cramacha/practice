/*
 * Given a string, replace all spaces in it with '%20' (URLify).
 */

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

/*
 * Find the first non-empty character traversing from the end of the string.
 */

int
find_next(char *inp, int last)
{
	int i;
	for (i = last; i >= 0; i--)
	{
		if (inp[i] != ' ')
			break;
	}
	return (i);
}

void
urlify(char *inp, int len)
{
	int last = len - 1;
	int cur;
	for (cur = find_next(inp, last); cur >= 0; cur = find_next(inp, cur))
	{
		/*
		 * The cur pointer may be pointing to an already modified part of the 
		 * string (%20) so we break if we encounter this situation.
		 * */
		if (!isalpha(inp[cur]))
			break;
		while (cur >= 0 && inp[cur] != ' ')
			swap(inp[cur--], inp[last--]);
		last -= 3;
		(void) memcpy(inp + last + 1, "%20", 3);	
	}
}

int
main(int argc, char **argv)
{
	const char *str = "Jo hn Smith    ";
	int len = strlen(str);	
	char *inp = (char*) malloc(sizeof (char) * len);
	(void) memcpy(inp, str, len);
	cout << "Original: " << inp << endl;
	urlify(inp, len);
	cout << "Modified: " << inp << endl;
	return (0);
}
