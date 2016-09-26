// Factory Method.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


class AbstractProduct
{
public:
	virtual ~AbstractProduct(){}

	virtual void product_active() = 0;
};

class DefaultProduct : public AbstractProduct
{
public:
	virtual void product_active()
	{
		cout << "DefaultProduct actived!" << endl;
	}
};

class ConcreteProduct : public AbstractProduct
{
public:
	virtual void product_active()
	{
		cout << "ConcreteProduct actived!" << endl;
	}
};


class Creator
{
public:
	Creator()
	{}

	//��������������ڴ�������ʵ�������ǵ����鷽������������
	void GenerateProduct()
	{
		_product = create_product();
	}

	AbstractProduct * GetProduct()
	{
		return _product;
	}

protected:
	//Factory Method
	//��ȱʡʵ�֣��������Ҫȱʡʵ�֣��˷������Զ���Ϊ���麯��
	virtual AbstractProduct * create_product()
	{
		return new DefaultProduct();
	}


private:
	AbstractProduct *_product;
};


class ConcreteCreator : public Creator
{
public:
	ConcreteCreator(){}

protected:
	//��һ��string product_type����ʵ�������н�����д����Ȥ�Ĳ�Ʒ
	virtual AbstractProduct * create_product()
	{
		return new ConcreteProduct();		

		//������Ȥ�Ĳ�Ʒ����ȱʡʵ�������
		//return Creator::create_product();
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	Creator *c = new ConcreteCreator();
	c->GenerateProduct();
	c->GetProduct()->product_active();

	return 0;
}

