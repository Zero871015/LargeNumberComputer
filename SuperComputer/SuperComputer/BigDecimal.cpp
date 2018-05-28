#include "BigDecimal.h"
BigDecimal::BigDecimal()
{
	this->isNagetive = false;
}

BigDecimal::~BigDecimal()
{
}

BigDecimal::BigDecimal(string str)
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
	this->isNagetive = false;
}

BigDecimal::BigDecimal(BigNumber n)
{
	this->numerator = n.numerator;
	this->denominator.push_back(1);
	this->isNagetive = n.isNagetive;
}

void BigDecimal::Print()
{
	if (this->isNagetive)
		cout << '-';
	for (int i = (int)this->numerator.size()-1; i >=0; i--)
	{
		cout << this->numerator[i];
	}
	cout << '/';
	for (int i = (int)this->denominator.size()-1; i >=0 ; i--)
	{
		cout << this->denominator[i];
	}
	cout << endl;
}

vector<int> BigDecimal::getDenominator()
{
	return this->denominator;
}

bool BigDecimal::isDecimal()
{
	return true;
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

void BigDecimal::Power(BigNumber &n)
{
}

void BigDecimal::factorial()
{
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
			m.Subtract(n);
		}
		else
			n.Subtract(m);
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
