#include <iostream>
#include <string>
#include "InorderToPostorder.h"
#include "Computer.h"
using namespace std;

int main()
{
	string str;
	while (getline(cin,str))
	{
		cout << "�ഫ����ǡG" << endl;
		str = Postorder(str);
		cout << str << endl;

		Computer(str);
	}
	return 0;
}