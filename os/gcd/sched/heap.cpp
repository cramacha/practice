#include "heap.h"

heap::heap(int capacity)
{
	total = capacity;
	if ((elem = (heap_element *) malloc(total * sizeof (heap_element))) == NULL)
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

	(void) bzero(newarray, new_capacity * sizeof (heap_element));

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

	elem[used] = *input;
	sift_up(used);
	used++;
}

void
heap::remove(heap_element *out)
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

	assert(elem != NULL);

	for (tmp = elem[cur]; cur > 0; cur = parent) {
		parent = cur / 2;

		if (elem[cur].val > elem[parent].val)
			break;
		elem[cur] = elem[parent];
	}

	elem[cur] = tmp;
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

	assert(elem != NULL);

	for (tmp = elem[cur]; left_child(cur) < total; cur = lchild) {
		lchild = left_child(cur);

		/*  Pick the bigger child. */
		if (lchild < total
				&& elem[lchild].val < elem[lchild + 1].val)
			lchild++;

		if (elem[cur].val <= elem[lchild].val)
			break;

		elem[cur] = elem[lchild];
	}
	elem[cur] = tmp;
}




