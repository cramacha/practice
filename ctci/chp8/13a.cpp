#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class box
{
public:
	int w;
	int h;
	int d;
	bool top_of(box &bottom)
	{
		return (h < bottom.h && w < bottom.w && d < bottom.d);
	}
};

class boxcompare
{
public:
	bool operator()(const box &a, const box &b)
	{
		return (a.h > b.h);
	}
};

ostream&
operator <<(ostream &out, vector<box> &path)
{
	for (int i = 0; i < path.size(); i++)
		out << path[i].h << " " << path[i].w << " "
			<< path[i].d << endl;
	return (out);
}

void
initialize(vector<box> &boxes)
{
	for (int i = 0; i < boxes.size(); i++)
	{
		boxes[i].w = boxes[i].h = boxes[i].d = rand() % 10;
	}	
}

int
stack_with_bottom(int index, vector<box> &boxes, vector<box> &path)
{
	int height = 0;
	int max_height = 0;
	box bottom = boxes[index];

	for (int i = index + 1; i < boxes.size(); i++)
	{
		if (boxes[i].top_of(bottom))
		{
			path.push_back(boxes[i]);
			height = stack_with_bottom(i, boxes, path);
			path.pop_back();
			max_height = max(max_height, height);
		}
	}

	if (index == boxes.size() - 1)
		cout << "Path: " << endl << path << endl;
	return (max_height + bottom.h);	
}

int
stack_impl(vector<box> &boxes, vector<box> &path)
{
	int max_height = 0;
	for (int i = 0; i < boxes.size(); i++)
	{
		path.push_back(boxes[i]);
		int height = stack_with_bottom(i, boxes, path);
		max_height = max(height, max_height);
		path.pop_back();		
	}
	return (max_height);	
}

void
stack(vector<box> &boxes)
{
	boxcompare cmp;
	vector<box> path;
	sort(boxes.begin(), boxes.end(), cmp);
	cout << "After sorting by height: " << endl << boxes << endl;
	int max_height = stack_impl(boxes, path);
	cout << "max height = " << max_height << endl;
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	vector<box> boxes(n);
	initialize(boxes);
	cout << "Input: " << endl << boxes << endl;
	stack(boxes);
	return(0);
}
