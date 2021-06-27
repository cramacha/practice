#ifndef STACK_H_
#define STACK_H_

#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

template <class T>
class stack {
public:
	stack<T>();
	~stack<T>();

	/*  Public modifiers. */
	void push(T);
	void pop();
	void empty();

	/*  Public accessors. */
	int size() const;
	T top() const;

	vector<T> data;

	/*  Friends */
	template <class U>
	friend ostream& operator <<(ostream &, const stack<U> &);
};

template <class T>
stack<T>::stack()
{}

template <class T>
stack<T>::~stack()
{}

template <class T>
void
stack<T>::push(T val)
{
	data.push_back(val);
}

template <class T>
void
stack<T>::pop()
{
	if (data.size() == 0)
		return;
	data.pop_back();
}

template <class T>
void
stack<T>::empty()
{
	while (data.size() > 0)
		data.pop_back();
}

template <class T>
T
stack<T>::top() const
{
	assert(data.size() != 0);
	return (data.back());
}

template <class T>
int
stack<T>::size() const
{
	return (data.size());
}

template <class U>
ostream&
operator <<(ostream &out, const stack<U> &s)
{
	int i;
	for (i = 0; i < s.data.size(); i++)
		out << s.data.at(i) << " ";
	out << endl;
	return (out);
}
#endif /*  STACK_H_ */
