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

void
sumlist(list<int> &l1, list<int> &l2) {
	int carry = 0;
	int sum = 0;
	int total = 0;
	list<int> res;
	list<int>::iterator it1 = l1.begin();
	list<int>::iterator it2 = l2.begin();

	//l1.reverse();
	//l2.reverse();

	print_list(l1);
	print_list(l2);

	while (it1 != l1.end() && it2 != l2.end()) {
		total = *it1 + *it2 + carry;
		sum = total % 10;
		carry = total / 10;
		res.push_back(sum);
		it1++;
		it2++;
	}


	while (it1 != l1.end()) {
		total = *it1 + carry;
		sum = total % 10;
		carry = total / 10;
		res.push_back(sum);
		it1++;
	}

	while (it2 != l2.end()) {
		total = *it2 + carry;
		sum = total % 10;
		carry = total / 10;
		res.push_back(sum);
		it2++;
	}

	if (carry) {
		res.push_back(carry);
	}

	res.reverse();
	print_list(res);
}

int main(int argc, char **argv)
{
	list<int> l1, l2;
	int i;
	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[2]);

	for (i = n1; i > 0; i--)
		l1.push_back(i + 1);

	for (i = n2; i > 0; i--)
		l2.push_back(i + 1);

	print_list(l1);
	print_list(l2);
	sumlist(l1, l2);
}