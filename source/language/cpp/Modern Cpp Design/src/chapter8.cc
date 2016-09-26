/*
 * chapter8.cc
 *
 *  Created on: 2012-7-17
 *      Author: chuanqi
 */




#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <loki/Factory.h>
using namespace std;
using namespace Loki;



exception* CreateNormalException() {
	return new exception();
}

class MyException : public exception {
public:
	explicit MyException(string const &msg) : msg_(msg) {
	}

	virtual ~MyException() throw() {
	}

	virtual char const * what() const throw() {
		return (std::string("Hello Factory : ") + msg_).c_str();
	}
	static exception * CreateFactorRegisiterToFactory() {
		return new MyException("Default");
	}

	string msg_;
};

exception * CloneMyException(exception const *ex) {
	MyException const *mex = dynamic_cast<MyException const*>(ex);
	return new MyException(mex->msg_ + " by Clone");
}




void chapter8() {
	Factory<exception, string> f;

	f.Register("exception", CreateNormalException);
	f.Register("MyException", MyException::CreateFactorRegisiterToFactory);

	exception *pe1 = f.CreateObject("MyException");
	exception *pe2 = f.CreateObject("exception");
	cout << pe1->what() << endl;
	cout << pe2->what() << endl;

	delete pe1;
	delete pe2;


	CloneFactory<exception> cf;
	MyException mye("ForCloneFactory");
	cf.Register(typeid(mye), CloneMyException);
	exception *pce1 = cf.CreateObject(&mye);
	cout << pce1->what() << endl;
	delete pce1;

}
