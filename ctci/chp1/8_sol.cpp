/*
 * Write a function such that if an element in an MxN matrix is 0, its entire
 * row and column are set to 0.
 */

#include <iostream>
#include <vector>

using namespace std;

void
generate_matrix(vector<vector<int> > &m, int r, int c)
{
	int i;
	int j;
	cout << "Generating matrix" << endl;
	for (i = 0; i < r; i++)
	{
		vector<int> row;
		for (j = 0; j < c; j++)
		{
			row.push_back(1);
		}
		m.push_back(row);
	}

	m[r/2][c/2] = 0;
	m[r/4][c/4] = 0;
}

void
print_matrix(vector<vector<int> > &m, int r, int c)
{
	int i;
	int j;
	cout << "Printing matrix" << endl;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			cout.width(3);
			cout << m[i][j];
		}
		cout << endl;
	}
}

void
zero_cols(vector<vector<int> > &m, int col_num, int r)
{
	int i;

	for (i = 0; i < r; i++)
		m[i][col_num] = 0;
}

void
zero_rows(vector<vector<int> > &m, int row_num, int c)
{
	int j;

	for (j = 0; j < c; j++)
		m[row_num][j] = 0;
}

void
zero_matrix(vector<vector<int> > &m, int r, int c)
{
	int i;
	int j;
	bool zero_row = false;
	bool zero_col = false;


	/*
	 * Find out if there is a 0 in any cell of the first column.
	 */
	for (i = 0; i < r; i++)
	{
		if (m[i][0] == 0)
		{
			zero_row = true;
			break;
		}
	}

	/*
	 * Find out if there is a 0 in any cell of the first row.
	 */
	for (j = 0; j < c; j++)
	{
		if (m[0][j] == 0)
		{
			zero_col = true;
			break;
		}
	}

	/*
	 * Traverse matrix, if any cell is 0, mark the corresponding 0 cell
	 * in the topmost and leftmost part of matrix as 0.
	 */
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			if (m[i][j] == 0)
			{
				m[0][j] = 0;
				m[i][0] = 0;
			}
		}
	}

	/*
	 * If a 0 is found in any cell of the 0th column, mark the entire row as 0.
	 */
	for (i = 0; i < r; i++)
	{
		if (m[i][0] == 0)
			zero_rows(m, i, c);
	}


	/*
	 * If a 0 is found in any cell of the 0th row, mark the entire col as 0.
	 */
	for (j = 0; j < c; j++)
	{
		if (m[0][j] == 0)
			zero_cols(m, j, r);
	}

	/*
	 * If a 0 is found in any cell of the 0th col, mark the entire 0th col as 0.
	 */
	if (zero_row)
		zero_cols(m, 0, r);

	/*
	 * If a 0 is found in any cell of the 0th row, mark the entire 0th row as 0.
	 */
	if (zero_col)
		zero_rows(m, 0, c);
}

int
main(int argc, char **argv)
{
	vector<vector<int> > m;
	int r = atoi(argv[1]);
	int c = atoi(argv[2]);
	generate_matrix(m, r, c);
	print_matrix(m, r, c);
	zero_matrix(m, r, c);
	print_matrix(m, r, c);
	return (0);
}
