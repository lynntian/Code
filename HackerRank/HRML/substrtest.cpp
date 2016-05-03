#include <string>
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	//string test2 = "a b c d e";
	istringstream test2 ("<tag name = rgdf");

/*	auto i1 = test2.find(' ');
	cout << i1 << endl;
	cout << test2.substr(0, i1) << endl;

	auto i2 = test2.find(' ', i1);

	cout << i2 << endl;
	cout << test2.substr(i1+1, i2) << endl;

	auto i3 = test2.find(' ', i2);
	cout << i3 << endl;

	cout << test2.substr(i1+1+ i2+1, i3) << endl;
*/
	string s;

	while(getline(test2, s, ' '))
	{
		cout << s << endl;
	}
}