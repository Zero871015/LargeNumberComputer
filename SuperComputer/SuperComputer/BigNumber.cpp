#include "BigNumber.h"
#include "Computer.h"
#include "InorderToPostorder.h"
#include <algorithm>
#include <sstream>

BigNumber::BigNumber()
{
	this->isNagetive = false;
	this->error = 0;
}

BigNumber::~BigNumber()
{
}

BigNumber::BigNumber(string str)
{
	bool isDone = true;
	this->error = 0;
	for (int i = 0; i < (int)str.length(); i++)
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
		{
			isDone = false;
			break;
		}
	}
	//輸入的是數字
	if(isDone)
	{ 
		reverse(str.begin(), str.end());
		for (int i = 0; i < (int)str.length(); i++)
		{
			if (str[i] >= '0'&&str[i] <= '9')
				this->numerator.push_back(str[i] - '0');
			else
				this->numerator.clear();
		}
		for (int i = (int)this->numerator.size()-1; i > 0; i--)
		{
			if (this->numerator[i] == 0)
				this->numerator.pop_back();
			else
				break;
		}
		this->isNagetive = false;
	}
	//輸入的是運算式
	else
	{
		/*BigNumber num, de;
		num.numerator = Computer(Postorder(str)).numerator;
		de.numerator = Computer(Postorder(str)).getDenominator();
		num.Divide(de);
		*this = num;*/
		*this = Computer(Postorder(str));
	}
}

string BigNumber::Print()
{
	string ans;
	if (this->error == 1)
	{
		ans = "出現不存在的變數";
	}
	else if (this->error == 2)
	{
		ans = "運算式錯誤，請重新檢查";
	}
	else
	{
		stringstream ss;
		if (this->isNagetive)
			ans += "-";
		for (int i = (int)this->numerator.size() - 1; i >= 0; i--)
		{
			ss << this->numerator[i];
		}
		ans += ss.str();
	}
	return ans;
}

vector<int> BigNumber::getDenominator()
{
	vector<int> temp;
	temp.push_back(1);
	return temp;
}

void BigNumber::setDenominator(vector<int> d)
{
}

bool BigNumber::isDecimal()
{
	return false;
}

void BigNumber::Add(BigNumber &n)
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

void BigNumber::Subtract(BigNumber &n)
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

void BigNumber::Multiply(BigNumber &n)
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
	if (this->numerator.size() == 1 && this->numerator[0] == 0)
		this->isNagetive = false;
}

void BigNumber::Divide(BigNumber &n)
{
	if (ABigerB(*this, n))
	{
		int i, j;
		bool negative = false;
		BigNumber count, tmp;

		if (this->isNagetive != n.isNagetive)
			negative = true;
		this->isNagetive = false;
		n.isNagetive = false;

		for (i = 0; i < (int)this->numerator.size(); i++)
		{
			j = 0;
			tmp.numerator.insert(tmp.numerator.begin(), this->numerator[(int)this->numerator.size() - 1 - i]);
			for (int k = (int)tmp.numerator.size() - 1; k > 0; k--)
			{
				if (tmp.numerator[k] == 0)
					tmp.numerator.pop_back();
				else
					break;
			}
			if (ABigerB(tmp, n))
			{
				while (ABigerB(tmp, n))
				{
					tmp.Subtract(n);
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
		*this = count;
		if (negative)
			this->isNagetive = true;
	}
	else
	{
		*this = BigNumber("0");
	}
	if (this->numerator.size() == 1 && this->numerator[0] == 0)
		this->isNagetive = false;
}

void BigNumber::Remainder(BigNumber & n)
{
	int i, j;
	BigNumber tmp;

	for (i = 0; i < (int)this->numerator.size(); i++)
	{
		j = 0;
		tmp.numerator.insert(tmp.numerator.begin(), this->numerator[(int)this->numerator.size() - 1 - i]);
		for (int k = (int)tmp.numerator.size() - 1; k > 0; k--)
		{
			if (tmp.numerator[k] == 0)
				tmp.numerator.pop_back();
			else
				break;
		}
		if (ABigerB(tmp, n))
		{
			while (ABigerB(tmp, n))
			{
				tmp.Subtract(n);
				j++;
			}
		}
	}
	*this = tmp;
}

void BigNumber::Power(BigNumber &n)
{
	BigNumber zero("0"), one("1"), two("2");
	if (AEqualB(n, zero))
	{
		*this = one;
	}
	else
	{
		BigNumber base = *this;
		if (n.isNagetive == false)
		{
			while (ABigerB(n, two))
			{
				this->Multiply(base);
				n.Subtract(one);
			}
		}
		else
		{
			*this = zero;
		}
	}
}

void BigNumber::Factorial()
{
	BigNumber zero("0"), one("1"), factor("1");
	if (AEqualB(*this, zero) || AEqualB(*this, one))
	{
		*this = one;
	}
	else
	{
		while (ABigerB(*this, one))
		{
			factor.Multiply(*this);
			this->Subtract(one);
		}
		*this = factor;
	}
}

void BigNumber::Nagetive()
{
	this->isNagetive = !this->isNagetive;
	if (this->numerator.size() == 1 && this->numerator[0] == 0)
		this->isNagetive = false;
}

ostream & operator<<(ostream & os, const BigNumber & n)
{
	if (n.isNagetive)
		os << '-';
	for (int i = (int)n.numerator.size() - 1; i >= 0; i--)
	{
		os << n.numerator[i];
	}
	return os;
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

bool AEqualB(BigNumber A, BigNumber B)
{
	if (A.numerator.size() == B.numerator.size())
	{
		for (int i = (int)A.numerator.size() - 1; i >= 0; i--)
		{
			if (A.numerator[i] != B.numerator[i])
				return false;
		}
		return true;
	}
	return false;
}

map<string, BigNumber> BigNumber::bigNumbers = {};