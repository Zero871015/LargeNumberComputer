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
	void Print();

	friend bool ABigerB(BigNumber A, BigNumber B);
	virtual void Add(BigNumber n);
	virtual void Subtract(BigNumber n);
	virtual void Multiply(BigNumber n);
	friend BigNumber Divide(BigNumber A, BigNumber B);
	virtual void Divide(BigNumber n);
	virtual void Power(BigNumber n);
	virtual void factorial();
	virtual void Nagetive();
	vector<int> numerator;
protected:
	bool isNagetive;
};