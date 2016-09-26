#pragma once

#include <string>			
using namespace std;

class AbstractVisitor;

class AbstractElement
{
public:
	virtual ~AbstractElement(){}
	virtual void Accpet(AbstractVisitor *v) = 0;
};

class ConcreteElement1 : public AbstractElement
{
public:
	ConcreteElement1(const string &name)
		: _name(name)
	{}

	virtual void Accpet(AbstractVisitor *v);

	string Name(){	return _name; }

private:
	string _name;
};

class ConcreteElement2 : public AbstractElement
{
public:
	ConcreteElement2(const string &name, const string &describe)
		: _name(name), _describe(describe)
	{}

	virtual void Accpet(AbstractVisitor *v);

	string Name(){	return _name; }

	string Describe(){	return _describe; }

private:
	string _name;
	string _describe;
};

