#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <typeinfo>
#include <exception>
#include <stdexcept>
#include <loki/static_check.h>
#include <loki/TypeManip.h>
#include <loki/LokiTypeInfo.h>
#include <loki/TypeTraits.h>
using namespace std;
using namespace Loki;


namespace {


void StaticAssertTest() {
  LOKI_STATIC_CHECK(true, This_is_a_static_assert_message);

  // Will cause compile time error when first argument is "false".
//  LOKI_STATIC_CHECK(false, Oh_error_on_static_assert_on_compile_time);
}



void IntegerOverload(){
	cout << "Call IntegerOverload by overload with no argument" << endl;
}
void IntegerOverload(Int2Type<1>){
	cout << "Call IntegerOverload by overload Int2Type<1>" << endl;
}
void IntegerOverload(Int2Type<2>){
	cout << "Call IntegerOverload by overload Int2Type<2>" << endl;
}
//////////////////////////////////////////////////////////////////
/// Type2Type这种类对类的映射可以使得在C++11之前的不支持函数偏特化的编译器中模拟函数的偏特化。
///////////////////////////////////////////////////////////////////
void TypeOverload(){
	cout << "Call TypeOverload by overload with no argument" << endl;
}
void TypeOverload(Type2Type<vector<int>>){
	cout << "Call TypeOverload by Type2Type<int> with no expenses" << endl;
}
void TypeOverload(Type2Type<vector<string>>){
	cout << "Call TypeOverload by Type2Type<string> with no expenses" << endl;
}
void TypeOverload(vector<int>&){
	cout << "使用引用的形式来进行重载也能消除拷贝可能引起的重量级拷贝开销" << endl;
}
void TypeOverload(vector<string>&){
	cout << "使用引用的形式来进行重载也能消除拷贝可能引起的重量级拷贝开销" << endl;
}
void TypeMappingTest() {
	IntegerOverload();
	IntegerOverload(Int2Type<1>());
	IntegerOverload(Int2Type<2>());

	vector<int> vec_int;
	vector<string> vec_str;
	TypeOverload();
	TypeOverload(Type2Type<vector<int>>());
	TypeOverload(Type2Type<vector<string>>());
	TypeOverload(vec_int);
	TypeOverload(vec_str);
}



void SelectTest(){
	cout << typeid(Select<true, int, double>::Result).name() << endl;
	cout << typeid(Select<false, int, double>::Result).name() << endl;
}


void ConversionTest(){
	cout << boolalpha << (bool)(Conversion<int, double>::exists) << endl;
	cout << boolalpha << (bool)(Conversion<int, double>::exists2Way) << endl;
	cout << boolalpha << (bool)(Conversion<int, int>::sameType) << endl;

	cout << boolalpha << (bool)(LOKI_SUPERSUBCLASS(exception, runtime_error)) << endl;
	cout << boolalpha << (bool)(LOKI_SUPERSUBCLASS(exception, exception)) << endl;
	cout << boolalpha << (bool)(LOKI_SUPERSUBCLASS_STRICT(exception, exception)) << endl;
}


void TypeInfoTest(){
	cout << boolalpha << typeid(exception).name() << endl;
	cout << boolalpha << typeid(runtime_error).name() << endl;
	cout << boolalpha << typeid(exception).before(typeid(runtime_error)) << endl;
	cout << boolalpha << typeid(runtime_error).before(typeid(exception)) << endl;

	TypeInfo info1 = typeid(exception);
	TypeInfo info2 = typeid(runtime_error);
	cout << info1.name() << endl;
	cout << info2.name() << endl;
	cout << boolalpha << info1.before(info2) << endl;
	cout << boolalpha << info2.before(info1) << endl;
}


void TypeTraitsTest(){
	cout << boolalpha << (bool)Loki::TypeTraits<int*>::isPointer << endl;
	cout << boolalpha << (bool)Loki::TypeTraits<int>::isReference << endl;
	cout << boolalpha << (bool)Loki::TypeTraits<int&>::isReference << endl;
	cout << boolalpha << typeid(Loki::TypeTraits<int>::ParameterType).name() << endl;
	cout << boolalpha << typeid(Loki::TypeTraits<int*>::ParameterType).name() << endl;
	cout << boolalpha << typeid(Loki::TypeTraits<int&>::ParameterType).name() << endl;
	cout << boolalpha << (bool)Loki::TypeTraits<int>::isStdFundamental << endl;
	cout << boolalpha << (bool)Loki::TypeTraits<int>::isStdSignedInt << endl;
	cout << boolalpha << (bool)Loki::TypeTraits<int>::isStdUnsignedInt << endl;
}


} // end of anonymous-namespace.



void chapter2(){
  StaticAssertTest();
  TypeMappingTest();
  SelectTest();
  ConversionTest();
  TypeInfoTest();
  TypeTraitsTest();
}
