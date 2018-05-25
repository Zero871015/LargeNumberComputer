#pragma once
#include "BigNumber.h"
class BigDecimal :
	public BigNumber
{
public:
	BigDecimal();
	~BigDecimal();
	BigDecimal(string str);

	friend void RFTCD(BigDecimal &a, BigDecimal &b);
	void Add(BigDecimal n);
	void Subtract(BigDecimal n);
	void Multiply(BigDecimal n);
	void Divide(BigDecimal n);
	void Power(BigDecimal n);
	void factorial();
private:
	vector<int> denominator;
};

