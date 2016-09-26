// Adapter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


namespace ClassAdapter
{
	class Target
	{
	public:
		virtual ~Target(){}

		virtual void DoA() = 0;

		virtual void DoB() = 0;
	};

	class Adaptee
	{
	public:
		virtual ~Adaptee(){}

		void Do1()
		{
			cout << "Do 1" << endl;
		}

		void Do2()
		{
			cout << "Do 2" << endl;
		}
	};

	// 使用已有的Adaptee接口去实现Target接口
	// 注意的是：这里使用public继承Target, private继承Adaptee
	class Adapter : public Target, private Adaptee
	{
	public:
		void DoA()
		{
			Do1();
		}

		void DoB()
		{
			Do2();
		}
	};
}

namespace ObjectAdapter
{
	class Target
	{
	public:
		virtual ~Target(){}

		virtual void DoA() = 0;

		virtual void DoB() = 0;
	};

	class Adaptee
	{
	public:
		void Do1()
		{
			cout << "Do 1" << endl;
		}

		void Do2()
		{
			cout << "Do 2" << endl;
		}
	};

	//使用已有的Adaptee接口去实现Target接口
	class Adapter : public Target
	{
	public:
		Adapter(Adaptee &e) 
			: _adaptee(e)
		{}

		void DoA()
		{
			_adaptee.Do1();
		}

		void DoB()
		{
			_adaptee.Do2();
		}

	private:
		Adaptee &_adaptee;
	};
}


int _tmain(int argc, _TCHAR* argv[])
{
	{
		ClassAdapter::Target *target = new ClassAdapter::Adapter();
		target->DoA();
		target->DoB();
	}

	cout << endl;

	{
		ObjectAdapter::Adaptee adaptee;
		ObjectAdapter::Target *target = new ObjectAdapter::Adapter(adaptee);
		target->DoA();
		target->DoB();
	}

	return 0;
}