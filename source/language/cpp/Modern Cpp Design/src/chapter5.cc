/*
 * chapter5.cc
 *
 *  Created on: 2012-7-16
 *      Author: chuanqi
 */


#include <exception>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <loki/Functor.h>
using namespace std;
using namespace Loki;

void NormalFunction() {
	cout << "void NormalFunction()" << endl;
}

void NormalFunction2(int){
	cout << "void NormalFunction2(int)" << endl;
}

struct SomeFunctor {
	void operator()() {
		cout << "void SomeFunctor::operator()()" << endl;
	}
};

struct SomeClass {
	void MemberFunction() {
		cout << "void SomeClass::MemberFunction()" << endl;
	}
};

void chapter5(){
	// 可调用体
	typedef Functor<void> FnType;
	vector<FnType> fns;
	fns.push_back(NormalFunction);
	SomeFunctor sf;
	fns.push_back(sf);
	SomeClass sc;
	FnType member_cmd(&sc, &SomeClass::MemberFunction);
	fns.push_back(member_cmd);

	// Chain()
	fns.push_back(Chain(FnType(NormalFunction), member_cmd));
	// BindFirst()
	fns.push_back(BindFirst(Functor<void, LOKI_TYPELIST_1(int)>(NormalFunction2), 66));

	for (size_t i = 0; i < fns.size(); ++i) {
		fns[i]();
	}
}
