#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int
get_ways(int total_true, int total, bool desired)
{
	if (desired == true)
		return (total_true);
	else
		return (total - total_true);
}

int
count_eval_impl(string input, bool desired)
{
	int ways = 0;
	bool actual;
	int total_true = 0;
	if (input.size() == 1)
	{
		istringstream(input) >> actual;
		return ((actual == desired) ? 1 : 0);
	}

	for (int i = 1; i < input.size(); i+= 2)
	{
		string left = input.substr(0, i);
		string right = input.substr(i + 1);
		char op = input[i];
		int left_true = count_eval_impl(left, true);
		int left_false = count_eval_impl(left, false);
		int right_true = count_eval_impl(right, true);
		int right_false = count_eval_impl(right, false);
		int total = (left_true + left_false) * (right_true + right_false);

		if (op == '&')
			total_true = left_true * right_true;
		else if(op == '|')
			total_true = (left_true * right_false) +
				(left_false * right_true) +
				(left_true * right_true);
		else if (op == '^')
			total_true = (left_true * right_false) +
				(left_false * right_true);
		ways += get_ways(total_true, total, desired);
	}
	return (ways);
}

void
count_eval(string input, bool desired)
{
	cout << count_eval_impl(input, desired) << endl;
}

int
main(int argc, char **argv)
{
	string input(argv[1]);
	stringstream ss(argv[2]);
	bool desired;
	ss >> boolalpha >> desired;
	count_eval(input, desired);
	return(0);
}
