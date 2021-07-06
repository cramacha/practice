#include "heap.h"

template <class T>
void
heap_sort(heap<T> *hp)
{
	int i;
	for (i = hp->used - 1; i > 0; --i) {
		swap(hp->data[0], hp->data[i]);
		hp->sift_down(0, i - 1);
		cout << "level : " << i << endl;
		hp->print();	
	}
}

