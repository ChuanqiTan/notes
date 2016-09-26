// State.cpp : Defines the entry point for the console application.
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

class Game;

class AbstractState
{
public:
	virtual void Display() = 0;

protected:
	AbstractState(Game *g)
		: _game(g)
	{}

	Game *_game;
};

class WaitingStartState : public AbstractState
{
public:
	WaitingStartState(Game *g)
		: AbstractState(g)
	{}

	virtual void Display();
};

class PlayingState : public AbstractState
{
public:
	PlayingState(Game *g)
		: AbstractState(g)
	{}

	virtual void Display();
};

class Game
{
public:
	Game();

	void SetState(AbstractState *s);

	void Display();

	~Game();

private:
	AbstractState *_state;
};


Game::Game()
{
	_state = new WaitingStartState(this);
}

Game::~Game()
{
	delete _state;
}

void Game::SetState(AbstractState *s)
{
	if (s != _state)
	{
		delete _state;
		_state = s;
	}
}

void Game::Display()
{
	//将与状态相关的操作转发给 状态对象 处理
	_state->Display();
}

void WaitingStartState::Display()
{
	cout << "Waiting to start!" << endl;
	_game->SetState(new PlayingState(_game));
}

void PlayingState::Display()
{
	for (int i = 0; i < 10; ++i)
	{
		cout << "Playing step " << i << endl;
	}	
}

void main ()
{
	Game g;
	g.Display();
	g.Display();
}