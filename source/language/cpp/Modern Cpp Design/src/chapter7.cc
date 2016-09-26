/*
 * chapter7.cc
 *
 *  Created on: 2012-7-16
 *      Author: chuanqi
 */




#include <exception>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <loki/SmartPtr.h>
using namespace std;
using namespace Loki;

class SmartPtrTest {
public:
	SmartPtrTest(int v) : value(v) {
		cout << "SmartPtrTest()" << endl;
	}
	~SmartPtrTest() {
		cout << "~SmartPtrTest()" << endl;
	}

	int value;
};


void chapter7() {
	SmartPtr<SmartPtrTest> pi = new SmartPtrTest(8);
	cout << pi->value << endl;

	SmartPtr<SmartPtrTest, RefCounted, AllowConversion> pi2 = new SmartPtrTest(6);
	SmartPtrTest *opt = pi2;
	cout << opt->value << endl;
}
