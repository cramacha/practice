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
public:
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
	void remove(heap_element *);
	void sift_up(int);
	void sift_down(int, int);

	heap_element *elem;
	int used;
	int total;
private:
	int left_child(int);
};

#endif /*  HEAP_H_ */
