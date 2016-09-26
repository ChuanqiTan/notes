// Singleton.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

//标准写法实现的单件模式
class Singleton
{
protected:
	//一般将构造方法实现为受保护的，如果不需要被扩展，也可以实现为私有的
	Singleton()
	{
		cout << "A old style singleton constructor" << endl;
	}

private:
	//一个私有的静态成员
	static Singleton * _instance;

public:
	//公有的Singleton方法，返回该类的唯一实例
	static Singleton * Instance()
	{
		if (NULL == _instance)
		{
			//惰性(lazy)初始化，只有使用时才初始化
			_instance = new Singleton();
		}
		return _instance;
	}

	void Display()
	{
		cout << "Old singleton display" << endl;
	}
};

Singleton * Singleton::_instance = NULL;		//初始化为空指针



//Effective C++上介绍的新的Singleton写法
class NewSingleton
{
private:
	NewSingleton()
	{
		cout << "New style singleton constructor" << endl;
	}

public:
	/*
		新的写法省略了检查NULL==_instance的过程，理论效率更好
		而且减少了实现单件的代码量
		真是太棒了！
	*/
	static NewSingleton& Instance()
	{
		static NewSingleton _instance;
		return _instance;
	}

	void Display()
	{
		cout << "New singleton display" << endl;
	}
};

void main()
{
	Singleton::Instance()->Display();
	Singleton::Instance()->Display();
	Singleton::Instance()->Display();
	Singleton::Instance()->Display();
	Singleton::Instance()->Display();
	Singleton::Instance()->Display();	

	NewSingleton::Instance().Display();
	NewSingleton::Instance().Display();
	NewSingleton::Instance().Display();
	NewSingleton::Instance().Display();
	NewSingleton::Instance().Display();
	NewSingleton::Instance().Display();
}