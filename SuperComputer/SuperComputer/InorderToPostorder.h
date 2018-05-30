//Name: Zero871015(B10615032)
//Data: 04/19/2018
//Problem: Inorder to postorder.

#pragma once
#include <iostream>
#include <string>
using namespace std;

int operatorPriorityInInput(char c);

int operatorPriorityInStack(char c);

bool isOperator(char c);

bool ispriority(char input, char stack);

string Postorder(string inorder);