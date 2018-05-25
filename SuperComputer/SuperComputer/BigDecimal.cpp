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

void BigDecimal::Add(BigDecimal n)
{
}

void BigDecimal::Subtract(BigDecimal n)
{
}

void BigDecimal::Multiply(BigDecimal n)
{
}

void BigDecimal::Divide(BigDecimal n)
{
}

void BigDecimal::Power(BigDecimal n)
{
}

void BigDecimal::factorial()
{
}

void RFTCD(BigDecimal & a, BigDecimal & b)
{
	BigNumber m, n;
	m.numerator = a.denominator;
	n.numerator = b.denominator;
	while (!(n.numerator.size() == 1 && n.numerator[0] == 0))
	{
	}
}
