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
����Ĳ�����,��������Ա����
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
һ������ĳ����Ӧ���������ģ������������������ʵ��ֻ�С�ִ�С�
*/
class Command
{
public:
	virtual ~Command(){}

	virtual void Execute() = 0;
};


/*
���Ǽ򵥵����������ֻ��Ҫ����Receiver��һ����Ա���������
�������Ѿ��ǻ������Ƶģ�һ��������������ߺ���Ҫִ�еĶ��������֡�
Receiver��������ߣ�Action����Ҫִ�еĶ������������Ѿ�����������ĸ�������
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
		//.*��->*����Ա���������
		(_receiver.*_action)();
	}

private:
	ReceiverType _receiver;
	Action _action;
};


/*
����ͨ�ľ�������
�ڹ��캯���ж���ò�����,Ȼ����execute�е��ò������������Ӧ�Ĺ���
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
�����Commandģʽ+Compositeģʽ
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
	vector<Command *> _commands;		//����һ��ָ������Commandָ���vector��Compositeģʽ�Ĺؼ�
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