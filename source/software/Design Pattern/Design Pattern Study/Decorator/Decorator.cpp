// Decorator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;


//组件与修饰者共同的抽象基类
//因为修饰者既可以包含其它的修饰者也可以包含真正的组件，所以它们需要一个共同的基类
class Component
{
public:
	virtual void Operation() = 0;

	virtual ~Component(){}
};


//真正的组件
class ConcreteComponent : public Component
{
public:
	virtual void Operation()
	{
		cout << "ConcreteComponent Operation" << endl;
	}
};


//修饰者的抽象基类，修饰者最重要的特征就是包含一个指向共同基类的指针Component *_component
class Decorator : public Component
{
public:	
	virtual void Operation()
	{
		//缺省的行为：转发
		if (_component != NULL)
		{
			_component->Operation();
		}
	}

protected:
	//修饰者必须包含Component，所以要在构造函数中初始化_component成员
	//不能有无参的构造函数
	Decorator(Component *c) : _component(c)
	{}

private:
	//这里_component用private修饰好，一个修饰者不用去关心它所修饰的组件的细节
	Component *_component;		
};


//具体的修饰者
//提供了一个AddBehavior()来附加新的行为
class ConcreteDecorator : public Decorator
{
public:
	ConcreteDecorator(Component *c)
		: Decorator(c)
	{}

	virtual void Operation()
	{
		Decorator::Operation();	//不去关心细节，仅仅链式调用
		AddBehavior();
	}

private:
	void AddBehavior()
	{
		cout << "ConcreteDecorator AddBehavior" << endl;
	}
};


void main()
{
	ConcreteComponent c;
	ConcreteDecorator d1(&c);
	ConcreteDecorator d2(&d1);
	d2.Operation();	
}


