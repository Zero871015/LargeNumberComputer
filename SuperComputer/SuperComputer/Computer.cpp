#include "Computer.h"
#include "InorderToPostorder.h"
#include <vector>

void Computer(string str)
{
	vector<string> stackNumber;	//一個stack用於存放運算元
	string temp = "";	//一個暫存空間
	for (int i = 0; i < (int)str.length(); i++)
	{
		//假如遇上分隔字元...
		if (str[i] == ' ')
		{
			//判斷其是否為運算子
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = stackNumber.size();
				string ans = "(";
				//從堆疊拿出兩個數做加法
				if (temp == "+")
				{
					ans += stackNumber[size - 2] + "+" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//從堆疊拿出兩個數做減法
				else if (temp == "-")
				{
					ans += stackNumber[size - 2] + "-" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//從堆疊拿出兩個數做乘法
				else if (temp == "*")
				{
					ans += stackNumber[size - 2] + "*" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//從堆疊拿出兩個數做除法
				else if (temp == "/")
				{
					ans += stackNumber[size - 2] + "/" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//從堆疊拿出一個數加負號
				else if (temp == "@")
				{
					ans += '-' + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//從堆疊拿出兩個數做次方
				else if (temp == "^")
				{
					ans += stackNumber[size - 2] + "^" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//從堆疊拿出一個數做階層
				else if (temp == "!")
				{
					ans += stackNumber[size - 1]+"!)";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
			}
			else
			{
				//不是運算符號，代表其為運算元
				//將此數放入堆疊中
				stackNumber.push_back(temp);
			}
			temp = "";
		}
		else
		{
			//還沒遇到分隔符號，代表該字元與前面是一體的
			temp += str[i];
		}
	}
}
