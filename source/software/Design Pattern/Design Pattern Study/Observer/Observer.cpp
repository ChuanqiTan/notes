// Observer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>
#include <ctime>
using namespace std;

//观察者的抽象基类
class AbstractObserver
{
public:
	virtual ~AbstractObserver(){}

	// Update操作时把观察者需要的信息一起发送过去了.属于“推模型”
	// 因为所有的改变的详细信息（这里只有一个时间t）都通过参数被推出了
	virtual void Update(const time_t &t) = 0;
};

class OriginStyleObserver : public AbstractObserver
{
public:
	virtual void Update(const time_t &t)
	{
		cout << "Origin Style: " << t << endl;
	}

};

class NewStyleObserver : public AbstractObserver
{
public:
	virtual void Update(const time_t &t)
	{
		struct tm * timeinfo;
		timeinfo = localtime ( &t );

		cout << "New Style: " << asctime (timeinfo);
	}
};


class Timer
{
public:
	void Attach(AbstractObserver *o)
	{
		_observers.push_back(o);
	}

	void Detach(AbstractObserver *o)
	{
		_observers.erase(remove(_observers.begin(), _observers.end(), o));
	}

	void Start()
	{
		time_t begin_time = clock();

		while(true)
		{
			time_t end_time = clock();

			if (end_time - begin_time >= 1000)
			{
				begin_time = end_time;
				Trick(time(NULL));
			}
		}
	}


private:
	/// 通知所有的注册观察者有事情发生
	void Trick(time_t t)
	{
		for (vector<AbstractObserver *>::iterator iter = _observers.begin(); iter != _observers.end(); ++iter)
		{
			(*iter)->Update(t);
		}
	}


	vector<AbstractObserver *> _observers;
};


void main ()
{
	Timer timer;

	//注册了2个观察者
	timer.Attach(new OriginStyleObserver());
	timer.Attach(new NewStyleObserver());

	//开始计时
	timer.Start();
}