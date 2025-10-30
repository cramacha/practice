#include <iostream>
#include <list>

using namespace std;

void print_list(list<int> &l) {
	for (auto &elem: l) {
		cout << elem << " ";
	}
	cout << endl;
}

// need to call next to get the next node else
// the next time it will be a segfault.
void partition(list<int> &l, int val) {
	list<int>::iterator n = l.begin();
	for (;n != l.end();) {
		if (*n < val) {
			cout << "list to eval for elem:" << *n << endl;
			print_list(l);
			l.push_front(*n);
			auto tmp = next(n, 1);
			l.erase(n);
			n = tmp;
		} else {
			n++;
		}
	}
}

int main(int argc, char **argv)
{
	list<int> l;
	int n = atoi(argv[1]);
	int val = atoi(argv[2]);

	for (int i = n; i > 0; i--)
		l.push_back(i + 1);

	print_list(l);
	partition(l, val);
	print_list(l);
}