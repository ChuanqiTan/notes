// Bridge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


//实现基类
class Implementor
{
public:
	virtual void Operation() = 0;

	virtual ~Implementor(){}
};

//具体的实现类
class ConcreteImplementorA : public Implementor
{
public:
	virtual void Operation()
	{
		cout << "ConcreteImplementorA do Operation" << endl;
	}
};


//抽象
//Abstraction一般为抽象基类，这里为了简便就为具体类
class Abstraction
{
public:
	Abstraction()
	{
		_imp = GetImplementor();
	}

	virtual ~Abstraction(){}

	virtual void Operation()
	{
		_imp->Operation();	//将对抽象的请求转发给实现
	}

protected:
	virtual Implementor* GetImplementor()	//可以通过继承重写这个方法选择不同的实现者
	{
		return new ConcreteImplementorA();
	}

	Implementor *_imp;
};


//使用的客户
class Client
{
public:
	Client()
	{
		//客户只需要知道Abstraction就可以,不必关心实现(实现了抽象与实现的分离)
		_imp = new Abstraction();
	}

	void Do()
	{
		_imp->Operation();
	}

private:
	Abstraction *_imp;
};


int _tmain(int argc, _TCHAR* argv[])
{
	Client c;
	c.Do();

	return 0;
}

