#include <iostream>
#include <vector>

using namespace std;

ostream&
operator <<(ostream &out, vector<int> &inp)
{
	for (int i = 0; i < inp.size(); i++)
		out << inp[i] << " ";
	out << endl;
	return (out);
}

int
search_impl(vector<int> &input, int k, int start, int end)
{
	if (start > end)
		return (-1);
	
	int mid = (start + end) / 2;
	
	if (input[mid] == k)
		return (mid);
	
	if (input[start] < input[mid])
	{
		if (input[start] <= k && input[mid] > k)
			return (search_impl(input, k, start, mid - 1));
		else
			return (search_impl(input, k, mid + 1, end));
	}
	else if (input[end] > input[mid])
	{
		if (input[mid] < k && input[end] >= k)
			return (search_impl(input, k, mid + 1, end));
		else
			return (search_impl(input, k, start, mid - 1));
	}
	else if (input[start] == input[mid])
	{
		if (input[mid] != input[end])
			return (search_impl(input, k, mid + 1, end));
		else
		{
			/*  Search both sides. */
			int index = search_impl(input, k, start, mid - 1);
			if (index == -1)
				return (search_impl(input, k, mid + 1, end));
			return (index);
		}
	}
	return (-1);
}

void
search(vector<int> &input, int k)
{
	int pos = search_impl(input, k, 0, input.size() - 1);
	cout << "pos = " << pos << endl;
}

int
main(int argc, char **argv)
{
	vector<int> input1({
		15, 16, 19, 20, 25, 1, 3 ,4 ,5 ,7 ,10, 14
	});
	
	vector<int> input2({
		2, 2, 2, 3, 4, 2
	});

	cout << input1;
	search(input1, 5);
	cout << input2;
	search(input2, 4);
	return (0);
}
