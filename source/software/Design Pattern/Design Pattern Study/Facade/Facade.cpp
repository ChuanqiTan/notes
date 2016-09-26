// Facade.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;


//ɨ����
class Scanner
{
public:
	string Scan(string file_name)
	{
		cout << "Scanner scan file : " << file_name << endl;
		return "Scan Result";
	}
};

//Ԥ������
class PreCopeer
{
public:
	void PreCope(string to_precope)
	{
		cout << "PreCoper do precope" << endl;
	}

};

//������
class Complier
{
public:
	string Complie(string to_complie)
	{
		cout << "Complier do complie" << endl;
		return "Complie Result";
	}
};

//������
class Linker
{
public:
	string Link(string to_link)
	{
		cout << "Linker do link" << endl;
		return "A execute file";
	}
};

//����ϵͳ�����
class ComplieSystemFacade
{
public:
	string DoComplie(string file_name)
	{
		/*
		����Ĺ��̣�ɨ����ţ���Ԥ���������룭������
		*/
		Scanner *scanner = new Scanner();
		PreCopeer *precopeer = new PreCopeer();
		Complier *complier = new Complier();
		Linker *linker = new Linker();

		string scan_result = scanner->Scan(file_name);
		precopeer->PreCope(scan_result);
		string complie_result = complier->Complie(scan_result);
		string linke_result = linker->Link(complie_result);

		delete scanner;
		delete precopeer;
		delete complier;
		delete linker;
		return linke_result;
	}
};


void main()
{
	ComplieSystemFacade *facade = new ComplieSystemFacade();
	//����Facade�ṩ�ķ������Ը������ʹ��ϵͳ
	facade->DoComplie("abc.cpp");
	delete facade;
}
