#pragma once

//头文件中不应该包含其它的类的头文件，因为头文件中仅仅有只有包括指向这两个类的指针
//指针的大小是固定的，所以只需要一个普通的声明语句就OK了
//所以对于需要用到的类，仅仅只要声明一个这个类型就可以了
class ConcreteElement1;
class ConcreteElement2;

class AbstractVisitor
{
public:
	virtual ~AbstractVisitor(){}

	// 这种针对继承层次中每一个类留一个接口就可以利用各个子类的特定接口，不一定非要使用抽象基类的接口，可行性更好
	virtual void VisitConcreteElement1(ConcreteElement1 * const){}
	virtual void VisitConcreteElement2(ConcreteElement2 * const){}

protected:
	AbstractVisitor(){}
};

class ConcreteVisitor1 : public AbstractVisitor
{
public:
	virtual void VisitConcreteElement1(ConcreteElement1 * const e);

	virtual void VisitConcreteElement2(ConcreteElement2 * const e);
};

class ConcreteVisitor2 : public AbstractVisitor
{
public:
	virtual void VisitConcreteElement1(ConcreteElement1 * const e);

	virtual void VisitConcreteElement2(ConcreteElement2 * const e);
};

