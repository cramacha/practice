#include "stackimpl.h"

int main(int argc, char **argv) {
	stack<int> st;
	st.push(10);

	cout << st << endl;

	st.push(1);
	st.push(2);

	cout << st << endl;

	st.pop();
	cout << st << endl;

	cout << "top = " << st.top() << endl;
	
	return (0);
}