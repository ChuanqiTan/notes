// Strategy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
using namespace std;

class AbstractStrategy
{
public:
	virtual void ShowWelcome(const string &game_name) const = 0;

	virtual ~AbstractStrategy(){}
};


class SimpleStrategy : public AbstractStrategy
{
public:
	virtual void ShowWelcome(const string &game_name) const
	{
		cout << endl << "Welcom to " << game_name << endl << endl;
	}
};


class MagnificentStrategy : public AbstractStrategy
{
public:
	virtual void ShowWelcome(const string &game_name) const
	{
		cout << "----------------------------------------------------" << endl;
		cout << "\t" << game_name << endl;
		cout << endl;
		cout << "                Welcome to this game !              " << endl;
		cout << endl;
		cout << "----------------------------------------------------" << endl;
	}
};



class Game
{
public:
	Game(string game_name)
		: _game_name(game_name)
	{
		_strategy = new SimpleStrategy();	//Ĭ�ϵĲ���
	}

	void SetShowWelcomeStrategy(AbstractStrategy *s)
	{
		delete _strategy;
		_strategy = s;
	}

	void ShowWelcome()
	{
		//ת�������Զ���
		_strategy->ShowWelcome(_game_name);
	}
	
	~Game()
	{
		if (_strategy != NULL)
		{
			delete _strategy;
			_strategy = NULL;
		}
	}

private:
	string _game_name;
	AbstractStrategy *_strategy;
};


void main()
{
	Game g("Game:Test");
	g.ShowWelcome();		//ʹ��Ĭ�ϵĲ���
	g.SetShowWelcomeStrategy(new MagnificentStrategy());	//���Ĳ���
	g.ShowWelcome();		//ʹ���µĲ���
}