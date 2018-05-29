#pragma once
#include "BigNumber.h"
class BigDecimal :
	public BigNumber
{
public:
	BigDecimal();
	~BigDecimal();
	BigDecimal(string str);
	BigDecimal(BigNumber n);

	friend ostream& operator<<(ostream&, const BigDecimal&);

	string Print();
	vector<int> getDenominator();
	void setDenominator(vector<int>);
	bool isDecimal();
	friend void RFTCD(BigDecimal &a, BigDecimal &b);
	void Scale(BigNumber n);
	void Add(BigNumber &n);
	void Subtract(BigNumber &n);
	void Multiply(BigNumber &n);
	void Divide(BigNumber &n);
	void Power(BigNumber &n);
	void Factorial();
	static map <string, BigDecimal> bigDecimals;
private:
	vector<int> denominator;
};

