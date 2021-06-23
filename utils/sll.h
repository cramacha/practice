#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

#include <iostream>
#include <cassert>

using namespace std;

template <class T>
class node {
	public:
		T val;
		node<T> *next;
		~node<T>();
		node<T>();
		node<T>(const T&);

		template <class U>
		friend ostream& operator <<(ostream &, const node<U> &);
};

template <class T>
node<T>::~node()
{
	val.~T();
	next = NULL;
}

template <class T>
node<T>::node(const T &inp)
{
	val = inp;
	next = NULL;
}

template <class T>
node<T>::node()
{
	next = NULL;
}

template <class U>
ostream&
operator <<(ostream &out, const node<U> &pn)
{
	out << pn.val << endl;
}

template <class T>
class list {
	public:
		
		/*  Public modifiers. */
		void reverse(void);
		void push_front(T);
		void push_back(T);
		void pop_front(void);
		void pop_back(void);
		void append(list<T> &);
		void ordered_insert(T);

		/*  Public accessors. */
		int size(void) const;
		node<T> *get_tail(void) const;
		node<T> *get_head(void) const;
		node<T> *at(int) const;
		void print(void) const;

		node<T> *head;
		~list<T>();
		list<T>();

		template <class U>
		friend ostream& operator <<(ostream &out, const node<U> &);
};
 
template <class T>
list<T>::~list()
{
	node<T> *pn = head;
	node<T> *tmp = pn;

	while (tmp != NULL) {
		pn = tmp;
		tmp = tmp->next;
		delete tmp;
	}
	head = NULL;
}

template <class T>
list<T>::list()
{
	head = NULL;
}

template <class T>
void
list<T>::push_front(T inp)
{
	node<T> *tmp = new node<T>(inp);

	if (head == NULL) {
		head = tmp;
		return;
	}

	tmp->next = head;
	head = tmp;
}

template <class T>
void
list<T>::push_back(T inp)
{
	node<T> *tmp = new node<T>(inp);
	node<T> *tail;

	if (head == NULL) {
		head = tmp;
		return;
	}

	tail = get_tail();
	tail->next = tmp;
}

template <class T>
void
list<T>::pop_front(void)
{
	if (head == NULL) {
		cout << "empty list, nothing to pop!" << endl;
		return;
	}

	node<T> *tmp = head;
	head = head->next;
	delete tmp;
}

template <class T>
void
list<T>::pop_back(void)
{
	node<T> *tail;
	node<T> *tmp = head;
	if (head == NULL) {
		cout << "empty list, nothing to pop!" << endl;
		return;
	}

	tail = get_tail();
	
	for (; tmp->next != tail; tmp = tmp->next);

	tmp->next = NULL;
	delete tail;
}

template <class T>
void
list<T>::reverse(void)
{
	list<T> *tmp = new list();
	node<T> *pn = head;

	if (head == NULL)
		return;

	while (pn != NULL) {
		tmp->push_front(pn->val);
		pn = pn->next;
		pop_front();
	}

	head = tmp->head;
}

template <class T>
void
list<T>::append(list<T> &l)
{
	node<T> *tail;
	node<T> *pn = l.head;
	if (head == NULL) {
		head = l.head;
		return;
	}

	tail = get_tail();
	tail->next = l.head;
}

template <class T>
void
list<T>::ordered_insert(T val)
{
	node<T> *pn;
	node<T> *tmp = new node<T>(val);
	if (head == NULL) {
		head = tmp;
		return;
	}

	if (tmp->val <= head->val) {
		tmp->next = head;
		head = tmp;
		return;
	}

	for (pn = head; pn->next != NULL 
			&& pn->next->val < tmp->val; pn = pn->next);

	tmp->next = pn->next;
	pn->next = tmp;
}

template <class T>
int
list<T>::size(void) const
{
	node<T> *pn;
	int i = 0;
	for (pn = head; pn != NULL; i++, pn = pn->next);
	return (i);
}

template <class T>
node<T>*
list<T>::get_tail(void) const
{
	node<T> *pn = head;
	for (; pn->next != NULL; pn = pn->next);

	return (pn);
}

template <class T>
node<T>*
list<T>::get_head(void) const
{
	return (head);
}

template <class T>
node<T>*
list<T>::at(int id) const
{
	int i = 0;
	node<T> *pn;

	assert (head != NULL);

	int list_size = size();

	assert (id <= list_size);

	for (pn = head; i < id; i++, pn = pn->next);

	return (pn);	
}

template <class T>
void
list<T>::print(void) const
{
	if (head == NULL) {
		cout << "empty list!" << endl;
		return;
	}

	node<T> *tmp = head;
	while (tmp != NULL) {
		cout << tmp->val << " ";
		tmp = tmp->next;
	}
	cout << endl;
}

#endif /*  SINGLY_LINKED_LIST */
