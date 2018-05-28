#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigNumber
{
public:
	BigNumber();
	~BigNumber();
	BigNumber(string str);
	virtual void Print();

	friend bool ABigerB(BigNumber A, BigNumber B);
	friend bool AEqualB(BigNumber A, BigNumber B);
	virtual vector<int> getDenominator();
	virtual bool isDecimal();
	virtual void Add(BigNumber &n);
	virtual void Subtract(BigNumber &n);
	virtual void Multiply(BigNumber &n);
	virtual void Divide(BigNumber &n);
	virtual void Power(BigNumber &n);
	virtual void factorial();
	virtual void Nagetive();
	vector<int> numerator;
	bool isNagetive;
};