// Memento.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

//实际用来保存游戏状态数据的类
//也可以考虑把这个类处理成GameMemento一样的私有构造函数+friend class GameMemento;
class GameState
{
public:
	GameState(const string &user_name, int step, int score)
		: _user_name(user_name), _step(step), _score(score)
	{}

	string UserName()
	{
		return _user_name;
	}

	int Step()
	{
		return _step;
	}

	int Score()
	{
		return _score;
	}

private:
	string _user_name;
	int _step;
	int _score;
};


//Game对应的Memento对象
//也可以考虑将GameState所保存的数据保存在这个类中,这样的话类的结构简单,但是可重用性不如分成两个类
//在现在写的这种分成两个类的结构中,GameState类仅仅充当一个保存数据的作用
class GameMemento
{
	//用友元实现对Game的宽接口和对其它类的窄接口
	friend class Game;

public:
	~GameMemento()
	{
		if (_state != NULL)
		{
			delete _state;
			_state = NULL;
		}
	}

private:
	//只能被Game调用的构造函数
	GameMemento(const string &user_name, int step, int score)
	{
		_state = new GameState(user_name, step, score);
	}

	GameState * GetState()
	{
		return _state;
	}

private:
	GameState *_state;
};


//某种游戏
class Game
{
public:
	//创建一个全新的游戏
	Game()
		: _user_name("Tan Chuan Qi")
		, _step(6)
		, _score(60)
	{}

	//使用备忘录来恢复一个游戏
	Game(GameMemento *memento)
		: _user_name(memento->GetState()->UserName())
		, _step(memento->GetState()->Step())
		, _score(memento->GetState()->Score())
	{}

	//得到当前对象的备忘录
	GameMemento * GetMemento()
	{
		GameMemento *memento = new GameMemento(_user_name, _step, _score);
		return memento;
	}

	void Score(int score)
	{
		_score = score;
	}

	int Score()
	{
		return _score;
	}

	string UserName()
	{
		return _user_name;
	}

	int Step()
	{
		return _step;
	}

private:
	string _user_name;
	int _step;
	int _score;
};


void main()
{
	Game g1;								//初始化一个全新的游戏
	cout << "g1 : " << g1.Score() << endl;	//输出游戏的状态

	g1.Score(100);							//游戏的状态被改变了
	cout << "g1 : " << g1.Score() << endl;	//输出游戏的状态

	GameMemento *m = g1.GetMemento();		//用一个备忘录对象保存游戏的状态
	Game g2(m);								//用这个备忘录去恢复一个新游戏
	cout << "g2 : " << g2.Score() << endl;	//显示新游戏的状态，可以看到，原来游戏中被改变的状态在新游戏中被保存下来了

	delete m;
}