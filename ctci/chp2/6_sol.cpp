#include <iostream>
#include <list>

using namespace std;

void
print_list(list<int> &l) {
	cout << "list = " << endl;
	for (auto &elem: l) {
		cout << elem << " ";
	}
	cout << endl;
}

bool
palindrome(list<int> &l) {
	list<int> tmp;
	int size = l.size();
	list<int>::iterator i = l.begin();
	list<int>::iterator n = next(i, size/2);

	while (n != l.end()) {
		tmp.push_front(*n);
		n++;
	}
	print_list(tmp);

	auto it1 = tmp.begin();

	while (i != l.end()) {
		if (*i != *it1) {
			return (false);
		}
		i++;
		it1++;
	}
	return (true);
}

int main(int argc, char **argv)
{
	list<int> l1, l2;
	int i;
	
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(2);
	l1.push_back(1);


	print_list(l1);
	bool ret = palindrome(l1);
	cout << " ret = " << ret << endl;
}