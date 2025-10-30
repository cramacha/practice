#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

#include <iostream>
#include <cassert>

using namespace std;

// Node declaration.
template <class T>
class node {
	public:
		T val;
		node<T> *next;

		~node<T>();
		node<T>();
		node<T>(const T&);

		template<class U>
		friend ostream& operator <<(ostream&, node<U>&);
};

template <class T>
node<T>::node() {
	next = nullptr;
}

template <class T>
node<T>::~node() {
	val.~T();
	next = nullptr;
}

template <class T>
node<T>::node(const T &inp) {
	val = inp;
	next = nullptr;
}

template <class U>
ostream&
operator <<(ostream &out, node<U> &p) {
	out << p.val << endl;
}

// List declaration.
template <class T>
class list {
	public: 
		node<T> *head;

		// list of modifiers.
		void reverse(void);
		void push_front(T);
		void push_back(T);
		void pop_front(void);
		void pop_back(void);
		void append(list<T>&);
		void ordered_insert(T);

		// list of accessors.
		int size(void) const;
		node<T> *at(int) const;
		node<T> *get_tail() const;
		node<T> *get_head() const;
		void print(void) const;

		~list<T>();
		list<T>();

		template<class U>
		friend ostream& operator <<(ostream &out, const node<U>&);
};

template <class T>
list<T>::~list() {
	node<T> *pn = head;
	node<T> *tmp = pn;

	if (head == nullptr)
		return;

	while (tmp != nullptr) {
		pn = tmp;
		tmp = tmp->next;
		delete pn;
	}
}

template <class T>
list<T>::list() {
	head = nullptr;
}

template <class T>
void
list<T>::pop_front() {
	node<T> *pn = head;

	if (head == nullptr) {
		return;
	}

	head = head -> next;
	delete pn;
}

template <class T>
void
list<T>::reverse() {
	list<T> *rev = new list<int>();
	node<T> *pn = head;

	if (head == nullptr) {
		return;
	}

	while (pn != nullptr) {
		rev->push_front(pn->val);
		pn = pn->next;
		pop_front();
	}

	head = rev->get_head();
}

template <class T>
void
list<T>::push_front(T val) {
	node<T> *tmp = new node<T>(val);

	if (head == nullptr) {
		head = tmp;
		return;
	}

	tmp->next = head;
	head = tmp;
}

template <class T>
void
list<T>::push_back(T val) {
	node<T> *pn = head;
	node<T> *tmp = new node<T>(val);

	if (head == nullptr) {
		head = tmp;
		return;
	}

	for (;pn->next != nullptr; pn = pn->next);

	pn->next = tmp;
}

template <class T>
void
list<T>::pop_back() {
	node<T> *tmp = head;
	node<T> *tail, *pn;

	if (head == nullptr) {
		return;
	}

	for (pn = head; pn->next != nullptr; pn = pn->next) {
		tmp = pn;
	}

	tmp->next = nullptr;
	delete pn;
}

template <class T>
void
list<T>::append(list<T> &l) {
	node<T> *tmp = l.head;
	node<T> *tail;

	if (head == nullptr) {
		head = l.head;
		return;
	}

	tail = get_tail();
	tail->next = tmp;
}

template <class T>
void
list<T>::ordered_insert(T val) {
	node<T> *tmp = new node<T>(val);
	node<T> *pn = head;

	if (head == nullptr) {
		head = tmp;
		return;
	}

	for (; pn->next != nullptr && pn->next->val > tmp->val; pn = pn->next);

	tmp->next = pn->next;
	pn->next = tmp;
}

template <class T>
int
list<T>::size() const {
	node<T> *pn = head;
	int i = 0;

	for (;pn != nullptr; i++, pn = pn->next);

	return (i);
}

template <class T>
node<T>*
list<T>::at(int pos) const {
	node<T> *pn = head;
	node<T> *tmp;
	int s = size();
	
	assert(head != nullptr);
	assert(pos > 0 && pos <= s);

	for (int i = 0; pn != nullptr; i++, pn = pn->next) {
		if (i == pos) {
			tmp = pn;
			break;
		}
	}

	return (tmp);
 }

 template <class T>
 node<T>*
 list<T>::get_tail() const {
 	node<T> *pn = head;

 	assert(head != nullptr);

 	for (; pn->next != nullptr; pn = pn->next);

 	return (pn);
 }

 template <class T>
 node<T>*
 list<T>::get_head() const {
 	assert(head != nullptr);

 	return (head);
 }

 template <class T>
 void
 list<T>::print() const {
 	cout << "Printing list" << endl;
 	node<T> *pn = head;

 	if (head == nullptr) {
 		return;
 	}

 	for (;pn != nullptr; pn = pn->next) {
 		cout << pn->val << " ";
 	}

 	cout << endl;
 }

#endif /* SINGLY_LINKED_LIST */
