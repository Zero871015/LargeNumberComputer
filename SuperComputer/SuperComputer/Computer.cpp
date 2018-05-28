#include "Computer.h"
#include "InorderToPostorder.h"
#include "BigNumber.h"
#include "BigDecimal.h"
#include <vector>

void Computer(string str)
{
	vector<BigNumber*> stackNumber;	//一個stack用於存放運算元
	BigDecimal tran;
	string temp = "";	//一個暫存空間
	for (int i = 0; i < (int)str.length(); i++)
	{
		//假如遇上分隔字元...
		if (str[i] == ' ')
		{
			//判斷其是否為運算子
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = (int)stackNumber.size();
				//從堆疊拿出兩個數做加法
				if (temp == "+")
				{
					if (stackNumber[size - 1]->isDecimal() && !stackNumber[size - 2]->isDecimal())
						swap(stackNumber[size - 1], stackNumber[size - 2]);
					stackNumber[size - 2]->Add(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					stackNumber[size - 1]->Print();
				}
				//從堆疊拿出兩個數做減法
				else if (temp == "-")
				{
					stackNumber[size - 2]->Subtract(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					stackNumber[size - 1]->Print();
				}
				//從堆疊拿出兩個數做乘法
				else if (temp == "*")
				{
					if (stackNumber[size - 1]->isDecimal() && !stackNumber[size - 2]->isDecimal())
						swap(stackNumber[size - 1], stackNumber[size - 2]);
					stackNumber[size - 2]->Multiply(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					stackNumber[size - 1]->Print();
				}
				//從堆疊拿出兩個數做除法
				else if (temp == "/")
				{
					if (stackNumber[size - 1]->isDecimal() && !stackNumber[size - 2]->isDecimal())
						swap(stackNumber[size - 1], stackNumber[size - 2]);
					stackNumber[size - 2]->Divide(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					stackNumber[size - 1]->Print();
				}
				//從堆疊拿出一個數加負號
				else if (temp == "@")
				{
					stackNumber[size - 1]->Nagetive();
					stackNumber[size - 1]->Print();
				}
				//從堆疊拿出兩個數做次方
				else if (temp == "^")
				{
					stackNumber[size - 2]->Power(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					stackNumber[size - 1]->Print();
				}
				//從堆疊拿出一個數做階層
				else if (temp == "!")
				{
					stackNumber[size - 1]->factorial();
					stackNumber[size - 1]->Print();
				}
			}
			else
			{
				bool isPoint = false;
				for (int i = 0; i < (int)temp.length(); i++)
				{
					if (temp[i] == '.')
					{
						isPoint = true;
						break;
					}
				}
				if (isPoint)
				{
					auto bigNum = new BigDecimal(temp);
					stackNumber.push_back(bigNum);
				}
				else
				{
					auto bigNum = new BigNumber(temp);
					stackNumber.push_back(bigNum);
				}
				//不是運算符號，代表其為運算元
				//將此數放入堆疊中
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
