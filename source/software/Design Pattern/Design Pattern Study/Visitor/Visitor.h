#pragma once

//ͷ�ļ��в�Ӧ�ð������������ͷ�ļ�����Ϊͷ�ļ��н�����ֻ�а���ָ�����������ָ��
//ָ��Ĵ�С�ǹ̶��ģ�����ֻ��Ҫһ����ͨ����������OK��
//���Զ�����Ҫ�õ����࣬����ֻҪ����һ��������;Ϳ�����
class ConcreteElement1;
class ConcreteElement2;

class AbstractVisitor
{
public:
	virtual ~AbstractVisitor(){}

	// ������Լ̳в����ÿһ������һ���ӿھͿ������ø���������ض��ӿڣ���һ����Ҫʹ�ó������Ľӿڣ������Ը���
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

