//Name: zero871015
//Data: 04/19/2018
//Problem: Inorder to postorder.

#include "InorderToPostorder.h"

//中序轉後序的輸入運算子優先度
int operatorPriorityInInput(char c)
{
	if (c == '+' || c == '-')return 1;
	else if (c == '*' || c == '/')return 2;
	else if (c == '@')return 3;
	else if (c == '^')return 4;
	else if (c == '!')return 5;
	else if (c == ')')return 0;
	else if (c == '(')return 6;
	else return -1;
}

//中序轉後序的堆疊運算子優先度
int operatorPriorityInStack(char c)
{
	if (c == '+' || c == '-')return 1;
	else if (c == '*' || c == '/')return 2;
	else if (c == '@')return 3;
	else if (c == '^')return 4;
	else if (c == '!')return 5;
	else if (c == '(')return 0;
	else return -1;
}

//回傳是否為運算子
bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '!')
		return true;
	else
		return false;
}

//判斷兩運算子是否優先
bool ispriority(char input, char stack)
{
	if (operatorPriorityInInput(input) > operatorPriorityInStack(stack))
	{
		return true;
	}
	else
		return false;
}

//中序轉後序
string Postorder(string inorder)
{
	for (int i = 0; i < (int)inorder.length(); i++)
	{
		if (inorder[i] == ' ')
		{
			inorder.erase(i,1);
			i--;
		}
	}
	string stack;	//堆疊運算子
	string ans;		//後序表示法
	bool isBlank = false;
	for (int i = 0; i < (int)inorder.length(); i++)
	{
		//如果是運算子...
		if (isOperator(inorder[i]))
		{
			isBlank = false;
			//判別是正負號還是加減
			if (inorder[i] == '-'|| inorder[i]=='+')
			{
				if (i==0||(isOperator(inorder[i - 1])&&inorder[i-1]!=')'&&inorder[i - 1] != '!'))
				{
					if (inorder[i] == '-')
						stack.push_back('@');
					continue;
				}
			}
			//若運算子堆疊為空，則push
			if (stack.size() == 0)
			{
				stack.push_back(inorder[i]);
			}
			//若遇到後括號需特別處理
			else if (inorder[i] == ')')
			{
				//直到前括號出現前，把堆疊都pop出來
				while (!(stack.back() == '('))
				{
					ans += stack.back();
					ans += " ";
					stack.pop_back();
				}
				//括號不用輸出，純pop
				stack.pop_back();
			}
			//若是優先度大於堆疊中的運算子，則push進去
			else if (ispriority(inorder[i], stack.back()))
			{
				stack.push_back(inorder[i]);
			}
			//若是皆不符合，則將運算子pop出一位，直到輸入運算子優先度大於堆疊
			else
			{
				if (stack.back() != '('&&stack.back() != ')')
				{
					ans += stack.back();
					ans += " ";
				}
				stack.pop_back();
				i--;
			}
		}
		//如果是運算元，直接輸出
		else
		{
			if (isBlank)
				ans.pop_back();
			ans += inorder[i];
			ans += " ";
			isBlank = true;
		}
	}
	//當輸入結束，將堆疊中的運算子全pop出來
	for (; !stack.empty();)
	{
		if (stack.back() != '('&&stack.back() != ')')
		{
			ans += stack.back();
			ans += " ";
		}
		stack.pop_back();
	}
	if (ans[(int)ans.length() - 1] != ' ')
		ans += ' ';
	return ans;
}