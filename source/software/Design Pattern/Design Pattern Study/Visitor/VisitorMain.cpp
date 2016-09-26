// Visitor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include "Element.h"
#include "Visitor.h"


void main()
{
	//�������ṹ��һ����˵��������������͵Ķ���ṹ�϶࣬����Ϊ�˼򵥽������������͵Ķ���ṹ��
	vector<AbstractElement *> object_structre;		
	object_structre.push_back(new ConcreteElement1("product1"));
	object_structre.push_back(new ConcreteElement2("product2", "Good"));
	object_structre.push_back(new ConcreteElement1("product3"));
	object_structre.push_back(new ConcreteElement1("product4"));
	object_structre.push_back(new ConcreteElement2("product5", "Bad"));

	//���������
	AbstractVisitor *visitor1 = new ConcreteVisitor1();		//�����������ӷ����ߣ�����ԭ���Ķ���ṹ�����Ӱ��
	AbstractVisitor *visitor2 = new ConcreteVisitor1();		//�����������ӷ����ߣ�����ԭ���Ķ���ṹ�����Ӱ��
	AbstractVisitor *visitor3 = new ConcreteVisitor2();		//�����������ӷ����ߣ�����ԭ���Ķ���ṹ�����Ӱ��
	AbstractVisitor *visitor4 = new ConcreteVisitor2();		//�����������ӷ����ߣ�����ԭ���Ķ���ṹ�����Ӱ��
	AbstractVisitor *visitor5 = new ConcreteVisitor2();		//�����������ӷ����ߣ�����ԭ���Ķ���ṹ�����Ӱ��

	//�ɶ���ṹ�������������
	for (vector<AbstractElement *>::iterator iter = object_structre.begin(); iter != object_structre.end(); ++iter)
	{
		(*iter)->Accpet(visitor1);
		(*iter)->Accpet(visitor2);
		(*iter)->Accpet(visitor3);
		(*iter)->Accpet(visitor4);
		(*iter)->Accpet(visitor5);
	}	
}

