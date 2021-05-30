#include <iostream>
#include <string>

using namespace std;

void
convert(double d)
{
	string binary;
	while (d != 0)
	{
		if (binary.size() > 31)
		{
			cout << "ERROR" << endl;
			break;
		}
		d *= 2;
		if (d > 1)
		{
			binary += "1";
			d -= 1;
		}
		else
			binary += "0";
	}
	cout << binary << endl;	
}

int
main(int argc, char **argv)
{
	double d = stod(argv[1]);
	convert(d);
	return (0);
}
