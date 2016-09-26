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
	// ������Ϊ���麯��
	// ʹ���������ֻ��д���Ǹ���Ȥ��ʵ��
	// ��ȻҲ����ʹ��ͨ���Ĵ��麯��ʵ�ַ���
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
		{//һ��һ���Ĺ����ö���
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