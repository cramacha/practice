#include <iostream>
#include <vector>

using namespace std;

ostream&
operator <<(ostream &out, vector<int> &input)
{
	for (int i = 0; i < input.size(); i++)
		out << i << " " << input[i] << endl;
	cout << endl;
	return (out);
}

bool
can_place(int row, int current_col, vector<int> &cols)
{
	for (int prev_row = 0; prev_row < row; prev_row++)
	{
		int prev_col = cols[prev_row];
		
		/* Same column. */
		if (prev_col == current_col)
			return (false);

		int row_dist = row - prev_row;
		int col_dist = abs(prev_col - current_col);
		
		/*  Same diagonal. */
		if (row_dist == col_dist)
			return (false);
	}

	return (true);
}

int
nqueens_impl(int row, int n, vector<int> &cols, vector<vector<int> > &result)
{
	int ways = 0;
	if (row == n)
	{
		result.push_back(cols);
		cout << cols << endl;
		return (1);
	}

	for (int i = 0; i < n; i++)
	{
		if (can_place(row, i, cols))
		{
			cols[row] = i;
			ways += nqueens_impl(row + 1, n, cols, result);
		}
	}

	return (ways);	
}

void
nqueens(int n)
{
	vector<int> cols(n);
	vector<vector<int> > result;
	int ways = nqueens_impl(0, n, cols, result);
	cout << "ways = " << ways << endl;
}
	
int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	nqueens(n);
	return (0);
}
