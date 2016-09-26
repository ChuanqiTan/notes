// Singleton.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

//��׼д��ʵ�ֵĵ���ģʽ
class Singleton
{
protected:
	//һ�㽫���췽��ʵ��Ϊ�ܱ����ģ��������Ҫ����չ��Ҳ����ʵ��Ϊ˽�е�
	Singleton()
	{
		cout << "A old style singleton constructor" << endl;
	}

private:
	//һ��˽�еľ�̬��Ա
	static Singleton * _instance;

public:
	//���е�Singleton���������ظ����Ψһʵ��
	static Singleton * Instance()
	{
		if (NULL == _instance)
		{
			//����(lazy)��ʼ����ֻ��ʹ��ʱ�ų�ʼ��
			_instance = new Singleton();
		}
		return _instance;
	}

	void Display()
	{
		cout << "Old singleton display" << endl;
	}
};

Singleton * Singleton::_instance = NULL;		//��ʼ��Ϊ��ָ��



//Effective C++�Ͻ��ܵ��µ�Singletonд��
class NewSingleton
{
private:
	NewSingleton()
	{
		cout << "New style singleton constructor" << endl;
	}

public:
	/*
		�µ�д��ʡ���˼��NULL==_instance�Ĺ��̣�����Ч�ʸ���
		���Ҽ�����ʵ�ֵ����Ĵ�����
		����̫���ˣ�
	*/
	static NewSingleton& Instance()
	{
		static NewSingleton _instance;
		return _instance;
	}

	void Display()
	{
		cout << "New singleton display" << endl;
	}
};

void main()
{
	Singleton::Instance()->Display();
	Singleton::Instance()->Display();
	Singleton::Instance()->Display();
	Singleton::Instance()->Display();
	Singleton::Instance()->Display();
	Singleton::Instance()->Display();	

	NewSingleton::Instance().Display();
	NewSingleton::Instance().Display();
	NewSingleton::Instance().Display();
	NewSingleton::Instance().Display();
	NewSingleton::Instance().Display();
	NewSingleton::Instance().Display();
}