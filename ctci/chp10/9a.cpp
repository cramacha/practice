#include <iostream>
#include <stdlib.h>

using namespace std;

bool
search_matrix(int **matrix, int elem, int rows, int cols)
{
	int r = 0;
	int c = cols - 1;
	while (r < rows && c >= 0)
	{
		if (matrix[r][c] == elem)
			return (true);
		else if (matrix[r][c] > elem)
			c--;
		else
			r++;
	}
	return (false);
}

void
initialize_matrix(int **matrix, int rows, int cols)
{
	int seed = rand() % (rows * cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			 matrix[i][j] = seed;
			 seed++;
		}
	}
}

void
print_matrix(int **matrix, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}




int
main(int argc, char **argv)
{
	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);
	int elem = atoi(argv[3]);
	int **matrix = (int **) malloc(rows * cols * sizeof (int *));
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = (int *) malloc(rows * sizeof (int));
		(void) bzero(matrix[i], rows * sizeof (int));
	}

	initialize_matrix(matrix, rows, cols);
	print_matrix(matrix, rows, cols);
	bool result = search_matrix(matrix, elem, rows, cols);
	cout << result << endl;
	return (0);
}
