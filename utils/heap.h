#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

/*  
 * Basic implementation of heap with the ability to provide a
 * custom comparator for your specific data type. This is handy
 * in the sift_up and sift_down operations. The logic for the custom
 * comparator is based off the answers in this post:
 * https://stackoverflow.com/questions/39734174/c-how-to-write-generic-comparator-function-for-int-double-string-etc-using-t.
 */
struct int_compare {
	bool operator()(const int &a, const int &b) const {
		return (a <= b);
	}
};

/*
 * If the declaration does not contain the int type
 * then we would use the standard std::less comparator.
 */
template <class T>
struct heap_compare {
	using type = std::less<T>;
};

/*
 * If the declaration contains the int type then
 * we will use the custom comparator below.
 */
template <>
struct heap_compare<int> {
	using type = int_compare;
};

/*
 * The following code is necessary in order to call
 * the comparator in the sift_up and sift_down
 * operations.
 */
template <class T>
using heap_cmp = typename heap_compare<T>::type;

template <class T>
class heap
{
private:
	int left_child(int);
public:
	heap<T>(T *, int, heap_cmp<T> cmp);
	~heap<T>();

	/*  Public modifiers */
	bool empty(void);
	bool full(void);
	bool double_heap(void);
	void sift_up(int);
	void sift_down(int, int);
	void insert(T);
	void remove(T *);
	void print(void);

	T *data;
	heap_cmp<T> cmp;
	int capacity;
	int used;
};

template <class T>
heap<T>::heap(T *data, int capacity, heap_cmp<T> cmp)
{
	this->data = data;
	this->capacity = capacity;
	this->cmp = cmp;
	used = 0;
}

template <class T>
heap<T>::~heap()
{
	delete data;
	data = NULL;
}

template <class T>
bool
heap<T>::empty(void)
{
	return (used == 0);
}

template <class T>
bool
heap<T>::full(void)
{
	return (used == capacity);
}

template <class T>
bool
heap<T>::double_heap(void)
{
	assert(data != NULL);
	int double_capacity = capacity * 2;
	T *newarray;
	if ((newarray = (T *) malloc(double_capacity * sizeof (T))) == NULL) {
		free(newarray);
		return (false);
	}
	(void) bzero(newarray, double_capacity * sizeof (T));
	(void) memcpy(newarray, data, capacity * sizeof (T));
	free(data);
	data = newarray;
	return (true);	
}

template <class T>
void
heap<T>::print(void)
{
	int i;
	int x;
	for (i = 0; i < used; i++) {
		cout << data[i] << " ";
		x = i + 2;

		/*
		 * A power of 2 would indicate completion of a single level.
		 */
		if (!(x & (x - 1)))
			cout << endl;
	}
	cout << endl;
}

template <class T>
void
heap<T>::insert(T elem)
{
	assert(data != NULL);

	/*  
	 *  Heap is full and effort to double heap is
	 *  unsuccessful.
	 */
	if (full() && !double_heap()) {
		cout << "Full heap!" << endl;
		return;
	}	

	data[used] = elem;
	sift_up(used);
	used++;
}

template <class T>
void
heap<T>::sift_up(int cur)
{
	T tmp;
	int parent;
	for (tmp = data[cur]; cur > 0; cur = parent) {
		parent = cur / 2;

		/*
		 * This is same as:
		 * if (tmp > data[parent]).
		 */
		if (!cmp(tmp, data[parent]))
			break;
		data[cur] = data[parent];
	}
	data[cur] = tmp;
}

template <class T>
void
heap<T>::remove(T *elem)
{
	assert(data != NULL && used > 0);

	*elem = data[0];
	data[0] = data[used - 1];
	sift_down(0, used - 1);
	used--;
}

template <class T>
int
heap<T>::left_child(int i)
{
	return ((i * 2) + 1);
}

template <class T>
void
heap<T>::sift_down(int cur, int len)
{
	T tmp;
	int child;
	for (tmp = data[cur]; left_child(cur) < len; cur = child) {
		child = left_child(cur);

		/*
		 * This is same as:
		 * if (data[child + 1] <= data[child])
		 */
		if (child != len - 1
				&& (cmp(data[child + 1], data[child])))
			child++;

		/*
		 * This is same as:
		 * if (tmp < data[child])
		 */
		if (cmp(tmp, data[child]))
			   break;

		data[cur] = data[child];
	}
	data[cur] = tmp;
}

#endif /*  HEAP_H */
