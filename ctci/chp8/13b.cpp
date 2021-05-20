#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class box
{
public:
	int h;
	int w;
	int d;
	bool top_of(box &other)
	{
		return (h < other.h && w < other.w && d < other.d);
	}
};

class boxcompare
{
public:
	bool operator ()(const box &a, const box &b)
	{
		return (a.h > b.h);
	}
};

ostream&
operator <<(ostream &out, vector<box> &path)
{
	for (int i = 0; i < path.size(); i++) 
	{
		out << path[i].h << " " << path[i].d 
			<< " " << path[i].w << endl;
	}
	return (out);
}

void
initialize(vector<box> &boxes)
{
	for (int i = 0; i < boxes.size(); i++)
		boxes[i].h = boxes[i].d = boxes[i].w = rand() % 10;
}

int
stack_impl(vector<box> boxes, box &bottom, int index, vector<box> &path)
{
	int height_with_bottom = bottom.h;
	int height_without_bottom = 0;
	if (index == boxes.size())
		return (0);
	box new_bottom = boxes[index];
	if (new_bottom.top_of(bottom))
		height_with_bottom += stack_impl(boxes, new_bottom, index + 1, path);
	height_without_bottom += stack_impl(boxes, bottom, index + 1, path);
	return (max(height_with_bottom, height_without_bottom));	
}

void
stack(vector<box> &boxes)
{
	vector<box> path;
	boxcompare cmp;
	cout << "Before sorting: " << endl << boxes << endl;
	sort(boxes.begin(), boxes.end(), cmp);
	cout << "After sorting: " << endl << boxes << endl;
	int max_height = stack_impl(boxes, boxes[0], 0, path);
	cout << "Max height: " << max_height << endl;
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	vector<box> boxes(n);
	initialize(boxes);
	stack(boxes);
	return (0);
}
