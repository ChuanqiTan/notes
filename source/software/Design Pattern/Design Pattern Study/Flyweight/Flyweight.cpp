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


//�������Ԫ����
class Flyweight
{
public:
	//����Flyweight����Ҫ�ľ����ṩ��һ�����ݡ��ⲿ״̬�����в����Ľӿ�
	//��������ǣ���ӡ�ַ����͵�ǰ��λ�á�
	//���У� �ַ������ڲ�״̬��λ����Ϣ���ⲿ״̬
	virtual void PrintStringAndPostion(const string &extrinsic_state) = 0;

	virtual ~Flyweight(){}
};


//�������Ԫ��
class ConcreteFlyweight : public Flyweight
{
	//����FlyweightFactoryΪ��Ԫ
	friend class FlyweightFactory;

public:
	//���� �ڲ����ⲿ״̬ ���д�ӡ
	virtual void PrintStringAndPostion(const string &extrinsic_state)
	{
		cout << "Operation with : " << _intrinsic_state << "\t" << extrinsic_state << endl;
	}

private:
	//�����캯������Ϊ˽�У�������ֻ������ԪFlyweightFactory��������Ԫʵ����
	ConcreteFlyweight(const string &key)
		: _intrinsic_state(key)
	{
		cout << "Constructor a new Flyweight by key = " << key << endl;
	}

	string _intrinsic_state;
};


/*
��Ԫ������
ÿ�ζ�����Ԫ������������Ԫ�ɱ�֤��ͬ����Ԫ�Ṳ��һ��ʵ��
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
		//ʮ����ͬλ�õ�ConcreteFlyweight����ʵ����ֻ������������ͬ��ConcreteFlyweight����
		vec.push_back(FlyweightFactory::Instance().GetFlyweight(i % 2 == 0 ? "abc" : "xyz"));
	}

	for (size_t i = 0; i < 10; ++i)
	{
		//λ����Ϣ��Ϊ���ⲿ״̬�����ڵ���ʱ���ݸ�Flyweight
		stringstream position;
		position << "At position: " << i;

		vec[i]->PrintStringAndPostion(position.str());
	}
}
