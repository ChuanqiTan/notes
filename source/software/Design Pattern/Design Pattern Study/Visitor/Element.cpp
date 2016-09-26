#include "stdafx.h"

#include "Visitor.h"
#include "Element.h"

void ConcreteElement1::Accpet(AbstractVisitor *v)
{
	//双分派：
	// 1－Accept是一个虚函数，在main中调用“(*iter)->Accpet(visitor1);”时完成一次分派
	// 2－这里由于v是一个指针且VisitConcreteElement1是虚函数，于是再借由v可以指向AbstractVisitor继承层次再实现了一次分派
	// 
	// 注：	也可以不使用双分派，AbstractVisitor只有一个接口VisitElemtn(AbstractVisitor *);
	//		但是这样的话就太浪费了，因为在ConcreteElemtnes的Accept方法中可以区分出来访问的是那一个Element
	//		仅仅使用抽象基类的接口相对于使用各个子类的特定接口来讲就丢失了一定的信息
	//		这种双分派虽然在编码上比较麻烦，需要Visitor知道Elements整个继承层次，但是往往由于可以
	//		利用各个子类的特殊接口，在自由度上更大，可行性也更好！
	v->VisitConcreteElement1(this);
}

void ConcreteElement2::Accpet(AbstractVisitor *v)
{
	v->VisitConcreteElement2(this);
}