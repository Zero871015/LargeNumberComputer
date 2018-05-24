#include "BigNumber.h"
#include <algorithm>

BigNumber::BigNumber()
{
	//this->numerator.push_back(0); //預設為空
	this->isNagetive = false;
}

BigNumber::~BigNumber()
{
}

BigNumber::BigNumber(string str)
{
	reverse(str.begin(), str.end());
	for (int i = 0; i < (int)str.length(); i++)
	{
		this->numerator.push_back(str[i] - '0');
	}
	this->isNagetive = false;
}

void BigNumber::Print()
{
	if (this->isNagetive)
		cout << '-';
	for (int i = (int)this->numerator.size() - 1; i >= 0; i--)
	{
		cout << this->numerator[i];
	}
	cout << endl;
}

bool ABigerB(BigNumber A, BigNumber B)
{
	if (A.numerator.size() > B.numerator.size())
		return true;
	else if (A.numerator.size() == B.numerator.size())
	{
		for (int i = (int)A.numerator.size() - 1; i >= 0; i--)
		{
			if (A.numerator[i] > B.numerator[i])
				return true;
			else if (A.numerator[i] < B.numerator[i])
				return false;
		}
		return true;
	}
	return false;
}

BigNumber Add(BigNumber A, BigNumber B)
{
	if (A.isNagetive && !B.isNagetive)
	{
		A.isNagetive = false;
		return Subtract(B, A);
	}
	else if (!A.isNagetive&&B.isNagetive)
	{
		B.isNagetive = false;
		return Subtract(A, B);
	}
	else
	{
		if (A.numerator.size() >= B.numerator.size())
		{
			for (int i = 0; i < (int)B.numerator.size(); i++)
			{
				A.numerator[i] += B.numerator[i];
			}

			for (int i = 0; i < (int)A.numerator.size() - 1; i++)
			{
				if (A.numerator[i] > 9)
				{
					A.numerator[i] -= 10;
					A.numerator[i + 1]++;
				}
			}
			if (A.numerator[A.numerator.size() - 1] > 9)
			{
				A.numerator[A.numerator.size() - 1] -= 10;
				A.numerator.push_back(1);
			}
			return A;
		}
		else
		{
			return Add(B, A);
		}
	}
}

BigNumber Subtract(BigNumber A, BigNumber B)
{
	if (A.isNagetive && !B.isNagetive)
	{
		B.isNagetive = true;
		return Add(A, B);
	}
	else if (!A.isNagetive&&B.isNagetive)
	{
		B.isNagetive = false;
		return Add(A, B);
	}
	else if (A.isNagetive&&B.isNagetive)
	{
		BigNumber temp;
		A.isNagetive = false;
		B.isNagetive = false;
		temp = Subtract(B, A);
		temp.isNagetive = !temp.isNagetive;
		return temp;
	}
	if (ABigerB(A, B))
	{
		for (int i = 0; i < (int)B.numerator.size(); i++)
		{
			A.numerator[i] -= B.numerator[i];
		}
		for (int i = 0; i < (int)A.numerator.size() - 1; i++)
		{
			if (A.numerator[i] < 0)
			{
				A.numerator[i] += 10;
				A.numerator[i + 1]--;
			}
		}
		for (int i = (int)A.numerator.size() - 1; i > 0; i--)
		{
			if (A.numerator[i] == 0)
				A.numerator.pop_back();
			else
				break;
		}
		return A;
	}
	else
	{
		for (int i = 0; i < (int)A.numerator.size(); i++)
		{
			B.numerator[i] -= A.numerator[i];
		}
		for (int i = 0; i < (int)B.numerator.size(); i++)
		{
			if (B.numerator[i] < 0)
			{
				B.numerator[i] += 10;
				B.numerator[i + 1]--;
			}
		}
		for (int i = (int)B.numerator.size() - 1; i > 0; i--)
		{
			if (B.numerator[i] == 0)
				B.numerator.pop_back();
			else
				break;
		}
		B.isNagetive = true;
		return B;
	}
}

BigNumber Multiply(BigNumber A, BigNumber B)
{
	BigNumber temp;
	for (int i = 0; i < (int)A.numerator.size() + (int)B.numerator.size(); i++)
	{
		temp.numerator.push_back(0);
	}
	for (int i = 0; i < (int)A.numerator.size(); i++)
	{
		for (int j = 0; j < (int)B.numerator.size(); j++)
		{
			temp.numerator[i + j] += A.numerator[i] * B.numerator[j];
		}
	}
	for (int i = 0; i < (int)temp.numerator.size(); i++)
	{
		while (temp.numerator[i] > 9)
		{
			temp.numerator[i] -= 10;
			temp.numerator[i + 1]++;
		}
	}
	for (int i = (int)temp.numerator.size() - 1; i > 0; i--)
	{
		if (temp.numerator[i] == 0)
			temp.numerator.pop_back();
		else
			break;
	}
	temp.isNagetive = A.isNagetive^B.isNagetive;


	return temp;
}

BigNumber Divide(BigNumber A, BigNumber B)
{
	int i, j;
	if (ABigerB(A, B))
	{
		BigNumber count, tmp;
		for (i = 0; i < (int)A.numerator.size(); i++)
		{
			j = 0;
			tmp.numerator.insert(tmp.numerator.begin(), A.numerator[(int)A.numerator.size() - 1 - i]);
			for (int k = (int)tmp.numerator.size() - 1; k > 0; k--)
			{
				if (tmp.numerator[k] == 0)
					tmp.numerator.pop_back();
				else
					break;
			}
			if (ABigerB(tmp, B))
			{
				while (ABigerB(tmp, B))
				{
					tmp = Subtract(tmp, B);
					j++;
				}
			}
			count.numerator.insert(count.numerator.begin(), j);
		}
		for (i = (int)count.numerator.size() - 1; i > 0; i--)
		{
			if (count.numerator[i] == 0)
				count.numerator.pop_back();
			else
				break;
		}
		count.isNagetive = A.isNagetive ^ B.isNagetive;
		return count;
	}
	else
	{
		return BigNumber("0");
	}
}

BigNumber Nagetive(BigNumber A)
{
	A.isNagetive = !A.isNagetive;
	return A;
}