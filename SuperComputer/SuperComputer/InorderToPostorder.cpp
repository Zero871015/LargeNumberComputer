//Name: zero871015
//Data: 04/19/2018
//Problem: Inorder to postorder.

#include "InorderToPostorder.h"

//�������Ǫ���J�B��l�u����
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

//�������Ǫ����|�B��l�u����
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

//�^�ǬO�_���B��l
bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '!')
		return true;
	else
		return false;
}

//�P�_��B��l�O�_�u��
bool ispriority(char input, char stack)
{
	if (operatorPriorityInInput(input) > operatorPriorityInStack(stack))
	{
		return true;
	}
	else
		return false;
}

//��������
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
	string stack;	//���|�B��l
	string ans;		//��Ǫ�ܪk
	bool isBlank = false;
	for (int i = 0; i < (int)inorder.length(); i++)
	{
		//�p�G�O�B��l...
		if (isOperator(inorder[i]))
		{
			isBlank = false;
			//�P�O�O���t���٬O�[��
			if (inorder[i] == '-'|| inorder[i]=='+')
			{
				if (i==0||(isOperator(inorder[i - 1])&&inorder[i-1]!=')'&&inorder[i - 1] != '!'))
				{
					if (inorder[i] == '-')
						stack.push_back('@');
					continue;
				}
			}
			//�Y�B��l���|���šA�hpush
			if (stack.size() == 0)
			{
				stack.push_back(inorder[i]);
			}
			//�Y�J���A���ݯS�O�B�z
			else if (inorder[i] == ')')
			{
				//����e�A���X�{�e�A����|��pop�X��
				while (!(stack.back() == '('))
				{
					ans += stack.back();
					ans += " ";
					stack.pop_back();
				}
				//�A�����ο�X�A��pop
				stack.pop_back();
			}
			//�Y�O�u���פj����|�����B��l�A�hpush�i�h
			else if (ispriority(inorder[i], stack.back()))
			{
				stack.push_back(inorder[i]);
			}
			//�Y�O�Ҥ��ŦX�A�h�N�B��lpop�X�@��A�����J�B��l�u���פj����|
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
		//�p�G�O�B�⤸�A������X
		else
		{
			if (isBlank)
				ans.pop_back();
			ans += inorder[i];
			ans += " ";
			isBlank = true;
		}
	}
	//���J�����A�N���|�����B��l��pop�X��
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