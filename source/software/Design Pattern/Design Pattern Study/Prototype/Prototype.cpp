// Prototype.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


//原型的虚基类
class Prototype
{
public:
	Prototype(const string &state)
		: _state(state)
	{}

	string State()
	{
		return _state;
	}

	virtual ~Prototype(){}

	//一般来说,这个都为纯虚函数,很难提供一个好的默认实现
	virtual Prototype* clone() = 0;	

protected:
	string _state;
};

//实际派生类1
class ConcretePrototype1 : public Prototype
{
public:
	ConcretePrototype1(const string &state)
		: Prototype(state)
	{}

	virtual ~ConcretePrototype1(){}

	virtual Prototype* clone()
	{
		return new ConcretePrototype1(_state);
	}
};

//实际派生类2
class ConcretePrototype2 : public Prototype
{
public:
	ConcretePrototype2(const string &state)
		: Prototype(state)
	{}

	virtual ~ConcretePrototype2(){}

	virtual Prototype* clone()
	{
		return new ConcretePrototype2(_state);
	}

private:
	string _state;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Prototype *p1 = new ConcretePrototype1("Prototype state 1");
	Prototype *p2 = new ConcretePrototype1("Prototype state 2");

	cout << p1->State() << endl;
	cout << p2->State() << endl;

	Prototype *p3 = p1->clone();
	Prototype *p4 = p2->clone();

	cout << p3->State() << endl;
	cout << p4->State() << endl;

	return 0;
}

