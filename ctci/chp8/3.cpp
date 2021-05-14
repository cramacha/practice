#include <iostream>
#include <vector>

using namespace std;

ostream&
operator <<(ostream& out, vector<int>& arr)
{
	for (int i = 0; i < arr.size(); i++)
		out << arr[i] << " ";

	return (out);
}	

int
magic_index_dup_impl(vector<int>& arr, int start, int end)
{
	if (start > end)
		return (-1);

	int mid = (start + end) >> 1;

	if (arr[mid] == mid) {
		cout << "found at pos: " << mid << endl;
		return (mid);
	}

	int l = magic_index_dup_impl(arr, start, min(arr[mid], mid - 1));
	if (l != -1)
		return (l);
	return magic_index_dup_impl(arr, max(arr[mid], mid + 1), end);
}

void
magic_index_dup(vector<int>& arr)
{
	(void) magic_index_dup_impl(arr, 0, arr.size() - 1);
}

int
magic_index_impl(vector<int>& arr, int start, int end)
{
	if (start > end)
		return (-1);

	int mid = (start + end) >> 1;

	if (arr[mid] == mid) {
		cout << "found at pos: " << mid << endl;
		return mid;
	}

	if (arr[mid] > mid)
		return (magic_index_impl(arr, start, mid - 1));
	else
		return (magic_index_impl(arr, mid + 1, end));
}

void
magic_index(vector<int>& arr)
{
	magic_index_impl(arr, 0, arr.size() - 1);
}


int main(int argc, char **argv) 
{
	vector<int> arr;

	vector<int> arr2 = {-10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13};
	
	int n = atoi(argv[1]);

	for (int i = 0; i < n; i++) {
		arr.push_back(rand() % n);
	}

	int pos = rand() % n;
	cout << "pos = " << pos << endl;
	arr[pos] = pos;

	cout << "Printing magic array: " << endl << arr << endl;

	magic_index(arr);

	cout << "Printing magic array: " << endl << arr2 << endl;
	magic_index_dup(arr2);
	return (0);
}
