#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void
print_matrix(vector<vector<int> > &m, int rows, int cols)
{
	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout.width(3);
			cout << m[i][j];
		}
		cout << endl;
	}
}

void
rotate90(vector<vector<int> > &m, int rows, int cols)
{
	int size = m.size();
	int limit;
	for (int row = 0, col = 0; row <= size/2; row++, col++) {
		limit = size - row - 1;
		for (int off = 0; off < limit - col; off++) {
			int tmp = m[col + off][row];
			m[col + off][row] = m[limit][row + off];
			m[limit][row + off] = m[limit - off][limit];
			m[limit - off][limit] = m[col][limit - off];
			m[col][limit - off] = tmp;
			print_matrix(m, rows, cols);
		}
	}
}

int
main(int argc, char **argv)
{
	vector<vector<int> > m;
	int rows = 3;
	int cols = 3;
	for (int i = 0; i < rows; i++) {
		if (i == m.size()) {
			vector<int> v;
			m.push_back(v);
		}
		for (int j = 0; j < cols; j++) {
			m[i].push_back(i + pow(3, j));
		}
	}

	cout << "before:" << endl;
	print_matrix(m, rows, cols);
	rotate90(m, rows, cols);
	cout << "after:" << endl;
	print_matrix(m, rows, cols);
	return (0);
}
