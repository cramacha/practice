#include <iostream>
#include "../../utils/stack.h"

using namespace std;

template <class T>
class queue {
public:
	queue<T>();
	~queue<T>();

	/*  Public modifiers */
	void insert(T);
	void pop(T *);

	/*  Friends */
	template <class U>
	friend ostream& operator <<(ostream&, queue<U>&);

	stack<T> s1;
	stack<T> s2;	
};

template <class T>
queue<T>::queue()
{}

template <class T>
queue<T>::~queue()
{}

/*
 * E.g. s1 = {1, 2} and s2 = {3} and val = 4
 *
 * After the while loop below, s1 = {}, s2 = {2, 1, 3}
 * (top is the leftmost element)
 *
 * After pushing val,
 * s1 = {4}, s2 = {2, 1, 3}
 */
template <class T>
void
queue<T>::insert(T val)
{
	while (s1.size() > 0) {
		T top = s1.top();
		s1.pop();
		s2.push(top);
	}
	s1.push(val);
}

/*
 * Using the same example as insert operation,
 * s1 = {4}, s2 = {2, 1, 3}
 *
 * After the while loop below, s1 = {4, 2, 1}
 * and top = 3
 */
template <class T>
void
queue<T>::pop(T *res)
{
	while (s2.size() > 0) {
		T top = s2.top();
		*res = top;
		s2.pop();
		s1.push(top);
	}
	s1.pop();
}

template <class U>
ostream &
operator <<(ostream &out, queue<U> &q)
{
	while (q.s1.size() > 0) {
		U top = q.s1.top();
		q.s1.pop();
		q.s2.push(top);
	}
	
	for (int j = 0; j < q.s2.size(); j++) {
		out << q.s2.data[j] << " ";		
	}
	out << endl;
	return (out);
}

int
main(int argc, char **argv)
{
	int *top = new int(-1);
	queue<int> q;
	int n = atoi(argv[1]);
	int i;
	for (i = 0; i < n; i++)
		q.insert(i);
	cout << q << endl;
	q.pop(top);
	cout << *top << endl;
	cout << q << endl;
	q.pop(top);
	cout << *top << endl;
	return (0);
}
