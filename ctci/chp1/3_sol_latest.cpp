/*
 * URLify a string, that is all empty characters in the string should be 
 * replaced with %20.
 *
 */
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int find_next(char *str, int last) {
	int cur;
	for (cur = last; cur >= 0; cur --) {
		if (str[cur] != ' ' && isalpha(str[cur]))
			break;	
	}
	return (cur);
}


char* urlify(char *str, int len) {
   cout << "Input = " << str << endl;
   int last = len - 1;
   int cur;
   for (cur = find_next(str, last); cur >= 0; cur = find_next(str, cur)) {
		cout << "swapping, cur = " << cur <<  endl;
	    while (cur >= 0 && str[cur] != ' ')
			swap(str[cur--], str[last--]);
		last -= 3;
		(void) memcpy(str + last + 1, "%20", 3);
	    cout << str << endl;	
   }
   return (str);
}


int main(int argc, char **argv) {
	const char* inp = "Jo hn Smith    ";
    int len = strlen(inp);
    char* str = (char *) malloc(sizeof(inp) * len);
	(void) memcpy(str, inp, len);
	char* ret = urlify(str, len);
	cout << "Output = " << ret << endl;
	return (0);
}

