#include "Computer.h"
#include "InorderToPostorder.h"
#include "BigNumber.h"
#include "BigDecimal.h"
#include <vector>

void Computer(string str)
{
	vector<BigNumber*> stackNumber;	//�@��stack�Ω�s��B�⤸
	BigDecimal tran;
	string temp = "";	//�@�ӼȦs�Ŷ�
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
					if (stackNumber[size - 1]->isDecimal() && !stackNumber[size - 2]->isDecimal())
						swap(stackNumber[size - 1], stackNumber[size - 2]);
					stackNumber[size - 2]->Add(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					stackNumber[size - 1]->Print();
				}
				//�q���|���X��Ӽư���k
				else if (temp == "-")
				{
					stackNumber[size - 2]->Subtract(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					stackNumber[size - 1]->Print();
				}
				//�q���|���X��Ӽư����k
				else if (temp == "*")
				{
					if (stackNumber[size - 1]->isDecimal() && !stackNumber[size - 2]->isDecimal())
						swap(stackNumber[size - 1], stackNumber[size - 2]);
					stackNumber[size - 2]->Multiply(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					stackNumber[size - 1]->Print();
				}
				//�q���|���X��Ӽư����k
				else if (temp == "/")
				{
					if (stackNumber[size - 1]->isDecimal() && !stackNumber[size - 2]->isDecimal())
						swap(stackNumber[size - 1], stackNumber[size - 2]);
					stackNumber[size - 2]->Divide(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					stackNumber[size - 1]->Print();
				}
				//�q���|���X�@�Ӽƥ[�t��
				else if (temp == "@")
				{
					stackNumber[size - 1]->Nagetive();
					stackNumber[size - 1]->Print();
				}
				//�q���|���X��Ӽư�����
				else if (temp == "^")
				{
					stackNumber[size - 2]->Power(*stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
					stackNumber[size - 1]->Print();
				}
				//�q���|���X�@�Ӽư����h
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
				//���O�B��Ÿ��A�N��䬰�B�⤸
				//�N���Ʃ�J���|��
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
