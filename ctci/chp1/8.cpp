#include <iostream>
#include <vector>

using namespace std;

void
print_matrix(vector<vector<int> > &m, int rows, int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout.width(3);
			cout << m[i][j];
		}
		cout << endl;
	}
}

void
zero_rows(vector<vector<int> > &m, int row, int cols)
{
	for (int i = 0; i < cols; i++)
		m[row][i] = 0;
}

void
zero_cols(vector<vector<int> > &m, int col, int rows)
{
	for (int i = 0; i < rows; i++)
		m[i][col] = 0;
}

void
rotate90(vector<vector<int> > &m, int rows, int cols)
{
	int i, j;
	bool zero_row = false, zero_col = false;
	for (i = 0; i < rows; i++) {
		if (m[i][0] == 0) {
			zero_col = true;
			break;
		}
	}
	
	for (i = 0; i < cols; i++) {
		if (m[0][i] == 0) {
			zero_row = true;
			break;
		}
	}

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if (m[i][j] == 0) {
				m[0][j] = 0;
				m[i][0] = 0;
			}
		}
	}

	for (i = 0; i < rows; i++) {
		if (m[i][0] == 0)
			zero_rows(m, i, cols);
	}

	for (i = 0; i < cols; i++) {
		if (m[0][i] == 0)
			zero_cols(m, i, rows);
	}

	if (zero_row)
		zero_rows(m, 0, cols);
	if (zero_col)
		zero_cols(m, 0, rows);
}


int
main(int argc, char **argv)
{
	int rows = 6;
	int cols = 6;
	vector<vector<int> > m;
	int i, j;

	for (i = 0; i < rows; i++) {
		if (i == m.size()) {
			vector<int> v;
			m.push_back(v);
		}
		for (j = 0; j < cols; j++) {
			m[i].push_back(i + 1); 
		}
	}
	m[1][1] = 0;
	m[4][4] = 0;

	cout << "before: " << endl;
	print_matrix(m, rows, cols);
	rotate90(m, rows, cols);
	cout << "after: " << endl;
	print_matrix(m, rows, cols);
	return (0);
}
