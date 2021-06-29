#include <iostream>
#include <vector>

using namespace std;

/*
 * We implement the actual stack using a vector of vectors.
 * 1. For push operation, we create a new stack when threshold is full.
 * 2. For pop operation, we pop from the back of the last vector. If
 *    the last vector is empty, we simply erase it from the vector of
 *    vectors.
 */
template <class T>
class stackset {
public:
	stackset<T>();
	stackset<T>(int);
	~stackset<T>();

	/*  Public modifiers */
	void push(T);
	void pop(void);
	void pop_at(int);

	/* Public accessors */
	int size(void) const;
	int top(void) const;
	int top_at(int) const;

	/*  Friends */
	template <class U>
	friend ostream& operator <<(ostream&, const stackset<U>&); 

	int threshold;
	vector<vector<T> > stacks;
};

template <class T>
stackset<T>::stackset()
{
	threshold = 1;
}

template <class T>
stackset<T>::stackset(int size)
{
	threshold = size;
}

template <class T>
stackset<T>::~stackset()
{}

template <class T>
void
stackset<T>::push(T val)
{
	if (stacks.size() == 0 || stacks.back().size() == threshold) {
		vector<T> st;
		stacks.push_back(st);
	}

	stacks.back().push_back(val);
}

template <class T>
void
stackset<T>::pop(void)
{
	if (stacks.size() == 0)
		return;

	stacks.back().pop_back();

	if (stacks.back().size() == 0)
		stacks.erase(stacks.begin() + stacks.size() - 1);
}

template <class T>
void
stackset<T>::pop_at(int index)
{
	if (stacks.size() == 0 || index < 0 || stacks.size() < index)
		return;

	stacks.at(index).pop_back();

	if (stacks.at(index).size() == 0)
		stacks.erase(stacks.begin() + index);	
}

template <class T>
int
stackset<T>::top(void) const
{
	return (stacks.back().back());
}

template <class T>
int
stackset<T>::top_at(int index) const
{
	if (index < 0 || stacks.size() < index)
		return (-1);

	return (stacks.at(index).back());
}

template <class U>
ostream&
operator <<(ostream &out, const stackset<U> &stackset)
{
	vector<vector<U> > st = stackset.stacks;
	for (int i = 0; i < st.size(); i++) {
		for (int j = 0; j < st.at(i).size(); j++) {
			out << st.at(i).at(j) << " ";
		}
		out << endl;
	}
	out << endl;
	return (out);
}

int
main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	int threshold = atoi(argv[2]);
	stackset<int> stacks(threshold);
	int i;
	for (i = 0; i < n; i++)
		stacks.push(i);

	cout << stacks; 
	stacks.pop();
	stacks.pop();
	cout << stacks; 

	stacks.pop();
	cout << stacks; 
	stacks.pop();
	cout << stacks; 
	stacks.pop_at(0);
	cout << stacks; 
	cout << stacks.top() << endl;
	return (0);
}
