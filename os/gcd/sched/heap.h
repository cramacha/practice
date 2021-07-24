#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <cstring>

using namespace std;

/*
 * Basic heap with none of the frills associated. For a more
 * comprehensive heap, look at the implementation in the utils
 * folder.
 */
class heap_element
{
	/*  Priority is saved here. */
	int val;

	/*  The task fptr is stored here. */
	void *meta;
};

class heap
{
public:
	heap(int);
	~heap();

	bool double_heap();
	bool empty();
	bool full();
	void insert(heap_element *);
	void remove(heap_element **);
	void sift_up(int);
	void sift_down(int, int);

	heap_element *elem;
	int used;
	int total;
private:
	int left_child(int);
};

heap::heap(int capacity)
{
	total = capacity;
	if ((elem = (heap_element *) malloc(total * sizeof (heap_element)) == NULL)
			return;

	(void) bzero(elem, total * sizeof (heap_element));
}

heap::~heap()
{
	free(elem);
	elem = NULL;
}

bool
heap::double_heap()
{
	heap_element *newarray;
	int new_capacity = total * 2;

	assert(elem != NULL);

	if ((newarray = (heap_element *) malloc(new_capacity * sizeof (heap_element))) == NULL)
		return (false);

	(void) bzero(new_capacity * sizeof (heap_element));

	/*
	 * Note that the third argument to memcpy needs the size of the
	 * heap_element.
	 */
	(void) memcpy(newarray, elem, sizeof (heap_element) * total);
	free(elem);
	elem = newarray;
	total = new_capacity;
	return (true);
}

bool
heap::empty()
{
	return (used == 0);
}

bool
heap::full()
{
	return (used == total);
}

void
heap::insert(heap_element *input)
{
	assert(input != NULL);

	/*
	 * Nothing more to do if the heap is full and capacity
	 * cannot be increased. Return early.
	 */
	if (full() && !double_heap())
		return;

	elem[used] = input;
	sift_up(used);
	used++;
}

void
heap::remove(heap_element **out)
{
	if (empty())
		return;

	*out = elem[0];
	elem[0] = elem[used - 1];
	sift_down(0, used - 1);
	used--;
}

void
heap::sift_up(int cur)
{
	heap_element tmp;
	int parent;

	assert(heap_element != NULL && cur > 0);

	for (tmp = heap_element[cur]; tmp > 0; cur = parent) {
		parent = cur / 2;

		if (heap_element[cur].val > heap_element[parent].val)
			break;
		heap_element[cur] = heap_element[parent];
	}

	heap_element[cur] = tmp;
}

int
heap::left_child(int x)
{
	return ((x * 2) + 1);
}

void
heap::sift_down(int cur, int total)
{
	heap_element tmp;
	int lchild;

	assert(heap_element != NULL && total > 0);

	for (tmp = heap_element[cur]; left_child(cur) < total; cur = lchild) {
		lchild = left_child(cur);

		/*  Pick the bigger child. */
		if (lchild < total
				&& heap_element[lchild].val < heap_element[lchild + 1].val)
			lchild++;

		if (heap_element[cur].val <= heap_element[lchild].val)
			break;

		heap_element[cur] = heap_element[lchild];
	}
	heap_element[cur] = tmp;
}

#endif /*  HEAP_H_ */
