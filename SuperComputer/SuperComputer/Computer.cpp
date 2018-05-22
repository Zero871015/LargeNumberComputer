#include "Computer.h"
#include "InorderToPostorder.h"
#include <vector>

void Computer(string str)
{
	vector<string> stackNumber;	//�@��stack�Ω�s��B�⤸
	string temp = "";	//�@�ӼȦs�Ŷ�
	for (int i = 0; i < (int)str.length(); i++)
	{
		//���p�J�W���j�r��...
		if (str[i] == ' ')
		{
			//�P�_��O�_���B��l
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = stackNumber.size();
				string ans = "(";
				//�q���|���X��Ӽư��[�k
				if (temp == "+")
				{
					ans += stackNumber[size - 2] + "+" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//�q���|���X��Ӽư���k
				else if (temp == "-")
				{
					ans += stackNumber[size - 2] + "-" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//�q���|���X��Ӽư����k
				else if (temp == "*")
				{
					ans += stackNumber[size - 2] + "*" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//�q���|���X��Ӽư����k
				else if (temp == "/")
				{
					ans += stackNumber[size - 2] + "/" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//�q���|���X�@�Ӽƥ[�t��
				else if (temp == "@")
				{
					ans += '-' + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//�q���|���X��Ӽư�����
				else if (temp == "^")
				{
					ans += stackNumber[size - 2] + "^" + stackNumber[size - 1] + ")";
					cout << ans << endl;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(ans);
				}
				//�q���|���X�@�Ӽư����h
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
				//���O�B��Ÿ��A�N��䬰�B�⤸
				//�N���Ʃ�J���|��
				stackNumber.push_back(temp);
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
