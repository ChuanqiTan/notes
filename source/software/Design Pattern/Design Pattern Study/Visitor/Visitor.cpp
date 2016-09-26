#include "stdafx.h"

#include <iostream>
#include "Element.h"
#include "Visitor.h"
using namespace std;

//ConcreteVistor1�൱�ڽ�Elements��һ��SimpleShowName������ȡ��������ⲿ
void ConcreteVisitor1::VisitConcreteElement1(ConcreteElement1 * const e)
{
	cout << e->Name() << endl;
}

void ConcreteVisitor1::VisitConcreteElement2(ConcreteElement2 * const e)
{
	cout << e->Name() << endl;
}


//ConcreteVistor2�൱�ڽ�Elements��һ��ComplexShowName������ȡ��������ⲿ
void ConcreteVisitor2::VisitConcreteElement1(ConcreteElement1 * const e)
{
	cout << "This is a ConcreteElement1 : " << e->Name() << endl;
}

void ConcreteVisitor2::VisitConcreteElement2(ConcreteElement2 * const e)
{
	cout << "This is a ConcreteElement1 : " << e->Name() << ", " << e->Describe() << endl;
}