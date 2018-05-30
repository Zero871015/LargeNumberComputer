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

//Console美化
void UpdataScr(string in1,string in2)
{
	system("CLS");
	cout << "輸入：" << endl;
	cout  << endl << endl;
	cout << "------------------------" << endl;
	cout << "上次輸入：" << endl;
	cout << in1 << endl << endl;
	cout << "------------------------" << endl;
	cout << "運行結果：" << endl;
	cout << in2 << endl << endl;
	cout << "------------------------"  << endl;
	cout << "目前存在的變數：" << endl;
	cout << "整數：" << endl;
	for (auto& i:BigNumber::bigNumbers)
	{
		cout << i.first << " : " << i.second << endl;
	}
	cout << endl << "小數：" << endl;
	for (auto& i : BigDecimal::bigDecimals)
	{
		cout << i.first << " : " << i.second << endl;
	}

	//調整游標位置
	HANDLE hOut;
	COORD c;
	c.X = 0; c.Y = 1;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, c);
}

int main()
{
#ifdef DEBUG
	//直接賦予字串到整數
	BigNumber test1 = "10*3";
	UpdataScr("測試一", test1.Print());
	system("pause");
	//直接賦予字串到小數
	BigDecimal test2 = "10.1";
	UpdataScr("測試二", test2.Print());
	system("pause");
	//用cin,cout輸出
	system("CLS");
	cout << "輸入一個數字重設test1" << endl;
	cin >> test1;
	cout << test1 << endl;
	system("pause");
	//測試兩種型別可以放入同一容器中
	system("CLS");
	vector<BigNumber*> nums;
	nums.push_back(&test1);
	nums.push_back(&test2);
	for (const auto& num : nums)
		cout << num->Print() << endl;
	system("pause");
#endif // DEBUG

	string str;			//輸入字串
	string result;		//執行結果
	UpdataScr("","");	//初始化Console介面
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
			UpdataScr("", "輸入為空白");
			continue;
		}
		else if ((int)str.length() == 0)
		{
			UpdataScr("", "輸入為空白");
			continue;
		}
		else if (str == ".")
		{
			UpdataScr("", "輸入錯誤");
			continue;
		}
		string sub;
		string name;
		string expression;
		//避免存取到range之外，長度>14才找子字串
		if ((int)str.length() > 14)
			sub = str.substr(0, 12);
		else
			sub = "";
		//如果子字串符合指令，宣告整數變數
		if (sub == "Set Integer ")
		{
			bool isName = true;
			//根據等於切割變數名字和運算式
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
				//檢查是否存在相同名稱的小數變數
				auto it = BigDecimal::bigDecimals.find(name);
				if (it != BigDecimal::bigDecimals.end())
					BigDecimal::bigDecimals.erase(name);

				BigNumber::bigNumbers[name] = BigNumber(expression);
				result = "已設置變數" + name;
			}
			else
			{
				result = "變數名稱錯誤";
			}
		}
		//小數部分，同理
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
				//檢查是否存在相同名稱的整數變數
				auto it = BigNumber::bigNumbers.find(name);
				if (it != BigNumber::bigNumbers.end())
					BigNumber::bigNumbers.erase(name);
				BigDecimal::bigDecimals[name] = BigDecimal(expression);
				result = "已設置變數" + name;
			}
			else
			{
				result = "變數名稱錯誤";
			}
		}
		//若不是宣告變數，那就是重新覆值或是直接運算。
		else
		{
			bool isEqualSign = false;
			//一樣根據等於去切割
			for (int i = 0; i < (int)str.length(); i++)
			{
				if (str[i] == '=')
					isEqualSign = true;
				else if (!isEqualSign)
					name += str[i];
				else
					expression += str[i];
			}
			//如果有等於，代表執行重新賦值
			if (isEqualSign)
			{
				bool isFound = false;
				//根據名字找變數
				auto itn = BigNumber::bigNumbers.find(name);
				if (itn != BigNumber::bigNumbers.end())
				{
					BigNumber num, de;
					num.numerator = BigDecimal(expression).numerator;
					de.numerator = BigDecimal(expression).getDenominator();
					num.Divide(de);
					BigNumber::bigNumbers[name] = num;
					result = "已變更變數" + name;
					isFound = true;
				}
				if (isFound == false)
				{
					auto itd = BigDecimal::bigDecimals.find(name);
					if (itd != BigDecimal::bigDecimals.end())
					{
						BigDecimal::bigDecimals[name] = BigDecimal(expression);
						result = "已變更變數" + name;
						isFound = true;
					}
				}
				//結果沒找到
				if (isFound == false)
					result = "找不到變數" + name;
			}
			//以上都不符合，直接執行運算
			else
			{
				string post;
				post = Postorder(str);
				result = Computer(post).Print();
			}
		}
		UpdataScr(str,result);	//輸出結果
	}
	return 0;
}