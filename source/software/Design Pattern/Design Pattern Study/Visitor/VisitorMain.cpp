// Visitor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include "Element.h"
#include "Visitor.h"


void main()
{
	//构造对象结构（一般来说访问者用于组合型的对象结构较多，这里为了简单仅仅用了数组型的对象结构）
	vector<AbstractElement *> object_structre;		
	object_structre.push_back(new ConcreteElement1("product1"));
	object_structre.push_back(new ConcreteElement2("product2", "Good"));
	object_structre.push_back(new ConcreteElement1("product3"));
	object_structre.push_back(new ConcreteElement1("product4"));
	object_structre.push_back(new ConcreteElement2("product5", "Bad"));

	//定义访问者
	AbstractVisitor *visitor1 = new ConcreteVisitor1();		//可以任意的添加访问者，而对原来的对象结构不造成影响
	AbstractVisitor *visitor2 = new ConcreteVisitor1();		//可以任意的添加访问者，而对原来的对象结构不造成影响
	AbstractVisitor *visitor3 = new ConcreteVisitor2();		//可以任意的添加访问者，而对原来的对象结构不造成影响
	AbstractVisitor *visitor4 = new ConcreteVisitor2();		//可以任意的添加访问者，而对原来的对象结构不造成影响
	AbstractVisitor *visitor5 = new ConcreteVisitor2();		//可以任意的添加访问者，而对原来的对象结构不造成影响

	//由对象结构来负责遍历迭代
	for (vector<AbstractElement *>::iterator iter = object_structre.begin(); iter != object_structre.end(); ++iter)
	{
		(*iter)->Accpet(visitor1);
		(*iter)->Accpet(visitor2);
		(*iter)->Accpet(visitor3);
		(*iter)->Accpet(visitor4);
		(*iter)->Accpet(visitor5);
	}	
}

