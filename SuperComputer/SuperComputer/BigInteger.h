#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInteger
{
public:
	BigInteger();
	BigInteger(string str);
	~BigInteger();

	friend BigInteger Add(BigInteger A, BigInteger B);
	friend BigInteger Subtract(BigInteger A, BigInteger B);
	friend BigInteger Multiply(BigInteger A, BigInteger B);
	friend BigInteger Divide(BigInteger A, BigInteger B);
	friend BigInteger Factorial(BigInteger A);
	friend BigInteger Power(BigInteger A, BigInteger B);

private:
	vector<int> molecularNumbers;
	bool isNegative;
};