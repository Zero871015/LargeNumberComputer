#include "Computer.h"
#include "InorderToPostorder.h"
#include "BigNumber.h"
#include "BigDecimal.h"
#include <vector>

BigNumber& Computer(string str)
{
	vector<BigNumber*> stackNumber;	//�@��stack�Ω�s��B�⤸
	BigDecimal tran;	//����ഫ���p�ƪ��Ȧs��
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
					if (size < 2)
					{
						//���~�A�B�⦡�����~
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
				//�q���|���X��Ӽư���k
				else if (temp == "-")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
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
				//�q���|���X��Ӽư����k
				else if (temp == "*")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
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
				//�q���|���X��Ӽư����k
				else if (temp == "/")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
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
				//�q���|���X�@�Ӽƥ[�t��
				else if (temp == "@")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
						BigNumber* error = new BigNumber();
						error->error = 2;
						return *error;
					}
					stackNumber[size - 1]->Nagetive();
				}
				//�q���|���X��Ӽư�����
				else if (temp == "^")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
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
				//�q���|���X�@�Ӽư����h
				else if (temp == "!")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
						BigNumber* error = new BigNumber();
						error->error = 2;
						return *error;
					}
					stackNumber[size - 1]->Factorial();
				}
			}
			//���O�B��Ÿ��A�N��䬰�B�⤸
			//�N���Ʃ�J���|��
			//���ˬd�O�_���ܼ�
			else
			{
				//�ܼƲĤ@�Ӧr���^��
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
						//���~�A�X�{���s�b���ܼ�
						BigNumber* error=new BigNumber();
						error->error = 1;
						return *error;
					}
				}
				//���O�ܼơA�P�_�䬰�p���٬O���
				else
				{
					int isPoint = 0;
					for (int i = 0; i < (int)temp.length(); i++)
					{
						if (temp[i] == '.')
						{
							if (isPoint++ > 0)
							{
								//���~�A�B�⦡�����~
								BigNumber* error = new BigNumber();
								error->error = 2;
								return *error;
							}
						}
						else if (temp[i] > '9' || temp[i] < '0')
						{
							//���~�A�B�⦡�����~
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
			//�٨S�J����j�Ÿ��A�N��Ӧr���P�e���O�@�骺
			temp += str[i];
		}
	}
	return *stackNumber[0];
}
