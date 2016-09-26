// Design Pattern Study.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

//声明
class Mediator;

class AbstractColleague
{
public:
	//由Colleague通知Mediator
	virtual void ToBeReady() = 0;

	//由Mediator通知Colleague
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
	//Mediator中的Colleague都相互不知道对方的存在
	//它们之间的交互逻辑被包含在Mediator中了
	//一旦A->B->C的轮流准备,然后在所有的人准备好了之后再轮流报自己的名字
	//这些逻辑A、B、C都相互不知道（他们甚至不知道对方的存在），它们只做自己的工作
	//只有Mediator知道所有人Colleague的存在，同时所有的Colleague也都知道Mediator的存在
	Mediator::Instance().BeginReadyAndToSayName();
}