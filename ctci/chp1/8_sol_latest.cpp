/*
 * Write a function such that if an element in an MxN matrix is 0, its entire
 * row and column are set to 0.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

void print_matrix(vector<vector<int> >&m, int r, int c) {

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout.width(3);
			cout << m[i][j];
		}
		cout << endl;
	}
}

void zero_rows(vector<vector<int> >&m, int row_num, int cols) {
	int i;
	for (i = 0; i < cols; i++)
		m[row_num][i] = 0;
}

void zero_cols(vector<vector<int> >&m, int col_num, int rows) {
	int i;
	for (i = 0; i < rows; i++)
		m[i][col_num] = 0;
}


void zero(vector<vector<int> >&m, int r, int c) {
	int i, j;
	bool zero_row = false, zero_col = false;
	cout << "input = " << endl;
	print_matrix(m, r,c);

	// zero row?
	for (i = 0; i < r; i++) {
		if (m[i][0] == 0) {
			zero_row = true;
			break;
		}
	}

	// zero col?
	for (i = 0; i < c; i++) {
		if (m[0][i] == 0) {
			zero_col = true;
			break;
		}
	}

	// add markers
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			if (m[i][j] == 0) {
				m[i][0] = 0;
				m[0][i] = 0;
			}				
		}
	}

	cout << "intermediate matrix = " << endl;
	print_matrix(m, r, c);

	// zero rows
	for (i = 0; i < r; i++) {
		if (m[i][0] == 0) {
			zero_rows(m, i, c);
		}
	}

	// zero cols
	for (i = 0; i < c; i++) {
		if (m[0][i] == 0) {
			zero_cols(m, i, r);
		}
	}

	cout << "Output = " << endl;
	print_matrix(m, r, c);
}

int main(int argv, char **argc) {
	int i, j;
	int r = atoi(argc[1]);
	int c = atoi(argc[2]);
	vector<vector<int> > m;
	for (i = 1; i <= r; i++) {
		vector<int> row;
		for (j = 1; j <= c; j++) {
			row.push_back(j);
		}
		m.push_back(row);
	}
	m[1][1] = 0;
	//m[0][2] = 0;
	zero(m, r, c);
	return (0);
}
