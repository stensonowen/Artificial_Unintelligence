#pragma once
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
class var{
public:
	var(bool val) : value(val){
		static int count;
		//stringstream ss;
		//ss << count;
		//name = 'v' + ss.str();
		name = 'p' + count;
		count++;
	}
	var(const char &name_, bool val) : name(name_), value(val){}
	void set(bool bal){ value = bal; }
	bool operator<(const var &other){ return this->name < other.name; }
	
	//string name;
	char name;
	bool value;
};

