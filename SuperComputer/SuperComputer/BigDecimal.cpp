// Name: B10615032,B10615020,B10615030
// Date: 05/17/2018
// Last Update: 05/31/2018
// Problem statement: Big decimal part.

#include "BigDecimal.h"
#include "InorderToPostorder.h"
#include "Computer.h"
#include <sstream>

BigDecimal::BigDecimal()
{
	this->isNagetive = false;
	this->error = 0;
}

BigDecimal::~BigDecimal()
{
}

BigDecimal::BigDecimal(string str)
{
	this->error = 0;
	bool isDone = true;
	for (int i = 0; i < (int)str.length(); i++)
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
		{
			isDone = false;
			break;
		}
	}
	//輸入是數字
	if (isDone)
	{
		reverse(str.begin(), str.end());
		bool isPoint = true;
		for (int i = 0; i < (int)str.length(); i++)
		{
			if (str[i] == '.')
			{
				this->denominator.push_back(0);
				this->denominator[i] = 1;
				isPoint = false;
			}
			else
			{
				if (isPoint)
				{
					this->denominator.push_back(0);
					this->numerator.push_back(str[i] - '0');
				}
				else
				{
					this->numerator.push_back(str[i] - '0');
				}
			}
		}
		for (int i = (int)this->denominator.size() - 1; i > 0; i--)
		{
			if (this->denominator[i] == 0)
			{
				this->denominator.pop_back();
			}
			else
				break;
		}
		for (int i = (int)this->numerator.size() - 1; i >0; i--)
		{
			if (this->numerator[i] == 0)
				this->numerator.pop_back();
			else
				break;
		}
		if (this->denominator.size() == 1 && this->denominator[0] == 0)
			this->denominator[0] = 1;
		this->isNagetive = false;
	}
	//輸入是運算式
	else
	{
		*this = Computer(Postorder(str));
		this->setDenominator(Computer(Postorder(str)).getDenominator());
	}
}

BigDecimal::BigDecimal(BigNumber n)
{
	this->numerator = n.numerator;
	this->denominator.push_back(1);
	this->isNagetive = n.isNagetive;
	this->error = n.error;
}

BigDecimal::BigDecimal(const char * s)
{
	string temp = s;
	*this = BigDecimal(temp);
}

