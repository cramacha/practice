#include <iostream>
#include <set>

using namespace std;

void
print_grid(int *grid[], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

void
fill(int *grid[], int rows, int cols, int ocolor, int ncolor,
	   	int row, int col, set<pair<int, int> > &visited)
{
	if (row < 0 || row > rows - 1 || col < 0 || col > cols - 1
			 || visited.find(make_pair(row, col)) != visited.end())
	{
		return;
	}

	int color = grid[row][col];
	if (color == ocolor)
	{
		grid[row][col] = ncolor;
		visited.insert(make_pair(row, col));
		fill(grid, rows, cols, ocolor, ncolor, row, col + 1, visited);
		fill(grid, rows, cols, ocolor, ncolor, row + 1, col, visited);
		fill(grid, rows, cols, ocolor, ncolor, row + 1, col + 1, visited);
		fill(grid, rows, cols, ocolor, ncolor, row, col - 1, visited);
		fill(grid, rows, cols, ocolor, ncolor, row - 1, col, visited);
	}
}

void
initialize(int *grid[], int rows, int cols, int ocolor)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i % 2)
				grid[i][j] = ocolor;
			else
				grid[i][j] = -1;
		}
	}
}

void
allocate(int *grid[], int rows, int cols)
{
	for (int i = 0; i < rows; i++) 
	{
		grid[i] = new int[cols];
	}	
}

int main(int argc, char **argv)
{
	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);
	int ocolor = atoi(argv[3]);
	int ncolor = atoi(argv[4]);
	int **grid = new int*[rows];
	set<pair<int, int> > visited;
	
	allocate(grid, rows, cols);
	initialize(grid, rows, cols, ocolor);
	cout << "Input: " << endl;
	print_grid(grid, rows, cols);
	
	fill(grid, rows, cols, ocolor, ncolor, 1, 0, visited);
	cout << "Output: " << endl;
	print_grid(grid, rows, cols);
	delete[] grid;
	return (0);
}
