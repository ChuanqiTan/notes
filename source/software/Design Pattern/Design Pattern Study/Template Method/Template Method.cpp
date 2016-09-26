// Template Method.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;


class AbstractGenerator
{
public:
	//�����һ��Template Method����������һ���㷨�Ŀ��
	void Display()
	{
		//��ģ�巽�������ǵ����˶�����������������㷨���
		//��ʵ����һ���ǳ��ǳ��������������ķ�����ƽʱ��������ж��ù�̫���
		if (CalcuteFileSize() > 100)
		{
			DisplayBigFile();
		}
		else
		{
			DisplaySmallFile();
		}
	}


protected:	//��������Ӧ�����ܱ�����

	//��������
	virtual int CalcuteFileSize() = 0;

	//��������
	virtual void DisplayBigFile()
	{
		cout << "This is a big file" << endl;
	}

	//��������
	virtual void DisplaySmallFile()
	{
		cout << "This is a small file" << endl;
	}
};

class ConcreteGenerator : public AbstractGenerator
{
public:
	ConcreteGenerator(int s) 
		: _size(s){}

	virtual int CalcuteFileSize()
	{
		//read a file
		//return this file's size
		return _size;	
	}

	virtual void DisplayBigFile()
	{
		cout << "Oh~~~  a big file" << endl;
	}

private:
	int _size;
};


void main()
{	
	AbstractGenerator *g1 = new ConcreteGenerator(20);
	g1->Display();

	AbstractGenerator *g2 = new ConcreteGenerator(200);
	g2->Display();
}

