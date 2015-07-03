#include<iostream>
#include<Windows.h>
#include<assert.h>
#include "prop.h"
#include "var.h"
using namespace std;

int main(){
	//test		(p ^ q)
	var a(1);
	var b(0);
	prop* p1 = new prop(&a);
	prop* p2 = new prop(&b);
	prop* p3 = new prop(p1, '^', p2);
	
	assert(p1->get_value() == true);
	assert(p2->get_value() == false);

	/*cout << a.value << "^" << b.value << "= " << p3->get_value() << endl;
	b.set(1);
	cout << a.value << "^" << b.value << "= " << p3->get_value() << endl;
	a.set(0);
	cout << a.value << "^" << b.value << "= " << p3->get_value() << endl;*/

	p3->tt();

	//test		(p ^ q) V r
	var c(0);
	prop* p4 = new prop(&c);
	prop* p5 = new prop(p3, 'V', p4);

	p5->tt();

	system("PAUSE");
	return 0;
}