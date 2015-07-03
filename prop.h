#pragma once
#include<set>
#include<vector>
#include<bitset>
#include "var.h"
using namespace std;

class prop{
public:
	prop();
	prop(const bool &val);
	prop(bool *val);
	prop(var *val);
	prop(const var &p, const char op, const var &q);
	prop(prop *p, const char op, prop *q);
	void tt();
	bool get_value();
	string to_string();
	~prop();

	bool value;
	var* val_ptr;

	char operation;
	prop* val1;
	prop* val2;
	prop* parent;

private:
	//bool value;

	/*
		prop must have two variables and an operation
		e.g. "p v q"
		operation should be a char that is translated into a truth table
		p and q are pointers to other propositions
			if p or q should be set value, then that proposition will have null pointers and a set value

	*/
};

int two_pow(int exponent);
string to_bin(int length, int x);