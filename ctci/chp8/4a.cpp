#include <iostream>
#include <vector>

using namespace std;

ostream&
operator <<(ostream &out, vector<int> &arr)
{
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	out << endl;
	return (out);
}


ostream&
operator <<(ostream &out, vector<vector<int> > &arr)
{
	for (int i = 0; i < arr.size(); i++)
		out << arr[i] << " ";
	return (out);
}

vector<vector<int> >
powerset_impl(vector<int> &arr, int n)
{
	vector<vector<int> > subsets;
	
	if (n == arr.size()) {
		subsets.push_back(vector<int>());
		return (subsets);
	}

	subsets = powerset_impl(arr, n + 1);
	vector<vector<int> > results = subsets;
	for (int i = 0; i < subsets.size(); i++)
	{
		subsets[i].push_back(arr[n]);				
	}

	results.insert(results.end(), subsets.begin(), subsets.end());
	
	return (results);
}

void
powerset(vector<int> &arr)
{
	vector<vector<int> > result = powerset_impl(arr, 0);
	cout << "Resulting powerset: " << result << endl;
}	

int main(int argc, char **argv)
{
	vector<int> arr;
	int n = atoi(argv[1]);
	
	for (int i = 0; i < n; i++)
		arr.push_back(i);

	cout << arr << endl;

	powerset(arr);
		
	return (0);
}
