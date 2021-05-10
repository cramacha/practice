#include <iostream>
#include <vector>

using namespace std;

int count_steps(int, int, vector<int> &);

ostream&
operator <<(ostream &out, const vector<int> &steps) 
{
	for (int i = 0; i < steps.size(); i++) {
		out << steps[i] << " ";
	}
	out << endl;
	return (out);
}

int
count_steps_impl(int total, int cur, int step, vector<int> &steps)
{
	int sum;
	steps.push_back(step);
	sum = count_steps(total, cur + step, steps);
	steps.pop_back();
	return (sum);
}


int
count_steps(int total, int cur, vector<int> & steps)
{
	int sum = 0;
	if (cur == total) {
		cout << steps << endl;
		return (1);
	}

	if (cur > total) {
		return (0);
	}

	sum += count_steps_impl(total, cur, 1, steps);
	sum += count_steps_impl(total, cur, 2, steps);
	sum += count_steps_impl(total, cur, 3, steps);

	return (sum);
}



int main(int argc, char **argv) {
	int total = atoi(argv[1]);
	vector<int> steps;
	cout << "Total steps to sum upto: " << total << endl;
	int sum = count_steps(total, 0, steps);
	cout << "Sum: " << sum << endl;
	return 0;
}
