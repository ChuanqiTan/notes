/*
 * chapter6.cc
 *
 *  Created on: 2012-7-16
 *      Author: chuanqi
 */




#include <exception>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <loki/Singleton.h>
using namespace std;
using namespace Loki;



/// Singleton Base Class
/// 这是我平时用的简易的Singleton手法，在单线程下似乎是安全的。
template<typename T>
class Singleton
{
public:
    static inline T & Instance()
    {
        static T instance;
        return instance;
    }

protected:
    Singleton() {}
    ~Singleton() {}	// protected de-constructor function NOT need to be virtual.

private:
    /// Disable.
    Singleton( Singleton const & );
    /// Disable.
    Singleton & operator=( Singleton const & );
};

class Language : public ::Singleton<Language> {
	friend class Singleton;
	Language() {}
public:
	void ShowLanguage() {
		cout << "Current language is English." << endl;
	}
};




class Configure {
public:
	void Show() {
		for (int i = 0; i < 3; ++i) {
			cout << "configure pair : <key, value>" << endl;
		}
	}
};




void chapter6() {
	// Loki定义的Singleton模式，是指这个typedef ... SingleConfigure只能是Singleton的
	// 而不是指Configure，以往我实现的Singleton都是直接针对Configure限制一个实例的，注意区别。
	typedef SingletonHolder<Configure> SingleConfigure;
	SingleConfigure::Instance().Show();

	// ERROR
//	SingleConfigure *pconfig = new SingleConfigure();
//	SingleConfigure config;

	Language::Instance().ShowLanguage();  // 我平常用的Singleton实现手法的调用方式
}
