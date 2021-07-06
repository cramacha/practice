#include "heap.h"
#include "heap_sort.h"

int
main(int argc, char **argv)
{
	heap<int> *hp;
	heap_cmp<int> cmp;
	int *data;
	int i;
	int n = atoi(argv[1]);
	if ((data = (int *) malloc(n * sizeof (int))) == NULL) {
		free(data);
		return (0);
	}
	
	(void) bzero(data, n * sizeof (int));

	hp = new heap<int>(data, n, cmp);
	for (i = n; i > 0; i--)
		hp->insert(i);
	hp->print();
	heap_sort(hp);
	cout << "after sorting:" << endl;
	hp->print();
	return (0);
}
