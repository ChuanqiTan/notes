// Flyweight.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;


//抽象的享元基类
class Flyweight
{
public:
	//基类Flyweight最重要的就是提供了一个根据“外部状态”进行操作的接口
	//这里操作是：打印字符串和当前的位置。
	//其中： 字符串是内部状态、位置信息是外部状态
	virtual void PrintStringAndPostion(const string &extrinsic_state) = 0;

	virtual ~Flyweight(){}
};


//具体的享元类
class ConcreteFlyweight : public Flyweight
{
	//声明FlyweightFactory为友元
	friend class FlyweightFactory;

public:
	//根据 内部、外部状态 进行打印
	virtual void PrintStringAndPostion(const string &extrinsic_state)
	{
		cout << "Operation with : " << _intrinsic_state << "\t" << extrinsic_state << endl;
	}

private:
	//将构造函数声明为私有，这样就只能由友元FlyweightFactory来产生享元实例了
	ConcreteFlyweight(const string &key)
		: _intrinsic_state(key)
	{
		cout << "Constructor a new Flyweight by key = " << key << endl;
	}

	string _intrinsic_state;
};


/*
享元工厂类
每次都由享元工厂来产生享元可保证相同的享元会共享一个实例
*/
class FlyweightFactory
{
private:
	FlyweightFactory(){}

public:
	//New Signlton Method
	static FlyweightFactory& Instance()
	{
		static FlyweightFactory _instance;
		return _instance;
	}

	Flyweight* GetFlyweight(const string &key)
	{
		if (_flyweights.count(key) == 0)
		{
			Flyweight *new_flyweight = new ConcreteFlyweight(key);
			_flyweights.insert(pair<string, Flyweight*>(key, new_flyweight));
		}

		return _flyweights[key];
	}

private:
	map<string, Flyweight*> _flyweights;
};


void main()
{
	vector<Flyweight*> vec;
	for (size_t i = 0; i < 10; ++i)
	{
		//十个不同位置的ConcreteFlyweight对象实际上只产生了两个不同的ConcreteFlyweight对象
		vec.push_back(FlyweightFactory::Instance().GetFlyweight(i % 2 == 0 ? "abc" : "xyz"));
	}

	for (size_t i = 0; i < 10; ++i)
	{
		//位置信息作为“外部状态”，在调用时传递给Flyweight
		stringstream position;
		position << "At position: " << i;

		vec[i]->PrintStringAndPostion(position.str());
	}
}
