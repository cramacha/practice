#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

/*
 * We represent 3 stacks in a single array-like data structure
 * with adjustable lengths capable of growing in either left or
 * right direction depending on their position in the array.
 * For the purposes of this problem, the left stack grows from
 * left to right, the right one from right to left and the middle
 * one can grow both ways to fit the other two.
 *
 * Here the stack class represents a single stack with top and bottom
 * pointers, inc - representing 1 (if the stack grows left to right) or
 * -1 (if the stack grows right to left) and capacity of the stack.
 *
 * The arrows below show the direction in which the stacks can grow.
 * For all purposes the middle stack grows from left to right unless
 * it is required to be shifted in which case it can shift both ways
 * to accomodate left and right stacks.
 *  ----------------------------------------
 * |	LEFT--->|<---MIDDLE--->|<---RIGHT   |
 *  ---------------------------------------- 
 */ 

typedef enum stack_type
{
	LEFT,
	MIDDLE,
	RIGHT
} stack_type_t;

/*  Represents the direction of stack growth. */
typedef enum direction
{
	MOVE_LEFT,
	MOVE_RIGHT
} direction_t;

/*  Represents a single stack in an array of stacks. */
class stack
{
	public:
		int *top;
		int *bottom;
		int inc;
		int capacity;
		stack_type_t type;
		
		stack(int *, stack_type_t, int, int);
		
		/*  Public modifiers. */
		void push(int);
		void pop(int *);
		bool full(void);
		bool empty(void);
		void shift(direction_t);
		void print(void);

		/*  Public accessors. */
		int count(void) const;
};

/*  Represents the entire array of stacks. */
class stacks
{
	public:
		int *data;
		int capacity;
		stack *left;
		stack *middle;
		stack *right;

		stacks(int *, int);
		~stacks();
		/*  Public modifiers. */
		void push(stack_type_t, int);
		void pop(stack_type_t, int *);
		bool full(void);
		bool empty(void);
};

stack::stack(int *data, stack_type_t type, int inc, int capacity)
{
	this->capacity = capacity;
	this->top = this->bottom = data;
	this->inc = inc;
	this->type = type;
}

void
stack::push(int elem)
{
	assert (!full());
	
	*top = elem;
	top += inc;
}

void
stack::pop(int *val)
{
	assert(!empty());

	top -= inc;
	int *tmp = top;
	*val = *top;


	/*  This is done to view the 0s when we print the array. */
	*tmp = 0;
}

bool
stack::full(void)
{
	return (count() == capacity);
}

bool
stack::empty(void)
{
	return (top == bottom);
}

int
stack::count(void) const
{
	/*  
	 *  Grows left. Memory is in increasing units from left to
	 *  right.
	 */
	if (inc == -1)
		return (bottom - top);
	
	/*  Grows right. */
	return (top - bottom);
}

void
stack::print(void)
{
	int i, n;
	int *tmp = bottom;
	
	if (empty())
		return;

	n = count();
	for (i = 0; i < n; i++, tmp+=inc)
		cout << *tmp << " ";
	cout << endl;
}

void
stack::shift(direction_t dir)
{
	int *last;
	int n = count();

	/*  Learning some C magic here. */
	void *src = (dir == MOVE_LEFT) ? top + 1 : bottom; 
	void *dst = (int *) src + inc;

	(void) memmove(dst, src, n * sizeof (int));

	top += inc;
	bottom += inc;
}

stacks::~stacks()
{
	delete data;
	data = NULL;
}

stacks::stacks(int *data, int capacity)
{
	this->data = data;
	this->capacity = capacity;

	left = new stack(data, LEFT, 1, capacity);
	middle = new stack(data + (capacity/3), MIDDLE, 1, capacity);
	right = new stack(data + capacity, RIGHT, -1, capacity);
}

void
stacks::push(stack_type_t type, int elem)
{
	assert(!full());

	/*
	 * The left and middle stacks grow left to right.
	 * The right stack grows right to left (its top moves left).
	 */ 
	switch (type) {
		case LEFT:
			if (left->top == middle->bottom)
				middle->shift(MOVE_RIGHT);
			left->push(elem);
			break;
		case MIDDLE:
			if (middle->top == left->top)
				middle->shift(MOVE_RIGHT);
			middle->push(elem);
			break;
		case RIGHT:
			if (middle->top == left->top)
				middle->shift(MOVE_LEFT);
			right->push(elem);
			break;
		default:
			break;
	}
}

void
stacks::pop(stack_type_t type, int *elem)
{
	assert(!empty());

	switch (type) {
		case LEFT:
			left->pop(elem);
			break;
		case MIDDLE:
			middle->pop(elem);
			break;
		case RIGHT:
			right->pop(elem);
			break;
		default:
			break;
	}	
}

bool
stacks::full(void)
{
	/*
	 *  The top is already one ahead per the logic in the push
	 *  operation and so there is no need to add + 1 to these
	 *  checks.
	 */
	return (left->top == middle->bottom &&
				middle->top == right->top);
}

bool
stacks::empty(void)
{
	return (left->bottom == right->bottom);
}

int
main(int argc, char **argv)
{
	int i, val;
	int n = atoi(argv[1]);
	int *data = (int *) malloc (n * sizeof (int));
	(void) bzero(data, n * sizeof (int));
	stacks *st = new stacks(data, n);
	for (i = 0; i < n/3; i++) { 
		st->push(LEFT, i + 1);
		st->push(MIDDLE, (i + 1) * 3);
	}
	st->left->print();
	st->middle->print();
	st->push(LEFT, 100);
	st->left->print();
	st->middle->print();
	
	st->push(RIGHT, -1);
	st->right->print();
	st->push(RIGHT, -2);
	st->right->print();

	cout << "Popping left" << endl;
	while (!st->left->empty()) {
		st->left->pop(&val);
		cout << val << " ";
	}
	cout << endl;
	cout << "Popping right" << endl;
	while (!st->right->empty()) {
		st->right->pop(&val);
		cout << val << " ";
	}
	cout << endl;
	cout << "Popping middle" << endl;
	while (!st->middle->empty()) {
		st->middle->pop(&val);
		cout << val << " ";
	}
	cout << endl;

return (0);
}
