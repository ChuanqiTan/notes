// Decorator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;


//����������߹�ͬ�ĳ������
//��Ϊ�����߼ȿ��԰���������������Ҳ���԰������������������������Ҫһ����ͬ�Ļ���
class Component
{
public:
	virtual void Operation() = 0;

	virtual ~Component(){}
};


//���������
class ConcreteComponent : public Component
{
public:
	virtual void Operation()
	{
		cout << "ConcreteComponent Operation" << endl;
	}
};


//�����ߵĳ�����࣬����������Ҫ���������ǰ���һ��ָ��ͬ�����ָ��Component *_component
class Decorator : public Component
{
public:	
	virtual void Operation()
	{
		//ȱʡ����Ϊ��ת��
		if (_component != NULL)
		{
			_component->Operation();
		}
	}

protected:
	//�����߱������Component������Ҫ�ڹ��캯���г�ʼ��_component��Ա
	//�������޲εĹ��캯��
	Decorator(Component *c) : _component(c)
	{}

private:
	//����_component��private���κã�һ�������߲���ȥ�����������ε������ϸ��
	Component *_component;		
};


//�����������
//�ṩ��һ��AddBehavior()�������µ���Ϊ
class ConcreteDecorator : public Decorator
{
public:
	ConcreteDecorator(Component *c)
		: Decorator(c)
	{}

	virtual void Operation()
	{
		Decorator::Operation();	//��ȥ����ϸ�ڣ�������ʽ����
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


