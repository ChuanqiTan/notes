// Template Method.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;


class AbstractGenerator
{
public:
	//这就是一个Template Method，它定义了一个算法的框架
	void Display()
	{
		//“模板方法”就是调用了多个“工厂方法”的算法框架
		//其实这是一个非常非常常见且易于理解的方案，平时编程无意中都用过太多次
		if (CalcuteFileSize() > 100)
		{
			DisplayBigFile();
		}
		else
		{
			DisplaySmallFile();
		}
	}


protected:	//工厂方法应该是受保护的

	//工厂方法
	virtual int CalcuteFileSize() = 0;

	//工厂方法
	virtual void DisplayBigFile()
	{
		cout << "This is a big file" << endl;
	}

	//工厂方法
	virtual void DisplaySmallFile()
	{
		cout << "This is a small file" << endl;
	}
};

class ConcreteGenerator : public AbstractGenerator
{
public:
	ConcreteGenerator(int s) 
		: _size(s){}

	virtual int CalcuteFileSize()
	{
		//read a file
		//return this file's size
		return _size;	
	}

	virtual void DisplayBigFile()
	{
		cout << "Oh~~~  a big file" << endl;
	}

private:
	int _size;
};


void main()
{	
	AbstractGenerator *g1 = new ConcreteGenerator(20);
	g1->Display();

	AbstractGenerator *g2 = new ConcreteGenerator(200);
	g2->Display();
}

