// Chain Of Responsibility.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

//处理者的抽象基类
class Handler
{
public:
	virtual void HandleRequester(string request_id)
	{
		//基类提供默认的处理,如果chain还有下一个处理者就转发,否则提示无人处理
		if (_successor)
		{
			_successor->HandleRequester(request_id);
		}
		else
		{
			cout << "Nobody cope request " << request_id << endl;
		}
	}

	virtual ~Handler(){}

protected:
	Handler(Handler *p = 0)
		: _successor(p)
	{}

	Handler *_successor;	//职责链上的下一个处理者
};

//具体处理者1
class ConcreteHandler1 : public Handler
{
public:
	ConcreteHandler1(string hander_name, Handler *h = 0)
		: Handler(h)
		, _hander_name(hander_name)
	{}

	virtual void HandleRequester(string request_id)
	{
		//如果能处理就处理,不能处理就调用基类提供的默认行为
		if (request_id == "request0" || request_id == "request1")
		{
			cout << "ConcreteHandler1 \"" << _hander_name << "\" cope " << request_id << endl;
		}
		else
		{
			Handler::HandleRequester(request_id);		
		}
	}

private:
	string _hander_name;
};

//具体处理者2
class ConcreteHandler2 : public Handler
{
public:
	ConcreteHandler2(string hander_name, Handler *h = 0)
		: Handler(h)
		, _hander_name(hander_name)
	{}

	virtual void HandleRequester(string request_id)
	{
		//如果能处理就处理,不能处理就调用基类提供的默认行为
		if (request_id == "request3" || request_id == "request4")
		{
			cout << "ConcreteHandler2 \"" << _hander_name << "\" cope " << request_id << endl;
		}
		else
		{
			Handler::HandleRequester(request_id);		
		}
	}

private:
	string _hander_name;
};

void main()
{
	//ConcreteHandler之间的关系就是典型的Compsite关系
	//它们之间的Composite关系可以很方便的利用在Chain of Responsibility上

	//构造职责链
	ConcreteHandler1 a("a");//事实上a永远没有机会处理消息，因为Chain上的c会把所有需要a来处理的消息都处理掉并停止传递
	ConcreteHandler2 b("b", &a);
	ConcreteHandler1 c("c", &b);
	Handler *chain_of_responsibility = &c;


	for (int i = 0; i < 5; ++i)
	{
		stringstream ss;
		ss << "request" << i;
		//在职责链上进行传递
		chain_of_responsibility->HandleRequester(ss.str());
	}
}

