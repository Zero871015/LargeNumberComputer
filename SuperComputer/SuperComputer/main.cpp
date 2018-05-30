// Name: B10615032,B10615020,B10615030
// Date: 05/17/2018
// Last Update: 05/31/2018
// Problem statement: A computer can use big number.

#define DEBUG

#include <iostream>
#include <string>
#include "InorderToPostorder.h"
#include "Computer.h"
#include <map>
#include <windows.h>
using namespace std;

//Console����
void UpdataScr(string in1,string in2)
{
	system("CLS");
	cout << "��J�G" << endl;
	cout  << endl << endl;
	cout << "------------------------" << endl;
	cout << "�W����J�G" << endl;
	cout << in1 << endl << endl;
	cout << "------------------------" << endl;
	cout << "�B�浲�G�G" << endl;
	cout << in2 << endl << endl;
	cout << "------------------------"  << endl;
	cout << "�ثe�s�b���ܼơG" << endl;
	cout << "��ơG" << endl;
	for (auto& i:BigNumber::bigNumbers)
	{
		cout << i.first << " : " << i.second << endl;
	}
	cout << endl << "�p�ơG" << endl;
	for (auto& i : BigDecimal::bigDecimals)
	{
		cout << i.first << " : " << i.second << endl;
	}

	//�վ��Ц�m
	HANDLE hOut;
	COORD c;
	c.X = 0; c.Y = 1;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, c);
}

int main()
{
#ifdef DEBUG
	//�����ᤩ�r�����
	BigNumber test1 = "10*3";
	UpdataScr("���դ@", test1.Print());
	system("pause");
	//�����ᤩ�r���p��
	BigDecimal test2 = "10.1";
	UpdataScr("���դG", test2.Print());
	system("pause");
	//��cin,cout��X
	system("CLS");
	cout << "��J�@�ӼƦr���]test1" << endl;
	cin >> test1;
	cout << test1 << endl;
	system("pause");
	//���ը�ث��O�i�H��J�P�@�e����
	system("CLS");
	vector<BigNumber*> nums;
	nums.push_back(&test1);
	nums.push_back(&test2);
	for (const auto& num : nums)
		cout << num->Print() << endl;
	system("pause");
#endif // DEBUG

	string str;			//��J�r��
	string result;		//���浲�G
	UpdataScr("","");	//��l��Console����
	while (getline(cin,str))
	{
		result = str;
		for (int i = (int)result.length()-1; i >= 0 ; i--)
		{
			if (result[i] == ' ')
				result.pop_back();
		}
		if (result == "")
		{
			UpdataScr("", "��J���ť�");
			continue;
		}
		else if ((int)str.length() == 0)
		{
			UpdataScr("", "��J���ť�");
			continue;
		}
		else if (str == ".")
		{
			UpdataScr("", "��J���~");
			continue;
		}
		string sub;
		string name;
		string expression;
		//�קK�s����range���~�A����>14�~��l�r��
		if ((int)str.length() > 14)
			sub = str.substr(0, 12);
		else
			sub = "";
		//�p�G�l�r��ŦX���O�A�ŧi����ܼ�
		if (sub == "Set Integer ")
		{
			bool isName = true;
			//�ھڵ�������ܼƦW�r�M�B�⦡
			for (int i = 12; i < (int)str.length(); i++)
			{
				if (str[i] == '=')
					isName = false;
				else if (isName)
					name += str[i];
				else
					expression += str[i];
			}
			if ((name[0] >= 'a'&&name[0] <= 'z') || (name[0] >= 'A'&&name[0] <= 'Z'))
			{
				//�ˬd�O�_�s�b�ۦP�W�٪��p���ܼ�
				auto it = BigDecimal::bigDecimals.find(name);
				if (it != BigDecimal::bigDecimals.end())
					BigDecimal::bigDecimals.erase(name);

				BigNumber::bigNumbers[name] = BigNumber(expression);
				result = "�w�]�m�ܼ�" + name;
			}
			else
			{
				result = "�ܼƦW�ٿ��~";
			}
		}
		//�p�Ƴ����A�P�z
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
			if ((name[0] >= 'a'&&name[0] <= 'z') || (name[0] >= 'A'&&name[0] <= 'Z'))
			{
				//�ˬd�O�_�s�b�ۦP�W�٪�����ܼ�
				auto it = BigNumber::bigNumbers.find(name);
				if (it != BigNumber::bigNumbers.end())
					BigNumber::bigNumbers.erase(name);
				BigDecimal::bigDecimals[name] = BigDecimal(expression);
				result = "�w�]�m�ܼ�" + name;
			}
			else
			{
				result = "�ܼƦW�ٿ��~";
			}
		}
		//�Y���O�ŧi�ܼơA���N�O���s�ЭȩάO�����B��C
		else
		{
			bool isEqualSign = false;
			//�@�ˮھڵ���h����
			for (int i = 0; i < (int)str.length(); i++)
			{
				if (str[i] == '=')
					isEqualSign = true;
				else if (!isEqualSign)
					name += str[i];
				else
					expression += str[i];
			}
			//�p�G������A�N����歫�s���
			if (isEqualSign)
			{
				bool isFound = false;
				//�ھڦW�r���ܼ�
				auto itn = BigNumber::bigNumbers.find(name);
				if (itn != BigNumber::bigNumbers.end())
				{
					BigNumber num, de;
					num.numerator = BigDecimal(expression).numerator;
					de.numerator = BigDecimal(expression).getDenominator();
					num.Divide(de);
					BigNumber::bigNumbers[name] = num;
					result = "�w�ܧ��ܼ�" + name;
					isFound = true;
				}
				if (isFound == false)
				{
					auto itd = BigDecimal::bigDecimals.find(name);
					if (itd != BigDecimal::bigDecimals.end())
					{
						BigDecimal::bigDecimals[name] = BigDecimal(expression);
						result = "�w�ܧ��ܼ�" + name;
						isFound = true;
					}
				}
				//���G�S���
				if (isFound == false)
					result = "�䤣���ܼ�" + name;
			}
			//�H�W�����ŦX�A��������B��
			else
			{
				string post;
				post = Postorder(str);
				result = Computer(post).Print();
			}
		}
		UpdataScr(str,result);	//��X���G
	}
	return 0;
}