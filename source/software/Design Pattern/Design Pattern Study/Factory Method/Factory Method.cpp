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

	//这个方法看起来在创建对象，实际上它是调用虚方法来创建对象
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
	//带缺省实现，如果不需要缺省实现，此方法可以定义为纯虚函数
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
	//有一个string product_type可以实现子类中仅仅重写感兴趣的产品
	virtual AbstractProduct * create_product()
	{
		return new ConcreteProduct();		

		//不感兴趣的产品交给缺省实现来完成
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

