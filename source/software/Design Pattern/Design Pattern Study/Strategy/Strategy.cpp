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
		_strategy = new SimpleStrategy();	//默认的策略
	}

	void SetShowWelcomeStrategy(AbstractStrategy *s)
	{
		delete _strategy;
		_strategy = s;
	}

	void ShowWelcome()
	{
		//转发给策略对象
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
	g.ShowWelcome();		//使用默认的策略
	g.SetShowWelcomeStrategy(new MagnificentStrategy());	//更改策略
	g.ShowWelcome();		//使用新的策略
}