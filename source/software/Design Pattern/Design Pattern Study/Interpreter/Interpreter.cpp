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


//上下文环境
class Context
{
public:
	void Add(const string &variable, bool value)
	{
		//利用了map的特点：如果[]运算符找不存在的元素则会自动添加。
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


//表达式的抽象基类
class AbstractExpression
{
public:
	virtual ~AbstractExpression(){}

	virtual bool Evaluate(Context &c) = 0;
};


//变量表达式
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


//与 表达式
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


//或 表达式
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


//非 表达式
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


