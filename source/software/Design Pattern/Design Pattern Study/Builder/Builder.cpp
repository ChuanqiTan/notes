// Builder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Builder
{
public:
	// 方法不为纯虚函数
	// 使得子类可以只重写它们感兴趣的实现
	// 当然也可以使用通常的纯虚函数实现方法
	virtual void BuilderPart(string aPart){}

	virtual string GetResult(){	return NULL; }
};

class SimpleBuilder : public Builder
{
public:
	virtual void BuilderPart(string aPart)
	{
		_result << aPart << endl;
	}

	virtual string GetResult()
	{
		return _result.str();
	}

private:
	stringstream _result;
};

class Director
{
public:
	Director(Builder *builder)
	{
		_builder = builder;

		vector<string> _parts;
		_parts.push_back("Part A");
		_parts.push_back("Part B");
		_parts.push_back("Part C");

		for (vector<string>::iterator iter = _parts.begin(); iter != _parts.end(); ++iter)
		{//一步一步的构建好对象
			_builder->BuilderPart(*iter);
		}
	}

	string GetResult()
	{
		return _builder->GetResult();
	}

private:
	Builder *_builder;
	string _result;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Builder *b = new SimpleBuilder();
	Director d(b);
	cout << d.GetResult() << endl;

	return 0;
}