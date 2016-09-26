// Interpreter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;


//�����Ļ���
class Context
{
public:
	void Add(const string &variable, bool value)
	{
		//������map���ص㣺���[]������Ҳ����ڵ�Ԫ������Զ���ӡ�
		_vars[variable] = value;
	}

	bool Lookup(const string &variable)
	{
		if (_vars.count(variable) != 0)
		{
			return _vars[variable];
		}

		throw exception("cannot find this int context");
	}

private:
	map<string, bool> _vars;
};


//���ʽ�ĳ������
class AbstractExpression
{
public:
	virtual ~AbstractExpression(){}

	virtual bool Evaluate(Context &c) = 0;
};


//�������ʽ
class VariableExpression : public AbstractExpression
{
public:
	VariableExpression(const string &s)
		: _var(s)
	{}

	virtual bool Evaluate(Context &c)
	{
		return c.Lookup(_var);
	}

private:
	string _var;
};


//�� ���ʽ
class AndExpression : public AbstractExpression
{
public:
	AndExpression(AbstractExpression *left, AbstractExpression *right)
		: _left(left), _right(right)
	{}

	virtual bool Evaluate(Context &c)
	{
		return _left->Evaluate(c) && _right->Evaluate(c);
	}

private:
	AbstractExpression *_left;
	AbstractExpression *_right;
};


//�� ���ʽ
class OrExpression : public AbstractExpression
{
public:
	OrExpression(AbstractExpression *left, AbstractExpression *right)
		: _left(left), _right(right)
	{}

	virtual bool Evaluate(Context &c)
	{
		return _left->Evaluate(c) || _right->Evaluate(c);
	}

private:
	AbstractExpression *_left;
	AbstractExpression *_right;
};


//�� ���ʽ
class NotExpression : public AbstractExpression
{
public:
	NotExpression(AbstractExpression *origin)
		: _origin(origin)
	{}

	virtual bool Evaluate(Context &c)
	{
		return !_origin->Evaluate(c);
	}

private:
	AbstractExpression *_origin;
};


void main()
{
	AbstractExpression *finial;
	Context c;
	c.Add("x", false);
	c.Add("y", true);
	c.Add("z", true);

	AbstractExpression *x = new VariableExpression("x");		//false
	finial = x;
	cout << (finial->Evaluate(c) ? "true" : "false") << endl;

	AbstractExpression *y = new VariableExpression("y");		//true
	finial = y;
	cout << (finial->Evaluate(c) ? "true" : "false") << endl;

	AbstractExpression *z = new VariableExpression("z");		//true
	finial = z;
	cout << (finial->Evaluate(c) ? "true" : "false") << endl;

	AbstractExpression *a1 = new AndExpression(x, y);			//(false && true) = false
	finial = a1;
	cout << (finial->Evaluate(c) ? "true" : "false") << endl;

	AbstractExpression *a2 = new OrExpression(a1, z);			//((false && true) || true) = true
	finial = a2;
	cout << (finial->Evaluate(c) ? "true" : "false") << endl;

	AbstractExpression *a3 = new NotExpression(a2);				//!((false && true) || true) = false
	finial = a3;
	cout << (finial->Evaluate(c) ? "true" : "false") << endl;
}


