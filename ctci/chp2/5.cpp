#include <iostream>
#include <list>

using namespace std;

void
print(list<int> &l)
{
	for (auto &elem: l)
		cout << elem << " ";
	cout << endl;
}

void
sum_list(list<int> &l1, list<int> &l2, list<int> &total)
{
	int sum = 0, carry = 0;
	l1.reverse();
	l2.reverse();
	list<int>::iterator it1 = l1.begin();
	list<int>::iterator it2 = l2.begin();

	while (it1 != l1.end() && it2 != l2.end()) {
		sum = carry + *it1 + *it2;
		carry = sum / 10;
		sum = sum % 10;
		total.push_back(sum);
		it1++;
		it2++;
	}

	while (it1 != l1.end()) {
		sum = carry + *it1;
		carry = sum / 10;
		sum = sum % 10;
		total.push_back(sum);
		it1++;
	}

	while (it2 != l2.end()) {
		sum = carry + *it2;
		carry = sum / 10;
		sum = sum % 10;
		total.push_back(sum);
		it2++;
	}

	if (carry > 0)
		total.push_back(carry);
}

int
main(int argc, char **argv)
{
	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[2]);
	list<int> l1, l2;
	list<int> sum;
	int i;

	for (i = 0; i < n1; i++)
		l1.push_back(i + 1);

	for (i = 0; i < n2; i++)
		l2.push_back(i * 2);
	print(l1);
	print(l2);
	sum_list(l1, l2, sum);
	print(sum);
	return (0);
}
