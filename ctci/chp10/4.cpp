#include <iostream>
#include <vector>

using namespace std;

class listy
{
	private:
		vector<int> input;
		int search_impl(int element, int left, int right);
	public:
		listy(vector<int> &);
		int element_at(int);
		int search(int);
};

listy::listy(vector<int> &a)
{
	input = a;
}


int
listy::element_at(int index)
{
	if (index >= input.size())
		return (-1);
	else
		return (input[index]);	
}

int
listy::search(int element)
{
	/*  
	 *  To find the limits of the input array, advance
	 *  the index pointer by a power of 2 until we reach the end
	 *  (This is obtained when element_at function returns -1).
	 */
	int index = 1;
	while (element_at(index) != -1 && element > element_at(index)) 
		index *= 2;

	cout << "size = " << index << endl;
	/*  
	 *  Regular binary search.
	 *	Total run time of this algorithm is:
	 *	Log(n) -> to find limits of array
	 *	Log(n) -> Binary search
	 */
	return (search_impl(element, index/2, index));
}

int
listy::search_impl(int element, int left, int right)
{
	if (left > right)
	   return (-1);

	int mid = (left + right)/2;	
	
	if (element == input[mid])
		return (mid);
	else if (element > input[mid])
		return (search_impl(element, mid + 1, right));
	else
		return (search_impl(element, left, mid - 1));
}	

int
main(int argc, char **argv)
{
	vector<int> input({
			4, 5, 6, 7, 8, 9, 10
			});
	int element = 9;
	listy list(input);
	vector<int> input2({
			4
			});
	int element2 = 45;
	listy list2(input);

	int index = list.search(element);
	cout << "element: " << element
	   	<< " found at: " << index << endl;
	int index2 = list2.search(element2);
	cout << "element2: " << element2
	   	<< " found at: " << index2 << endl;

	return (0);
}
