// Composite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;


//组件的抽象接口
//Add, Remove, GetChilds都提供默认的实现.
//Operation为纯虚函数
//这样,无论是叶子结点还是组合结点都可以使用这个接口来进行操作了
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


//不能包含子结点的叶子结点
//只需要重写必要的函数
//接口中类似于容器的功能函数可以直接使用抽象接口中的默认实现
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


//可以包含子结点的组件
//重写作为一个容器应该提供的功能
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
	//有指向父结点的指针是Composite模式的精髓所在,结构型模式多是采用这种继承来实现目的的
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

