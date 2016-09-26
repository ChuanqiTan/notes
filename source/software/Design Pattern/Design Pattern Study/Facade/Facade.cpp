// Facade.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;


//扫描器
class Scanner
{
public:
	string Scan(string file_name)
	{
		cout << "Scanner scan file : " << file_name << endl;
		return "Scan Result";
	}
};

//预处理器
class PreCopeer
{
public:
	void PreCope(string to_precope)
	{
		cout << "PreCoper do precope" << endl;
	}

};

//编译器
class Complier
{
public:
	string Complie(string to_complie)
	{
		cout << "Complier do complie" << endl;
		return "Complie Result";
	}
};

//链接器
class Linker
{
public:
	string Link(string to_link)
	{
		cout << "Linker do link" << endl;
		return "A execute file";
	}
};

//编译系统的外观
class ComplieSystemFacade
{
public:
	string DoComplie(string file_name)
	{
		/*
		编译的过程：扫描符号－－预处理－－编译－－链接
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
	//调用Facade提供的方法可以更方便的使用系统
	facade->DoComplie("abc.cpp");
	delete facade;
}
