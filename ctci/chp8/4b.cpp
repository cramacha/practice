#include <iostream>
#include <vector>

using namespace std;

ostream&
operator <<(ostream &out, vector<int> &arr)
{
	for (int i = 0; i < arr.size(); i++)
		out << arr[i] << " ";
	out << endl;
	return (out);
}

ostream&
operator <<(ostream &out, vector<vector<int> > &arr)
{
	for (int i = 0; i < arr.size(); i++)
		out << arr[i];
	return (out);
}

vector<int>
convert_int_to_set(int n, vector<int> &arr)
{
	vector<int> subset;
	int index = 0;
	while (n)
	{
		if ((n & 1) == 1) {
			subset.push_back(arr[index]);	
		}
		n >>= 1;
		index++;
	}
	return subset;
}

void
powerset(vector<int> &arr)
{
	vector<vector<int> > result;
	int n = arr.size();
	int max = 1 << n;
	int index = 0;

	for (int i = 0; i < max; i++) 
	{
		result.push_back(convert_int_to_set(i, arr));
	}

	cout << result << endl;	
}

int main(int argc, char **argv)
{
	vector<int> arr;
	int n = atoi(argv[1]);
	
	for (int i = 1; i <= n; i++)
		arr.push_back(i);
	
	cout << "input: " << arr << endl;
	powerset(arr);
	return (0);
}
