#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <typeinfo>
#include <exception>
#include <stdexcept>
#include <loki/MultiMethods.h>
using namespace std;
using namespace Loki;



struct LhsBase {virtual ~LhsBase(){}};
struct LhsDevied : public LhsBase {};
struct RhsBase {virtual ~RhsBase(){}};
struct RhsDevied : public RhsBase {};





struct StaticDispatchFirer
{
	void Fire(LhsBase&, RhsBase&)
	{
		cout << "void StaticFire(LhsBase&, RhsBase&) " << endl;
	}
	void Fire(LhsBase&, RhsDevied&)
	{
		cout << "void StaticFire(LhsBase&, RshDevied&)" << endl;
	}
	void Fire(LhsDevied&, RhsBase&)
	{
		cout << "void StaticFire(LshDevied&, RhsBase&)" << endl;
	}
	void Fire(LhsDevied&, RhsDevied&)
	{
		cout << "void StaticFire(LshDevied&, RshDevied&)" << endl;
	}
	void OnError(LhsBase&, RhsBase&)
	{
		cout << "void StaticOnError(LhsBase&, RhsBase&)" << endl;
	}
};
void StaticDispatcherTest()
{
	StaticDispatcher<StaticDispatchFirer,
					 LhsBase,
					 LOKI_TYPELIST_2(LhsBase, LhsDevied),
					 false,
					 RhsBase,
					 LOKI_TYPELIST_2(RhsBase, RhsDevied),
					 void> dispatcher;
	LhsBase lb;
	LhsDevied ld;
	RhsBase rb;
	RhsDevied rd;
	StaticDispatchFirer firer;

	dispatcher.Go(lb, rb, firer);
	dispatcher.Go(lb, rd, firer);
	dispatcher.Go(ld, rb, firer);
	dispatcher.Go(ld, rd, firer);
}



void BasicCall1(LhsBase&, RhsBase&)
{
	// Should manual do dynamic_cast at first.
	cout << "void BasicCall1(LhsBase&, RhsBase&) " << endl;
}
void BasicCall2(LhsBase&, RhsBase&)
{
	// Should manual do dynamic_cast at first.
	cout << "void BasicCall2(LhsBase&, RshDevied&)" << endl;
}
void BasicCall3(LhsBase&, RhsBase&)
{
	// Should manual do dynamic_cast at first.
	cout << "void BasicCall3(LshDevied&, RhsBase&)" << endl;
}
void BasicCall4(LhsBase&, RhsBase&)
{
	// Should manual do dynamic_cast at first.
	cout << "void BasicCall4(LshDevied&, RshDevied&)" << endl;
}
// BasicDispatcher最大的弱点在于：注册的Call函数都只能接受LhsBase,RhsBase的参数，
// 并需要在函数内部进行手动的dynamic_cast到正确的类别。
void BasicDispatcherTest()
{
	BasicDispatcher<LhsBase, RhsBase, void> dispatcher;
	dispatcher.Add<LhsBase, RhsBase>(BasicCall1);
	dispatcher.Add<LhsBase, RhsDevied>(BasicCall2);
	dispatcher.Add<LhsDevied, RhsBase>(BasicCall3);
	dispatcher.Add<LhsDevied, RhsDevied>(BasicCall4);

	LhsBase lb;
	LhsDevied ld;
	RhsBase rb;
	RhsDevied rd;

	dispatcher.Go(lb, rb);
	dispatcher.Go(lb, rd);
	dispatcher.Go(ld, rb);
	dispatcher.Go(ld, rd);
}



void FnCall1(LhsBase&, RhsBase&)
{
	// Should manual do dynamic_cast at first.
	cout << "void FnCall1(LhsBase&, RhsBase&) " << endl;
}
void FnCall2(LhsBase&, RhsDevied&)
{
	// Should manual do dynamic_cast at first.
	cout << "void FnCall2(LhsBase&, RshDevied&)" << endl;
}
void FnCall3(LhsDevied&, RhsBase&)
{
	// Should manual do dynamic_cast at first.
	cout << "void FnCall3(LshDevied&, RhsBase&)" << endl;
}
void FnCall4(LhsDevied&, RhsDevied&)
{
	// Should manual do dynamic_cast at first.
	cout << "void FnCall4(LshDevied&, RshDevied&)" << endl;
}
// FnDispatcher已经比较好用了，而且trampoline function并不会增加
// 额外的开销，最关键还是类型安全的，所以这种方式我应该知道并融会贯通！
// 还应当注意的是：FnDispatcher的后端就是BasicDispatcher，
// 它的弱点在于：它只能接受函数指针而不能接受仿函数！(因为它的Add函数的第3个模板参数要求具有外部连接的函数指针）
void FnDispatcherTest()
{
	FnDispatcher<LhsBase, RhsBase, void> dispatcher;
	dispatcher.Add<LhsBase, RhsBase, FnCall1>();
	dispatcher.Add<LhsBase, RhsDevied, FnCall2>();
	dispatcher.Add<LhsDevied, RhsBase, FnCall3>();
	dispatcher.Add<LhsDevied, RhsDevied, FnCall4>();

	LhsBase lb;
	LhsDevied ld;
	RhsBase rb;
	RhsDevied rd;

	dispatcher.Go(lb, rb);
	dispatcher.Go(lb, rd);
	dispatcher.Go(ld, rb);
	dispatcher.Go(ld, rd);
}






struct FunctorCall1
{
	void operator()(LhsBase&, RhsBase&)
	{
		cout << "void FunctorCall(LhsBase&, RhsBase&) " << endl;
	}
};
struct FunctorCall2
{
	void operator()(LhsBase&, RhsDevied&)
	{
		cout << "void FunctorCall(LhsBase&, RshDevied&)" << endl;
	}
};
struct FunctorCall3
{
	void operator()(LhsDevied&, RhsBase&)
	{
		cout << "void FunctorCall(LshDevied&, RhsBase&)" << endl;
	}
};
struct FunctorCall4
{
	void operator()(LhsDevied&, RhsDevied&)
	{
		cout << "void FunctorCall(LshDevied&, RshDevied&)" << endl;
	}
};
// FunctorDispatcher已经基本完美了，不仅使用方便，是类型安全的，而且还可以接受仿函数，这已经太好了！
// 唯一的缺点是：它和FnDispatcher正好相反，它不能接受普通函数指针。
// 所以把FcDispatcher和FunctorDispatcher配合使用才是真正的完美！
void FunctorDispatcherTest()
{
	FunctorDispatcher<LhsBase, RhsBase, void> dispatcher;
	dispatcher.Add<LhsBase, RhsBase>(FunctorCall1());
	dispatcher.Add<LhsBase, RhsDevied>(FunctorCall2());
	dispatcher.Add<LhsDevied, RhsBase>(FunctorCall3());
	dispatcher.Add<LhsDevied, RhsDevied>(FunctorCall4());

	LhsBase lb;
	LhsDevied ld;
	RhsBase rb;
	RhsDevied rd;

	dispatcher.Go(lb, rb);
	dispatcher.Go(lb, rd);
	dispatcher.Go(ld, rb);
	dispatcher.Go(ld, rd);
}



void chapter11()
{
	StaticDispatcherTest();
	cout << endl;
	BasicDispatcherTest();
	cout << endl;
	FnDispatcherTest();
	cout << endl;
	FunctorDispatcherTest();
}
