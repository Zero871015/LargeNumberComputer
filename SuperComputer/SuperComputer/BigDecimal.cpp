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
	bool isPoint = false;
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (str[i] == '.')
		{
			isPoint = true;
		}
		else
		{
			if (isPoint == false)
			{
				this->denominator.push_back(str[i] - '0');
				this->numerator.push_back(0);
			}
			else
			{
				this->numerator.push_back(str[i] - '0');
			}
		}
	}
	this->isNagetive = false;
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

	for (int i = (int)temp.numerator.size(); i>0; i--)
	{
		if (temp.numerator[i] == 0)
			temp.numerator.pop_back();
		else
			break;
	}
	for (int i = (int)temp.denominator.size(); i > 0; i--)
	{
		if (temp.denominator[i] == 0)
			temp.denominator.pop_back();
		else
			break;
	}

	*this = temp;
}


void BigDecimal::Add(BigNumber &n)
{
	if (n.isDecimal())
	{
		//Ãa£{
		//RFTCD(*this, n);
	}
	else
		cout << "testN";
}

void BigDecimal::Subtract(BigNumber &n)
{
}

void BigDecimal::Multiply(BigNumber &n)
{
}

void BigDecimal::Divide(BigNumber &n)
{
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
		if (ABigerB(m, n))
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
