// Name: B10615032,B10615020,B10615030
// Date: 05/17/2018
// Last Update: 05/31/2018
// Problem statement: Big decimal part.

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
	BigDecimal(const char* s);


	friend ostream& operator<<(ostream&, const BigDecimal);

	string Print();
	vector<int> getDenominator();
	void setDenominator(vector<int>);
	bool isDecimal();
	bool isDecimal()const;
	friend void RFTCD(BigDecimal &a, BigDecimal &b);
	void FractionReduction();
	void Scale(BigNumber n);
	void Add(BigNumber &n);
	void Subtract(BigNumber &n);
	void Multiply(BigNumber &n);
	void Divide(BigNumber &n);
	void Power(BigNumber &n);
	void Factorial();
	static map <string, BigDecimal> bigDecimals;
	friend BigDecimal Sqrts(BigNumber);
private:
	vector<int> denominator;
};

