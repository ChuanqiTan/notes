/*
 * chapter3.h
 *
 *  Created on: 2012-7-15
 *      Author: chuanqi
 */


#include <exception>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <loki/Typelist.h>
#include <loki/HierarchyGenerators.h>
using namespace std;
using namespace Loki;
using namespace Loki::TL;

template<typename T>
struct Holder {
	T value;
};

template<typename T, class Base>
struct LineHolder : public Base {
	T value;
};


void chapter3(){
	typedef LOKI_TYPELIST_3(int, double, char) MyTypeLists1;
	cout << Length<MyTypeLists1>::value << endl;
	cout << typeid(TypeAt<MyTypeLists1, 2>::Result).name() << endl;
	cout << IndexOf<MyTypeLists1, double>::value << endl;
	typedef Erase<Append<MyTypeLists1, exception>::Result, exception>::Result MyTypeLists2;
	typedef NoDuplicates<MyTypeLists2>::Result MyTypeLists3;
	typedef Append<Append<MyTypeLists3, exception>::Result, runtime_error>::Result MyTypeLists4;
	cout << typeid(MostDerived<MyTypeLists4, exception>::Result).name() << endl;
	typedef DerivedToFront<MyTypeLists4>::Result MyTypeLists5;
	cout << typeid(MyTypeLists5).name() << endl;

	typedef GenScatterHierarchy<MyTypeLists1, Holder> MyHolderClasses;
	MyHolderClasses my;
	Field<int>(my).value = 3;
	Field<double>(my).value = 8.8;
	Field<2>(my).value = 'b';
	cout << Field<int>(my).value << ", " << Field<double>(my).value << ", " << Field<char>(my).value << endl;
	cout << Field<0>(my).value << ", " << Field<1>(my).value << ", " << Field<2>(my).value << endl;

	typedef GenLinearHierarchy<MyTypeLists1, LineHolder> MyHolderClasses2;
	MyHolderClasses2 my2;
//	Field<int>(my2).value = 3;
//	Field<double>(my2).value = 8.8;
//	Field<2>(my2).value = 'b';
//	cout << Field<int>(my2).value << ", " << Field<double>(my2).value << ", " << Field<char>(my2).value << endl;
//	cout << Field<0>(my2).value << ", " << Field<1>(my2).value << ", " << Field<2>(my2).value << endl;

	Tuple<LOKI_TYPELIST_3(int, double, char)> my_tuple;
	Field<0>(my_tuple) = 0;
	Field<1>(my_tuple) = 1.1;
	Field<2>(my_tuple) = 'c';
	cout << Field<0>(my_tuple) << ", " << Field<1>(my_tuple) << ", " << Field<2>(my_tuple) << endl;
}
