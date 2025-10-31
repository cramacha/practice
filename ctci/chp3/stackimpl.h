#ifndef STACK_IMPL
#define STACK_IMPL

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

template <class T>
class stack {
	public:
		stack<T>();
		~stack<T>();

		/* public modifiers */
		void push(T);
		void pop(void);
		void empty(void);


		/* public accessors */
		T top(void) const;
		int size(void) const;

		/* friends */
		template <class U>
		friend ostream& operator<<(ostream&, const stack<U>&);

		vector<T> data;
};


template <class T>
stack<T>::stack() 
{}

template <class T>
stack<T>::~stack() 
{}

template <class T>
void
stack<T>::push(T val) {
	data.push_back(val);
}

template <class T>
void
stack<T>::pop() {
	if (size() == 0)
		return;
	data.pop_back();
}

template <class T>
void
stack<T>::empty() {
	int len = size();

	if (size() == 0)
		return;

	for (int i = 0; i < len; i++) {
		data.pop_back();
	}
}

template <class T>
int
stack<T>::size() const {
	return (data.size());
}

template <class T>
T
stack<T>::top() const {
	assert(data.size() > 0);

	return (data.back());
}


template <class U>
ostream&
operator <<(ostream &out, const stack<U>& st) {
	int len = st.size();
	for (int i = 0; i < len; i++) {
		out << st.data.at(i) << " " << endl;
	}
	out << endl;
	return (out);
}

#endif /* STACK_IMPL */