// Command.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

/*
定义的参与者,有两个成员函数
*/
class MyClass
{
public:
	void Display1()
	{
		cout << "MyClass.Display1() called" << endl;
	}

	void Display2()
	{
		cout << "MyClass.Display2() called" << endl;
	}
};


/*
一个命令的抽象就应该是这样的，命令最基本的属性其实就只有“执行”
*/
class Command
{
public:
	virtual ~Command(){}

	virtual void Execute() = 0;
};


/*
这是简单的命令，适用于只需要调用Receiver的一个成员方法的情况
但是这已经是基本完善的：一个命令包括参与者和需要执行的动作两部分。
Receiver代表参与者，Action代表要执行的动作。这两者已经包括了命令的根本属性
*/
template<class ReceiverType>
class SimpleCommand : public Command
{
public:
	typedef void (ReceiverType::* Action)();

	SimpleCommand(ReceiverType &r, Action a)
		: _receiver(r), _action(a)
	{}

	void Execute()
	{
		//.*与->*：成员访问运算符
		(_receiver.*_action)();
	}

private:
	ReceiverType _receiver;
	Action _action;
};


/*
最普通的具体命令
在构造函数中定义好参与者,然后在execute中调用参与者来完成相应的功能
*/
class NormalCommand1 : public Command
{
public:
	NormalCommand1(MyClass &r)
		: _receiver(r)
	{}

	void Execute()
	{
		_receiver.Display1();
	}

private:
	MyClass _receiver;
};

class NormalCommand2 : public Command
{
public:
	NormalCommand2(MyClass &r)
		: _receiver(r)
	{}

	void Execute()
	{
		_receiver.Display2();
	}

private:
	MyClass _receiver;
};


/*
宏命令：Command模式+Composite模式
*/
class MacroCommand : public Command
{
public:
	MacroCommand(){}

	void Add(Command *c)
	{
		_commands.push_back(c);
	}

	void Remove(Command *c)
	{
		_commands.erase(remove(_commands.begin(), _commands.end(), c), _commands.end());
	}

	virtual void Execute()
	{
		for (vector<Command *>::iterator iter = _commands.begin(); iter != _commands.end(); ++iter)
		{
			(*iter)->Execute();
		}
	}

private:
	vector<Command *> _commands;		//包括一个指向基类的Command指针的vector是Composite模式的关键
};

void main()
{
	MyClass m;

	Command *aCommand = new SimpleCommand<MyClass>(m, &MyClass::Display1);
	aCommand->Execute();

	Command *bCommand = new NormalCommand1(m);
	bCommand->Execute();

	Command *cCommand = new NormalCommand2(m);
	cCommand->Execute();	

	MacroCommand micro_command;
	micro_command.Add(aCommand);
	micro_command.Add(bCommand);
	micro_command.Add(cCommand);
	micro_command.Execute();
}