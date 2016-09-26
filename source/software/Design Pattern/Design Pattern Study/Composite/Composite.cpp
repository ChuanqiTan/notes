// Composite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;


//����ĳ���ӿ�
//Add, Remove, GetChilds���ṩĬ�ϵ�ʵ��.
//OperationΪ���麯��
//����,������Ҷ�ӽ�㻹����Ͻ�㶼����ʹ������ӿ������в�����
class Component
{
public:
	virtual void Operation() = 0;

	virtual void Add(Component *c){}

	virtual void Remove(Component *c){}

	virtual vector<Component*> GetChilds()
	{
		vector<Component*> vec;
		return vec;
	}

	virtual ~Component(){}
};


//���ܰ����ӽ���Ҷ�ӽ��
//ֻ��Ҫ��д��Ҫ�ĺ���
//�ӿ��������������Ĺ��ܺ�������ֱ��ʹ�ó���ӿ��е�Ĭ��ʵ��
class Leaf : public Component
{
public:
	Leaf(const string &sign)
		: _sign(sign)
	{}

	virtual void Operation()
	{
		cout << "Leaf " << _sign << " Operation" << endl;
	}

private:
	string _sign;
};


//���԰����ӽ������
//��д��Ϊһ������Ӧ���ṩ�Ĺ���
class Composite : public Component
{
public:
	Composite(const string &sign)
		: _sign(sign)
	{}

	virtual void Operation()
	{
		cout << "Composite " << _sign << " Operation! And call children to operation" << endl;

		for (vector<Component*>::iterator iter = _childrens.begin(); iter != _childrens.end(); ++iter)
		{
			(*iter)->Operation();
		}
	}

	virtual void Add(Component *c)
	{
		_childrens.push_back(c);
	}

	virtual void Remove(Component *c)
	{
		_childrens.erase(remove(_childrens.begin(), _childrens.end(), c));
	}

	virtual vector<Component*> GetChilds()
	{
		return _childrens;
	}

	virtual ~Composite()
	{
		for (vector<Component*>::iterator iter = _childrens.begin(); iter != _childrens.end(); ++iter)
		{
			delete (*iter);
		}
	}

private:
	//��ָ�򸸽���ָ����Compositeģʽ�ľ�������,�ṹ��ģʽ���ǲ������ּ̳���ʵ��Ŀ�ĵ�
	vector<Component*> _childrens;
	string _sign;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Component *leaf1 = new Leaf("a");
	Component *leaf2 = new Leaf("b");
	Component *leaf3 = new Leaf("c");
	Component *leaf4 = new Leaf("d");
	Component *leaf5 = new Leaf("e");

	Component *composite1 = new Composite("A");
	Component *composite2 = new Composite("B");
	Component *composite3 = new Composite("C");
	Component *composite4 = new Composite("D");

	composite1->Add(composite2);
	composite1->Add(composite3);
	composite2->Add(leaf1);
	composite2->Add(leaf2);
	composite3->Add(leaf3);
	composite3->Add(composite4);
	composite4->Add(leaf4);
	composite4->Add(leaf5);

	composite1->Operation();

	return 0;
}

