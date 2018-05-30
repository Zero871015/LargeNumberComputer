#include "Computer.h"
#include "InorderToPostorder.h"
#include "BigNumber.h"
#include "BigDecimal.h"
#include <vector>

BigNumber& Computer(string str)
{
	vector<BigNumber*> stackNumber;	//一個stack用於存放運算元
	BigDecimal tran;	//整數轉換為小數的暫存器
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
					if (size < 2)
					{
						//錯誤，運算式有錯誤
						BigNumber* error = new BigNumber();
						error->error = 2;
						return *error;
					}
					if (stackNumber[size - 1]->isDecimal() && !stackNumber[size - 2]->isDecimal())
						swap(stackNumber[size - 1], stackNumber[size - 2]);
					stackNumber[size - 2]->Add(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出兩個數做減法
				else if (temp == "-")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
						BigNumber* error = new BigNumber();
						error->error = 2;
						return *error;
					}
					if (stackNumber[size - 1]->isDecimal() && !stackNumber[size - 2]->isDecimal())
					{
						swap(stackNumber[size - 1], stackNumber[size - 2]);
						stackNumber[size - 1]->Nagetive();
						stackNumber[size - 2]->Nagetive();
					}
					stackNumber[size - 2]->Subtract(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出兩個數做乘法
				else if (temp == "*")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
						BigNumber* error = new BigNumber();
						error->error = 2;
						return *error;
					}
					if (stackNumber[size - 1]->isDecimal() && !stackNumber[size - 2]->isDecimal())
						swap(stackNumber[size - 1], stackNumber[size - 2]);
					stackNumber[size - 2]->Multiply(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出兩個數做除法
				else if (temp == "/")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
						BigNumber* error = new BigNumber();
						error->error = 2;
						return *error;
					}
					if (stackNumber[size - 1]->isDecimal() && !stackNumber[size - 2]->isDecimal())
					{
						BigDecimal buffer(*stackNumber[size - 1]);
						buffer.setDenominator(stackNumber[size - 1]->getDenominator());
						swap(stackNumber[size - 1], stackNumber[size - 2]);
						stackNumber[size - 2]->setDenominator(stackNumber[size-1]->getDenominator());
						stackNumber[size-2]->numerator=stackNumber[size-1]->numerator;
						stackNumber[size - 2]->Divide(buffer);
					}
					else
						stackNumber[size - 2]->Divide(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出一個數加負號
				else if (temp == "@")
				{
					if (size < 1)
					{
						//錯誤，運算式有錯誤
						BigNumber* error = new BigNumber();
						error->error = 2;
						return *error;
					}
					stackNumber[size - 1]->Nagetive();
				}
				//從堆疊拿出兩個數做次方
				else if (temp == "^")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
						BigNumber* error = new BigNumber();
						error->error = 2;
						return *error;
					}
					stackNumber[size - 2]->Power(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					if (stackNumber[size - 1]->error != 0)
					{
						return *stackNumber[size - 1];
					}
				}
				//從堆疊拿出一個數做階層
				else if (temp == "!")
				{
					if (size < 1)
					{
						//錯誤，運算式有錯誤
						BigNumber* error = new BigNumber();
						error->error = 2;
						return *error;
					}
					stackNumber[size - 1]->Factorial();
				}
			}
			//不是運算符號，代表其為運算元
			//將此數放入堆疊中
			//先檢查是否為變數
			else
			{
				//變數第一個字為英文
				if ((temp[0] >= 'a'&&temp[0] <= 'z') || (temp[0] >= 'A'&&temp[0] <= 'Z'))
				{
					bool isFound = false;

					map<string, BigDecimal>::iterator itd;
					itd = BigDecimal::bigDecimals.find(temp);
					map<string, BigNumber>::iterator itn;
					itn = BigNumber::bigNumbers.find(temp);
					if (itd != BigDecimal::bigDecimals.end())
					{
						auto bigNum = new BigDecimal(BigDecimal::bigDecimals[temp]);
						stackNumber.push_back(bigNum);
						isFound = true;
					}
					else if (isFound == false && itn != BigNumber::bigNumbers.end())
					{
						auto bigNum = new BigNumber(BigNumber::bigNumbers[temp]);
						stackNumber.push_back(bigNum);
					}
					else
					{
						//錯誤，出現不存在的變數
						BigNumber* error=new BigNumber();
						error->error = 1;
						return *error;
					}
				}
				//不是變數，判斷其為小數還是整數
				else
				{
					int isPoint = 0;
					for (int i = 0; i < (int)temp.length(); i++)
					{
						if (temp[i] == '.')
						{
							if (isPoint++ > 0)
							{
								//錯誤，運算式有錯誤
								BigNumber* error = new BigNumber();
								error->error = 2;
								return *error;
							}
						}
						else if (temp[i] > '9' || temp[i] < '0')
						{
							//錯誤，運算式有錯誤
							BigNumber* error = new BigNumber();
							error->error = 2;
							return *error;
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
				}
				
			}
			temp = "";
		}
		else
		{
			//還沒遇到分隔符號，代表該字元與前面是一體的
			temp += str[i];
		}
	}
	return *stackNumber[0];
}
