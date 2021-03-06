// Name: B10615032,B10615020,B10615030
// Date: 05/17/2018
// Last Update: 05/31/2018
// Problem statement: Big integer part.

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class BigNumber
{
public:
	BigNumber();
	~BigNumber();
	BigNumber(string str);
	BigNumber(const char* s);
	virtual string Print();

	friend istream& operator>>(istream&, BigNumber);
	friend ostream& operator<<(ostream&, const BigNumber);

	friend bool ABigerB(BigNumber A, BigNumber B);
	friend bool AEqualB(BigNumber A, BigNumber B);
	virtual vector<int> getDenominator();
	virtual void setDenominator(vector<int>);
	virtual bool isDecimal();
	virtual bool isDecimal()const;
	virtual void Add(BigNumber &n);
	virtual void Subtract(BigNumber &n);
	virtual void Multiply(BigNumber &n);
	virtual void Divide(BigNumber &n);
	void Remainder(BigNumber &n);
	virtual void Power(BigNumber &n);
	virtual void Factorial();
	virtual void Nagetive();


	vector<int> numerator;
	bool isNagetive;
	static map <string, BigNumber> bigNumbers;
	int error;
};