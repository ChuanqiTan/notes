// Prototype.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


//ԭ�͵������
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

	//һ����˵,�����Ϊ���麯��,�����ṩһ���õ�Ĭ��ʵ��
	virtual Prototype* clone() = 0;	

protected:
	string _state;
};

//ʵ��������1
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

//ʵ��������2
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

