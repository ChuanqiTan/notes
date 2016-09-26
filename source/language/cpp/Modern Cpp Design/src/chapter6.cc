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
/// ������ƽʱ�õļ��׵�Singleton�ַ����ڵ��߳����ƺ��ǰ�ȫ�ġ�
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
	// Loki�����Singletonģʽ����ָ���typedef ... SingleConfigureֻ����Singleton��
	// ������ָConfigure��������ʵ�ֵ�Singleton����ֱ�����Configure����һ��ʵ���ģ�ע������
	typedef SingletonHolder<Configure> SingleConfigure;
	SingleConfigure::Instance().Show();

	// ERROR
//	SingleConfigure *pconfig = new SingleConfigure();
//	SingleConfigure config;

	Language::Instance().ShowLanguage();  // ��ƽ���õ�Singletonʵ���ַ��ĵ��÷�ʽ
}