string BigDecimal::Print()
{
	string ans;

	if (this->error == 1)
	{
		return ans = "出現不存在的變數";
	}
	else if (this->error == 2)
	{
		return ans = "運算式錯誤，請重新檢查";
	}
	else if (this->error == 3)
	{
		return ans = "嘗試除零";
	}

	if (this->numerator.size() == 1 && this->numerator[0] == 0)
	{
		return "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	}
	this->FractionReduction();

	
	stringstream ss;
	if (this->isNagetive)
		ans += '-';

	////////////
	BigNumber num, de;
	num.numerator = this->numerator;
	de.numerator = this->denominator;
	int j;
	BigNumber count, tmp;
	BigNumber hundred = BigDecimal("10^100");
	num.Multiply(hundred);

	for (int i = 0; i < (int)num.numerator.size(); i++)
	{
		j = 0;
		tmp.numerator.insert(tmp.numerator.begin(), num.numerator[(int)num.numerator.size() - 1 - i]);
		for (int k = (int)tmp.numerator.size() - 1; k > 0; k--)
		{
			if (tmp.numerator[k] == 0)
				tmp.numerator.pop_back();
			else
				break;
		}
		if (ABigerB(tmp, de))
		{
			while (ABigerB(tmp, de))
			{
				tmp.Subtract(de);
				j++;
			}
		}
		count.numerator.insert(count.numerator.begin(), j);
	}
	for (int i = (int)count.numerator.size() - 1; i > 100; i--)
	{
		if (count.numerator[i] == 0)
		{
			count.numerator.pop_back();
		}
		else
			break;
	}
	for (int i = (int)count.numerator.size() - 1; i >= 0; i--)
	{
		if (i == 99)
			ss << '.';
		ss << count.numerator[i];
	}
	ans += ss.str();
	ss.str("");

	////////////
	return ans;
}

vector<int> BigDecimal::getDenominator()
{
	return this->denominator;
}


void BigDecimal::setDenominator(vector<int> d)
{
	this->denominator = d;
}

bool BigDecimal::isDecimal()
{
	return true;
}

bool BigDecimal::isDecimal() const
{
	return true;
}

void BigDecimal::FractionReduction()
{
	BigNumber n,m,gcd;
	n.numerator = this->numerator;
	m.numerator = this->denominator;
	while (!AEqualB(n, BigNumber("0")))
	{
		if (!ABigerB(n, m))
		{
			m.Remainder(n);
		}
		else
			n.Remainder(m);
		if (AEqualB(m, BigNumber("0")))
			swap(n, m);
	}
	gcd = m;
	n.numerator = this->numerator;
	m.numerator = this->denominator;
	n.Divide(gcd);
	m.Divide(gcd);
	this->numerator = n.numerator;
	this->denominator = m.numerator;
}

void BigDecimal::Scale(BigNumber n)
{
	BigDecimal temp;
	for (int i = 0; i < (int)this->numerator.size(); i++)
	{
		for (int j = 0; j < (int)n.numerator.size(); j++)
		{
			temp.numerator.push_back(0);
			temp.numerator[i + j] += this->numerator[i] * n.numerator[j];
		}
	}
	for (int i = 0; i < (int)this->denominator.size(); i++)
	{
		for (int j = 0; j < (int)n.numerator.size(); j++)
		{
			temp.denominator.push_back(0);
			temp.denominator[i + j] += this->denominator[i] * n.numerator[j];
		}
	}

	for (int i = 0; i < (int)this->numerator.size()-1; i++)
	{
		while (this->numerator[i] > 9)
		{
			this->numerator[i] -= 10;
			this->numerator[i + 1]++;
		}
	}
	for (int i = 0; i < (int)this->denominator.size() - 1; i++)
	{
		while (this->denominator[i] > 9)
		{
			this->denominator[i] -= 10;
			this->denominator[i + 1]++;
		}
	}

	for (int i = (int)temp.numerator.size()-1; i>0; i--)
	{
		if (temp.numerator[i] == 0)
			temp.numerator.pop_back();
		else
			break;
	}
	for (int i = (int)temp.denominator.size()-1; i > 0; i--)
	{
		if (temp.denominator[i] == 0)
			temp.denominator.pop_back();
		else
			break;
	}
	temp.isNagetive = this->isNagetive;
	*this = temp;
}

void BigDecimal::Add(BigNumber &n)
{
	BigDecimal temp(n);
	temp.denominator = n.getDenominator();
	RFTCD(*this, temp);
	BigNumber a1, a2;
	a1.numerator = this->numerator;
	a1.isNagetive = this->isNagetive;
	a2.numerator = temp.numerator;
	a2.isNagetive = temp.isNagetive;
	a1.Add(a2);
	temp = BigDecimal(a1);
	temp.denominator = this->denominator;
	*this = temp;
}

void BigDecimal::Subtract(BigNumber &n)
{
	BigDecimal temp(n);
	temp.denominator = n.getDenominator();
	RFTCD(*this, temp);
	BigNumber a1, a2;
	a1.numerator = this->numerator;
	a1.isNagetive = this->isNagetive;
	a2.numerator = temp.numerator;
	a2.isNagetive = temp.isNagetive;
	a1.Subtract(a2);
	temp = BigDecimal(a1);
	temp.denominator = this->denominator;
	*this = temp;
	
}

void BigDecimal::Multiply(BigNumber &n)
{
	BigNumber buffer1,buffer2;
	BigDecimal temp(n),ans;
	temp.denominator = n.getDenominator();

	buffer1.numerator = this->numerator;
	buffer2.numerator = temp.numerator;
	buffer1.Multiply(buffer2);
	ans.numerator = buffer1.numerator;

	buffer1.numerator = this->denominator;
	buffer2.numerator = temp.denominator;
	buffer1.Multiply(buffer2);
	ans.denominator = buffer1.numerator;

	ans.isNagetive = this->isNagetive^n.isNagetive;
	*this = ans;
}

void BigDecimal::Divide(BigNumber &n)
{
	BigDecimal temp(n);
	temp.denominator = temp.numerator;
	temp.numerator = n.getDenominator();
	this->Multiply(temp);
}

BigDecimal Sqrts(BigNumber n)
{
	if ((int)n.numerator.size() % 2 == 1)
		n.numerator.push_back(0);
	BigNumber temp, temp2("0");
	BigDecimal ans;
	for (int i = (int)n.numerator.size() - 1; i >= 1; i -= 2)
	{
		temp.numerator.insert(temp.numerator.begin(), n.numerator[i]);
		temp.numerator.insert(temp.numerator.begin(), n.numerator[i - 1]);
		BigNumber s("0"), temp3;
		BigNumber one("1");
		for (int k = (int)temp.numerator.size() - 1; k > 0; k--)
		{
			if (temp.numerator[k] == 0)
				temp.numerator.pop_back();
			else
				break;
		}
		temp3 = temp2;
		temp3.numerator.insert(temp3.numerator.begin(), s.numerator[0]);
		temp3.Multiply(s);
		while (ABigerB(temp3, temp) == false)
		{
			s.Add(one);
			temp3 = temp2;
			temp3.numerator.insert(temp3.numerator.begin(), s.numerator[0]);
			temp3.Multiply(s);
		}
		if (AEqualB(temp3, temp) == false)
		{
			temp3.Divide(s);
			temp3.numerator[0] -= 1;
			s.Subtract(one);
			temp3.Multiply(s);
		}
		temp.Subtract(temp3);
		if (AEqualB(s, BigNumber("0")) == false)
			temp3.Divide(s);
		temp3.Add(s);
		temp2 = temp3;
		ans.numerator.insert(ans.numerator.begin(), s.numerator[0]);
	}
	for (int i = 0; i < 100; i++)
	{
		temp.numerator.insert(temp.numerator.begin(), 0);
		temp.numerator.insert(temp.numerator.begin(), 0);
		BigNumber s("0"), temp3("0");
		BigNumber one("1");
		for (int k = (int)temp.numerator.size() - 1; k > 0; k--)
		{
			if (temp.numerator[k] == 0)
				temp.numerator.pop_back();
			else
				break;
		}
		temp3 = temp2;
		temp3.numerator.insert(temp3.numerator.begin(), 0);
		for (int k = (int)temp3.numerator.size() - 1; k > 0; k--)
		{
			if (temp3.numerator[k] == 0)
				temp3.numerator.pop_back();
			else
				break;
		}
		temp3.Multiply(s);
		while (ABigerB(temp3, temp) == false)
		{
			s.Add(one);
			temp3 = temp2;
			temp3.numerator.insert(temp3.numerator.begin(), s.numerator[0]);
			temp3.Multiply(s);
		}
		if (AEqualB(temp3, temp) == false)
		{
			temp3 = temp2;
			s.Subtract(one);
			temp3.numerator.insert(temp3.numerator.begin(), s.numerator[0]);
			temp3.Multiply(s);
		}
		temp.Subtract(temp3);
		if (AEqualB(s, BigNumber("0")) == false)
			temp3.Divide(s);
		temp3.Add(s);
		if (AEqualB(temp3, BigNumber("0")) == false)
			temp2 = temp3;
		else
			temp2.numerator.insert(temp2.numerator.begin(), 0);
		ans.numerator.insert(ans.numerator.begin(), s.numerator[0]);
		ans.denominator.push_back(0);
	}
	ans.denominator.push_back(1);
	return ans;
}

void BigDecimal::Power(BigNumber &n)
{
	this->FractionReduction();
	BigNumber up, down, one("1");;
	BigDecimal temp(n);
	temp.denominator = n.getDenominator();
	BigDecimal base = *this;
	up.numerator = temp.numerator;
	down.numerator = temp.denominator;
	up.Divide(down);

	if (AEqualB(up, BigNumber("0")) == true)
	{
		BigDecimal a(one);
		*this = a;
	}
	while (ABigerB(up, BigNumber("2")) == true)
	{
		this->Multiply(base);
		up.Subtract(one);
	}
	up.numerator = temp.numerator;
	up.Remainder(down);
	if (AEqualB(up, BigNumber("0")) == false)
	{
		BigDecimal integer, decimal;
		up.numerator = base.numerator;
		down.numerator = base.denominator;
		integer = Sqrts(up);
		this->Multiply(integer);
		decimal = Sqrts(down);
		this->Divide(decimal);
	}
	if (n.isNagetive == true)
	{
		BigDecimal inverse("1");
		inverse.Divide(*this);
		*this = inverse;
	}
	this->FractionReduction();
}

void BigDecimal::Factorial()
{
	if (this->isNagetive == true)
	{
		this->error = 2;
		return;
	}
	BigNumber up, down;
	up.numerator = this->numerator;
	down.numerator = this->denominator;
	up.Remainder(down);

	if (AEqualB(up, BigNumber("0")) == true)
	{
		up.numerator = this->numerator;
		up.Divide(down);
		up.Factorial();
		BigDecimal ans(up);
		*this = ans;
	}
	else
	{
		this->error = 2;
	}
}

ostream & operator<<(ostream & os, const BigDecimal d)
{
	if (d.isNagetive)
		os << '-';
	for (int i = (int)d.numerator.size() - 1; i >= 0; i--)
	{
		os << d.numerator[i];
	}
	os << '/';
	for (int i = (int)d.denominator.size() - 1; i >= 0; i--)
	{
		os << d.denominator[i];
	}
	return os;
}

void RFTCD(BigDecimal & a, BigDecimal & b)
{
	BigNumber m , n;
	m.numerator = a.denominator;
	n.numerator = b.denominator;
	BigNumber GCD, LCM;
	BigNumber ta, tb;
	while (!AEqualB(n, BigNumber("0")))
	{
		if (!ABigerB(n, m))
		{
			m.Remainder(n);
		}
		else
			n.Remainder(m);
		if (AEqualB(m, BigNumber("0")))
			swap(n, m);
	}
	GCD = m;
	m.numerator = a.denominator;
	n.numerator = b.denominator;
	m.Multiply(n);
	m.Divide(GCD);
	LCM = m;
	ta = LCM; tb = LCM;
	m.numerator = a.denominator;
	n.numerator = b.denominator;
	ta.Divide(m);
	tb.Divide(n);
	a.Scale(ta);
	b.Scale(tb);

}

map <string, BigDecimal> BigDecimal::bigDecimals = {};