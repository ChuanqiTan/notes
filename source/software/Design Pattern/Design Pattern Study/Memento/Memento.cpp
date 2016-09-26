// Memento.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

//ʵ������������Ϸ״̬���ݵ���
//Ҳ���Կ��ǰ�����ദ���GameMementoһ����˽�й��캯��+friend class GameMemento;
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


//Game��Ӧ��Memento����
//Ҳ���Կ��ǽ�GameState����������ݱ������������,�����Ļ���Ľṹ��,���ǿ������Բ���ֳ�������
//������д�����ֳַ�������Ľṹ��,GameState������䵱һ���������ݵ�����
class GameMemento
{
	//����Ԫʵ�ֶ�Game�Ŀ�ӿںͶ��������խ�ӿ�
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
	//ֻ�ܱ�Game���õĹ��캯��
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


//ĳ����Ϸ
class Game
{
public:
	//����һ��ȫ�µ���Ϸ
	Game()
		: _user_name("Tan Chuan Qi")
		, _step(6)
		, _score(60)
	{}

	//ʹ�ñ���¼���ָ�һ����Ϸ
	Game(GameMemento *memento)
		: _user_name(memento->GetState()->UserName())
		, _step(memento->GetState()->Step())
		, _score(memento->GetState()->Score())
	{}

	//�õ���ǰ����ı���¼
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
	Game g1;								//��ʼ��һ��ȫ�µ���Ϸ
	cout << "g1 : " << g1.Score() << endl;	//�����Ϸ��״̬

	g1.Score(100);							//��Ϸ��״̬���ı���
	cout << "g1 : " << g1.Score() << endl;	//�����Ϸ��״̬

	GameMemento *m = g1.GetMemento();		//��һ������¼���󱣴���Ϸ��״̬
	Game g2(m);								//���������¼ȥ�ָ�һ������Ϸ
	cout << "g2 : " << g2.Score() << endl;	//��ʾ����Ϸ��״̬�����Կ�����ԭ����Ϸ�б��ı��״̬������Ϸ�б�����������

	delete m;
}