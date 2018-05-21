#include "Computer.h"
#include "InorderToPostorder.h"
#include <vector>

void Computer(string str)
{
	vector<string> stackNumber;
	string temp = "";
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (str[i] == ' ')
		{
			if ((int)temp.length()==1&&(isOperator(temp[0]) || temp == "!"))
			{
				int size = stackNumber.size();
				string ans = "(";
				if (temp == "+")
				{
					ans += stackNumber[size - 2] + "+" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				else if (temp == "-")
				{
					ans += stackNumber[size - 2] + "-" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				else if (temp == "*")
				{
					ans += stackNumber[size - 2] + "*" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				else if (temp == "/")
				{
					ans += stackNumber[size - 2] + "/" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				else if (temp == "^")
				{
					ans += stackNumber[size - 2] + "^" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				else if (temp == "!")
				{
					ans += stackNumber[size - 1]+"!)";
					cout << ans << endl;
					stackNumber.push_back(ans);
				}
			}
			else
			{
				stackNumber.push_back(temp);
			}
			temp = "";
		}
		else
		{
			temp += str[i];
		}
	}
}
