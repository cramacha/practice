#include <iostream>
#include <vector>
#include <string>

using namespace std;

int
get_new_mid(vector<string> &sparse, int mid)
{
	int l = mid;
	int r = mid;
	while (l >= 0 && sparse[l] == "")
		l--;
	
	if (sparse[l] != "")
		return (l);

	while (r <= sparse.size() && sparse[r] == "")
		r++;

	if (sparse[r] != "")
		return (r);
	
	return (-1);
}
	
int
search_impl(vector<string> &sparse, string &elem,
		int left, int right)
{
	if (left > right)
		return (-1);

	int mid = (left + right) / 2;
	
	/*  Find the nearest non-empty string if mid is empty string. */
	if (sparse[mid] == "")
		mid = get_new_mid(sparse, mid);
	
	/*  In case we didnt find a suitable mid both sides. */
	if (mid == -1)
		return (mid);

	/* Regular binary search. */
	if (sparse[mid] == elem)
		return (mid);
	else if (sparse[mid] < elem)
		return (search_impl(sparse, elem, mid + 1, right));
	else
		return (search_impl(sparse, elem, left, mid - 1));
}

void
search(vector<string> &sparse, string &element)
{
	int pos = search_impl(sparse, element, 0, sparse.size() - 1);
	cout << "pos = " << pos << endl;
}

int
main(int argc, char **argv)
{
	vector<string> sparse({"at", "", "ball", "", ""
			"", "", "", "car", "", "","dad"
			});
	string element = "ball";
	search(sparse, element);
	return (0);
}
