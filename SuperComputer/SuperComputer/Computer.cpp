#include "Computer.h"
#include "InorderToPostorder.h"
#include "BigNumber.h"
#include <vector>

void Computer(string str)
{
	vector<BigNumber> stackNumber;	//�@��stack�Ω�s��B�⤸
	string temp = "";	//�@�ӼȦs�Ŷ�
	BigNumber bigNum;
	for (int i = 0; i < (int)str.length(); i++)
	{
		//���p�J�W���j�r��...
		if (str[i] == ' ')
		{
			//�P�_��O�_���B��l
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = (int)stackNumber.size();
				//�q���|���X��Ӽư��[�k
				if (temp == "+")
				{
					bigNum = Add(stackNumber[size - 2], stackNumber[size - 1]);
					bigNum.Print();
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(bigNum);
				}
				//�q���|���X��Ӽư���k
				else if (temp == "-")
				{
					bigNum = Subtract(stackNumber[size - 2], stackNumber[size - 1]);
					bigNum.Print();
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(bigNum);
				}
				//�q���|���X��Ӽư����k
				else if (temp == "*")
				{
					bigNum = Multiply(stackNumber[size - 2], stackNumber[size - 1]);
					bigNum.Print();
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(bigNum);
				}
				//�q���|���X��Ӽư����k
				else if (temp == "/")
				{
					bigNum = Divide(stackNumber[size - 2], stackNumber[size - 1]);
					bigNum.Print();
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(bigNum);
				}
				//�q���|���X�@�Ӽƥ[�t��
				else if (temp == "@")
				{
					bigNum = Nagetive(stackNumber[size - 1]);
					bigNum.Print();
					stackNumber.pop_back();
					stackNumber.push_back(bigNum);
				}
				//�q���|���X��Ӽư�����
				else if (temp == "^")
				{
					/*ans += stackNumber[size - 2] + "^" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);*/
				}
				//�q���|���X�@�Ӽư����h
				else if (temp == "!")
				{
					/*ans += stackNumber[size - 1]+"!)";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.push_back(ans);*/
				}
			}
			else
			{
				bigNum = BigNumber(temp);
				//���O�B��Ÿ��A�N��䬰�B�⤸
				//�N���Ʃ�J���|��
				stackNumber.push_back(bigNum);
			}
			temp = "";
		}
		else
		{
			//�٨S�J����j�Ÿ��A�N��Ӧr���P�e���O�@�骺
			temp += str[i];
		}
	}
}
