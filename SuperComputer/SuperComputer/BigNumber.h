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
	friend BigNumber Add(BigNumber A, BigNumber B);
	friend BigNumber Subtract(BigNumber A, BigNumber B);
	friend BigNumber Multiply(BigNumber A, BigNumber B);
	friend BigNumber Divide(BigNumber A, BigNumber B);
	friend BigNumber Nagetive(BigNumber A);
private:
	bool isNagetive;
	vector<int> numerator;
};