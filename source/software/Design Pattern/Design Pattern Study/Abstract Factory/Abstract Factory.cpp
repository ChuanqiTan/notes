// Abstract Factory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

class ProductA
{
public:
	ProductA(const string &sign) 
		: _sign(sign)
	{}

	string Sign()
	{
		return _sign;
	}

private:
	string _sign;
};

class ProductB
{
public:
	ProductB(const string &sign) 
		: _sign(sign)
	{}

	string Sign()
	{
		return _sign;
	}

private:
	string _sign;
};


class AbstractFactory
{
public:
	virtual ~AbstractFactory(){}

	virtual ProductA * GetProductA() = 0;
	virtual ProductB * GetProductB() = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
public:
	virtual ProductA * GetProductA()
	{
		return new ProductA("ProductA made by ConcreteFactory1");
	}
	virtual ProductB * GetProductB()
	{
		return new ProductB("ProductB made by ConcreteFactory1");
	}

};

class ConcreteFactory2 : public AbstractFactory
{
public:
	virtual ProductA * GetProductA()
	{
		return new ProductA("ProductA made by ConcreteFactory2");
	}
	virtual ProductB * GetProductB()
	{
		return new ProductB("ProductB made by ConcreteFactory2");
	}

};


class Client
{
public:
	Client(AbstractFactory *factory)
	{
		_pA = factory->GetProductA();
		_pB = factory->GetProductB();
	}

	ProductA * GetProductA()
	{
		return _pA;
	}

	ProductB * GetProductB()
	{
		return _pB;
	}

private:
	ProductA * _pA;
	ProductB * _pB;
};

int _tmain(int argc, _TCHAR* argv[])
{
	AbstractFactory *f1 = new ConcreteFactory1();
	AbstractFactory *f2 = new ConcreteFactory2();

	Client c1(f1);
	cout << c1.GetProductA()->Sign() << endl;
	cout << c1.GetProductB()->Sign() << endl;

	Client c2(f2);
	cout << c2.GetProductA()->Sign() << endl;
	cout << c2.GetProductB()->Sign() << endl;

	delete f1;
	delete f2;
	return 0;
}

