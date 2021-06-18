#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Find the next available non-empty character from the
 * back of the string. 
 */
int
find_next(char *a, int cur)
{
	int i;
	for (i = cur; i > 0; i--) {
		if (a[i] != ' ')
			break;
	}
	return (i);
}

void
urlify(char *a, int len)
{
	int cur;
	int last = len - 1;
	for (cur = find_next(a, last); cur > 0; cur = find_next(a, last)) {
		while (a[cur] != ' ') {
			a[last--] = a[cur--];
		}
		last -= 3;
		(void) memcpy(a + last + 1, "%20", 3);	
	}
}

int
main(int argc, char **argv)
{
	const char *orig = "John Smith  ";
	int len = strlen(orig), i = 0;
	char *urlified = (char *) malloc(sizeof (char) * len);
	(void) memcpy(urlified, orig, len);
	urlify(urlified, len);
	cout << "inp: " << orig 
		<< " out: " << urlified << endl;
	return (0);
}
