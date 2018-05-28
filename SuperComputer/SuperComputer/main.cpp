#include <iostream>
#include <string>
#include "InorderToPostorder.h"
#include "Computer.h"
#include <map>
using namespace std;




int main()
{
	string str;
	//BigNumber("1+1").Print();
	//BigNumber("2.1").Print();
	//BigDecimal("2.1").Print();
	while (getline(cin,str))
	{
		if ((int)str.length() > 14)
		{
			string name;
			string expression;
			string sub = str.substr(0, 12);
			if (sub == "Set Integer ")
			{
				bool isName = true;
				for (int i = 12; i < (int)str.length(); i++)
				{
					if (str[i] == '=')
						isName = false;
					else if (isName)
						name += str[i];
					else
						expression += str[i];
				}
				BigNumber::bigNumbers[name] = BigNumber(expression);
			}
			else if (sub == "Set Decimal ")
			{
				bool isName = true;
				for (int i = 12; i < (int)str.length(); i++)
				{
					if (str[i] == '=')
						isName = false;
					else if (isName)
						name += str[i];
					else
						expression += str[i];
				}
				BigDecimal::bigDecimals[name]=BigDecimal(expression);

			}
			else
			{
				cout << "轉換為後序：" << endl;
				str = Postorder(str);
				cout << str << endl;
				Computer(str).Print();
			}
		}
		else
		{
			cout << "轉換為後序：" << endl;
			str = Postorder(str);
			cout << str << endl;
			Computer(str).Print();
		}
	}
	return 0;
}