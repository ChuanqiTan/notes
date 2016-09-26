// Bridge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


//ʵ�ֻ���
class Implementor
{
public:
	virtual void Operation() = 0;

	virtual ~Implementor(){}
};

//�����ʵ����
class ConcreteImplementorA : public Implementor
{
public:
	virtual void Operation()
	{
		cout << "ConcreteImplementorA do Operation" << endl;
	}
};


//����
//Abstractionһ��Ϊ������࣬����Ϊ�˼���Ϊ������
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
		_imp->Operation();	//���Գ��������ת����ʵ��
	}

protected:
	virtual Implementor* GetImplementor()	//����ͨ���̳���д�������ѡ��ͬ��ʵ����
	{
		return new ConcreteImplementorA();
	}

	Implementor *_imp;
};


//ʹ�õĿͻ�
class Client
{
public:
	Client()
	{
		//�ͻ�ֻ��Ҫ֪��Abstraction�Ϳ���,���ع���ʵ��(ʵ���˳�����ʵ�ֵķ���)
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

