#include "prop.h"
#include <iostream>

prop::prop(){
}

prop::prop(const bool &val) : value(val) {}
prop::prop(var *val) : val_ptr(val) {}

prop::prop(const var &p, const char op, const var &q) : operation(op){
	val1 = new prop(&p);
	val1->parent = this;
	val2 = new prop(&q);
	val2->parent = this;
}

prop::prop(prop *p, const char op, prop *q) : operation(op){
	//cout << "\t" << p << "," << &q << endl;
	val1 = p;
	val2 = q;
	val1->parent = this;
	val2->parent = this;
}
/*
prop *prop::operator=(prop *other){
	val1 = other->val1;
	val2 = other->val2;
	operation = other->operation;
	value = other->value;
	return this;
}

prop prop::operator=(const prop &other){
	val1 = other.val1;
	val2 = other.val2;
	operation = other.operation;
	value = other.value;
	return this;
}

*/
prop::~prop(){
}

bool prop::get_value(){
	if (val1 == NULL && val2 == NULL){
		if(val_ptr == NULL) return value;
		else return val_ptr->value;
	}
	bool p = val1->get_value();
	bool q = val2->get_value();
	//cout << "\t" << p << operation << q << " = " << endl;
	if (operation == '^') return (p && q);			//	and
	else if (operation == 'V') return (p || q);		//	or
	else if (operation == 'X') return (p != q);		//	xor
	else if (operation == '|') return !(p && q);	//	nand
	else if (operation == '~') return !p;			//	not
	else if (operation == '=') return (p == q);		//	biconditional
	else if (operation == '>') return (q || (!p));	//	conditional
	else{
		cerr << "unrecognized operation: " << operation << endl;
		exit(1);
	}
}

void follow_path(prop* tmp, set<var*> &vars){
	if (tmp->val_ptr != NULL) vars.insert(tmp->val_ptr);
	else{
		if (tmp->val1 != NULL) follow_path(tmp->val1, vars);
		if (tmp->val2 != NULL) follow_path(tmp->val2, vars);
	}
}

void prop::tt(){
	string prop_str = this->to_string();
	cout << prop_str << " :" << endl;
	//follow each path down until it reaches a boolean pointer
	set<var*> vars;
	prop* tmp = this;
	follow_path(this, vars);
	vector<var*> values;
	for (set<var*>::iterator itr = vars.begin(); itr != vars.end(); itr++){
		cout << "\t" << (*itr)->name;
		values.push_back(*(itr));
		(*itr)->value = 1;
	}
	//print out proposition as string; (must determine number of tabs (tab = 7 spaces))
	int num_tabs = prop_str.length() / 7;
	cout << "\t" << prop_str;
	for (int k = 0; k < num_tabs; k++) cout << "\t";
	cout << endl;
	string combo;
	for (int i = 0; i < two_pow(vars.size()); i++){ //size - 1?
		//cycle through all possible combinations of variable values
		combo = to_bin(vars.size(), i);
		for (unsigned int j = 0; j < values.size(); j++){
			if (combo[j] == '1') values[j]->value = false;	//swapped for convention of truth table
			else values[j]->value = true;
			cout << "\t" << values[j]->value;
		}
		cout << "\t" << this->get_value();
		for (int k = 0; k < num_tabs; k++) cout << "\t";
		cout << endl;
	}
	cout << endl;
	//set variables to initial values?
}

string prop::to_string(){
	string out = "";
	if (val_ptr != NULL){
		//if it's a variable:
		out += string(1, val_ptr->name);
		return out;
	}
	if (operation == '~'){
		out += operation + val1->to_string();
	}
	else{
		out += "(" + val1->to_string() + ")";
		out += operation;
		out += "(" + val2->to_string() + ")";
	}
	return out;
}

int two_pow(const int exponent){
	// power function is expensive (and I forgot it)
	int power = 1;
	for (int i = 0; i < exponent; i++) power *= 2;
	return power;
}

string to_bin(int length, int x){
	//cannot use bitset<length>(x) because length isn't defined until vars are counted
	string out = "";
	//int power = 1;	
	//for (int i = 0; i < length - 1; i++) power *= 2;
	int power = two_pow(length - 1);
	for (int i = length - 1; i >= 0; i--){
		if (x >= power){
			out += "1";
			x -= power;
		}
		else out += "0";
		power /= 2;
	}
	return out;
}