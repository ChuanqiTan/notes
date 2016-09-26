// Design Pattern Study.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

//����
class Mediator;

class AbstractColleague
{
public:
	//��Colleague֪ͨMediator
	virtual void ToBeReady() = 0;

	//��Mediator֪ͨColleague
	virtual void SayName() = 0;

	virtual ~AbstractColleague(){}

protected:
	AbstractColleague(Mediator * const mediator) 
		: _mediator(mediator){}

	Mediator *_mediator;
};

class ColleagueA : public AbstractColleague
{
public:
	ColleagueA(Mediator * const mediator)
		: AbstractColleague(mediator)
	{}

	virtual void ToBeReady();

	virtual void SayName()
	{
		cout << "My name is A" << endl;
	}
};

class ColleagueB : public AbstractColleague
{
public:
	ColleagueB(Mediator * const mediator)
		: AbstractColleague(mediator)
	{}

	virtual void ToBeReady();

	virtual void SayName()
	{
		cout << "My name is B" << endl;
	}
};

class ColleagueC : public AbstractColleague
{
public:
	ColleagueC(Mediator * const mediator)
		: AbstractColleague(mediator)
	{}

	virtual void ToBeReady();

	virtual void SayName()
	{
		cout << "My name is C" << endl;
	}
};

class Mediator
{
public:
	static Mediator & Instance()
	{
		static Mediator instance;
		return instance;
	}


	void BeginReadyAndToSayName()
	{
		a->ToBeReady();
	}

	void AReadyNow()
	{
		b->ToBeReady();
	}


	void BReadyNow()
	{
		c->ToBeReady();
	}

	void CReadyNow()
	{
		AllSayName();
	}

private:
	Mediator()
	{
		a = new ColleagueA(this);
		b = new ColleagueB(this);
		c = new ColleagueC(this);
		_ready_count = 0;
	}

	Mediator(Mediator &);
	Mediator & operator=(Mediator &);

	void AllSayName()
	{
		cout << "Mediator command all to say name" << endl;
		a->SayName();
		b->SayName();
		c->SayName();
	}


	AbstractColleague *a;
	AbstractColleague *b;
	AbstractColleague *c;
	int _ready_count;
};

void ColleagueA::ToBeReady()
{
	cout << "ColleagueA to be ready" << endl;
	_mediator->AReadyNow();
}

void ColleagueB::ToBeReady()
{
	cout << "ColleagueB to be ready" << endl;
	_mediator->BReadyNow();
}

void ColleagueC::ToBeReady()
{
	cout << "ColleagueC to be ready" << endl;
	_mediator->CReadyNow();
}

void main()
{
	//Mediator�е�Colleague���໥��֪���Է��Ĵ���
	//����֮��Ľ����߼���������Mediator����
	//һ��A->B->C������׼��,Ȼ�������е���׼������֮�����������Լ�������
	//��Щ�߼�A��B��C���໥��֪��������������֪���Է��Ĵ��ڣ�������ֻ���Լ��Ĺ���
	//ֻ��Mediator֪��������Colleague�Ĵ��ڣ�ͬʱ���е�ColleagueҲ��֪��Mediator�Ĵ���
	Mediator::Instance().BeginReadyAndToSayName();
}