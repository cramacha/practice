#include <iostream>
#include "../sched/sched.h"

using namespace std;

/*
 * Class representing each array slice with pointers
 * indicating its left and right boundaries.
 */
class array_slice
{
public:
	array_slice(int *, int, int);
	int *arr;
	int left;
	int right;
};

array_slice::array_slice(int *arr, int left, int right)
{
	this->arr = arr;
	this->left = left;
	this->right = right;
}

void
array_slice_init(int *arr, array_slice *slices[], int len)
{
	assert(arr != NULL);
	int left = len/2;
	int right = left;
	if (len % 2 == 0)
		right--;
	slices[0] = new array_slice(arr, 0, left - 1);
	slices[1] = new array_slice(arr, left, left + right);
}

void
swap(int *arr, int x, int y)
{
	arr[x] = (arr[x] + arr[y]) - (arr[y] = arr[x]);
}

int
left_child(int x)
{
	return ((x * 2) + 1);
}

void
heap_sift_down(int *arr, int i, int len)
{
	int tmp;
	int child;
	for (tmp = arr[i]; left_child(i) < len; i = child) {
		child = left_child(i);
		if (child != len - 1 && arr[child] < arr[child + 1])
			child++;

		if (tmp >= arr[child])
			break;

		arr[i] = arr[child];
	}
	arr[i] = tmp;
}

void
heapify(int *arr, int start, int len)
{
	int i;
	for (i = len/2; i >=start; --i)
		heap_sift_down(arr, start, i);
}

void
heap_sort(int *arr, int start, int len)
{
	int i;
	assert(arr != NULL);
	heapify(arr, start, len);

	for (i = len - 1; i >= start; --i) {
		swap(arr, i, start);
		heap_sift_down(arr, start, i);
	}
}

void
sorting_func(void *args, int thread_num)
{
	array_slice *slice;
	assert(args != NULL);

	slice = (array_slice *)args;
	heap_sort(slice->arr, slice->left, slice->right);
}

void
merge_impl(int *arr, int lpos, int rpos, int rend)
{
	int elems;
	int *tmp;
	int l = lpos;
	int r = rpos + 1;
	int tmp_pos = 0;
	int i;
	elems = rend - lpos + 1;

	if ((tmp = (int *) malloc(elems * sizeof (int))) == NULL)
		return;

	while (l <= rpos && r <= rend) {
		if (arr[l] <= arr[r])
			tmp[tmp_pos++] = arr[l++];
		else
			tmp[tmp_pos++] = arr[r++];
	}

	while (l <= rpos)
		tmp[tmp_pos++] = arr[l++];
	while (r <= rend)
		tmp[tmp_pos++] = arr[r++];

	for (i = 0; i < elems; ++i)
		arr[i] = tmp[i];
}

void
merge_func(void *args, int thread_num)
{
	array_slice *slices;
	assert(args != NULL);
	slices = (array_slice *)args;

	merge_impl(slices[0].arr, slices[0].left, slices[0].right,
			slices[1].right);
}

void
print_array(int *arr, int len)
{
	int i;
	for (i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int
main(int argc, char **argv)
{
	int *arr;
	task *tp[2];
	task *merge;
	array_slice *slices[2];
	int i;
	int n = atoi(argv[1]);

	assert (argc == 1 && n > 0);

	/*  Scheduler with 2 tasks and 2 workers. */
	sched *sp = new sched(2,2);
	if ((arr = (int *) malloc(n * sizeof (int))) == NULL)
		exit(-1);
	(void) bzero(arr, n * sizeof (int));

	for (i = 0; i < n; i++)
		arr[i] = rand() % n;

	print_array(arr, n);

	/*  Initialize array slices. */
	array_slice_init(arr, slices, n);

	/*
	 * Create a new task with the sorting func to execute
	 * and post it to the scheduler.
	 */
	for (i = 0; i < 2; i++) {
		tp[i] = new task(1, sorting_func, (void *)&slices[i]);
		sp->post(tp[i], false);
	}

	/*  Execute all tasks in the scheduler. */
	(void) sp->execute();

	/*  Merge all the slices. */
	merge = new task(1, merge_func, (void *)&slices);
	sp->post(merge, false);
	(void) sp->execute();

	/*  We are done - cleanup resources. */
	(void) sp->done();
	print_array(arr, n);
	return (0);
}
