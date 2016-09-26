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

//�����ߵĳ������
class Handler
{
public:
	virtual void HandleRequester(string request_id)
	{
		//�����ṩĬ�ϵĴ���,���chain������һ�������߾�ת��,������ʾ���˴���
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

	Handler *_successor;	//ְ�����ϵ���һ��������
};

//���崦����1
class ConcreteHandler1 : public Handler
{
public:
	ConcreteHandler1(string hander_name, Handler *h = 0)
		: Handler(h)
		, _hander_name(hander_name)
	{}

	virtual void HandleRequester(string request_id)
	{
		//����ܴ���ʹ���,���ܴ���͵��û����ṩ��Ĭ����Ϊ
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

//���崦����2
class ConcreteHandler2 : public Handler
{
public:
	ConcreteHandler2(string hander_name, Handler *h = 0)
		: Handler(h)
		, _hander_name(hander_name)
	{}

	virtual void HandleRequester(string request_id)
	{
		//����ܴ���ʹ���,���ܴ���͵��û����ṩ��Ĭ����Ϊ
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
	//ConcreteHandler֮��Ĺ�ϵ���ǵ��͵�Compsite��ϵ
	//����֮���Composite��ϵ���Ժܷ����������Chain of Responsibility��

	//����ְ����
	ConcreteHandler1 a("a");//��ʵ��a��Զû�л��ᴦ����Ϣ����ΪChain�ϵ�c���������Ҫa���������Ϣ���������ֹͣ����
	ConcreteHandler2 b("b", &a);
	ConcreteHandler1 c("c", &b);
	Handler *chain_of_responsibility = &c;


	for (int i = 0; i < 5; ++i)
	{
		stringstream ss;
		ss << "request" << i;
		//��ְ�����Ͻ��д���
		chain_of_responsibility->HandleRequester(ss.str());
	}
}

