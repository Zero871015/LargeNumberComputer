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

void BigNumber::Add(BigNumber n)
{
	if (this->isNagetive && !n.isNagetive)
	{
		this->isNagetive = false;
		swap(*this, n);
		this->Subtract(n);
	}
	else if (!this->isNagetive&&n.isNagetive)
	{
		n.isNagetive = false;
		this->Subtract(n);
	}
	else
	{
		if (this->numerator.size() < n.numerator.size())
		{
			swap(*this, n);
		}

		for (int i = 0; i < (int)n.numerator.size(); i++)
		{
			this->numerator[i] += n.numerator[i];
		}

		for (int i = 0; i < (int)this->numerator.size() - 1; i++)
		{
			if (this->numerator[i] > 9)
			{
				this->numerator[i] -= 10;
				this->numerator[i + 1]++;
			}
		}

		if (this->numerator[this->numerator.size() - 1] > 9)
		{
			this->numerator[this->numerator.size() - 1] -= 10;
			this->numerator.push_back(1);
		}
	}
}

void BigNumber::Subtract(BigNumber n)
{
	if (this->isNagetive && !n.isNagetive)
	{
		n.isNagetive = true;
		this->Add(n);
	}
	else if (!this->isNagetive&&n.isNagetive)
	{
		n.isNagetive = false;
		this->Add(n);
	}
	else
	{
		if (!ABigerB(*this, n))
		{
			swap(*this, n);
			this->isNagetive = !this->isNagetive;
		}
		for (int i = 0; i < (int)n.numerator.size(); i++)
		{
			this->numerator[i] -= n.numerator[i];
		}
		for (int i = 0; i < (int)this->numerator.size() - 1; i++)
		{
			if (this->numerator[i] < 0)
			{
				this->numerator[i] += 10;
				this->numerator[i + 1]--;
			}
		}
		for (int i = (int)this->numerator.size() - 1; i > 0; i--)
		{
			if (this->numerator[i] == 0)
				this->numerator.pop_back();
			else
				break;
		}
		
	}
}

void BigNumber::Multiply(BigNumber n)
{
	BigNumber temp;
	for (int i = 0; i < (int)this->numerator.size() + (int)n.numerator.size(); i++)
	{
		temp.numerator.push_back(0);
	}
	for (int i = 0; i < (int)this->numerator.size(); i++)
	{
		for (int j = 0; j < (int)n.numerator.size(); j++)
		{
			temp.numerator[i + j] += this->numerator[i] * n.numerator[j];
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
	temp.isNagetive = this->isNagetive^n.isNagetive;
	*this = temp;
}

void BigNumber::Divide(BigNumber n)
{
}

void BigNumber::Power(BigNumber n)
{
}

void BigNumber::factorial()
{
}

void BigNumber::Nagetive()
{
	this->isNagetive = !this->isNagetive;
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
					tmp.Subtract(B);
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