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

//�۲��ߵĳ������
class AbstractObserver
{
public:
	virtual ~AbstractObserver(){}

	// Update����ʱ�ѹ۲�����Ҫ����Ϣһ���͹�ȥ��.���ڡ���ģ�͡�
	// ��Ϊ���еĸı����ϸ��Ϣ������ֻ��һ��ʱ��t����ͨ���������Ƴ���
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
	/// ֪ͨ���е�ע��۲��������鷢��
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

	//ע����2���۲���
	timer.Attach(new OriginStyleObserver());
	timer.Attach(new NewStyleObserver());

	//��ʼ��ʱ
	timer.Start();
}