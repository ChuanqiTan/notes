#include "stdafx.h"

#include <iostream>
#include "Element.h"
#include "Visitor.h"
using namespace std;

//ConcreteVistor1相当于将Elements的一个SimpleShowName操作提取到了类的外部
void ConcreteVisitor1::VisitConcreteElement1(ConcreteElement1 * const e)
{
	cout << e->Name() << endl;
}

void ConcreteVisitor1::VisitConcreteElement2(ConcreteElement2 * const e)
{
	cout << e->Name() << endl;
}


//ConcreteVistor2相当于将Elements的一个ComplexShowName操作提取到了类的外部
void ConcreteVisitor2::VisitConcreteElement1(ConcreteElement1 * const e)
{
	cout << "This is a ConcreteElement1 : " << e->Name() << endl;
}

void ConcreteVisitor2::VisitConcreteElement2(ConcreteElement2 * const e)
{
	cout << "This is a ConcreteElement1 : " << e->Name() << ", " << e->Describe() << endl;
}