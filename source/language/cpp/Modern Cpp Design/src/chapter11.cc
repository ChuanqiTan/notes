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
// BasicDispatcher�����������ڣ�ע���Call������ֻ�ܽ���LhsBase,RhsBase�Ĳ�����
// ����Ҫ�ں����ڲ������ֶ���dynamic_cast����ȷ�����
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
// FnDispatcher�Ѿ��ȽϺ����ˣ�����trampoline function����������
// ����Ŀ�������ؼ��������Ͱ�ȫ�ģ��������ַ�ʽ��Ӧ��֪�����ڻ��ͨ��
// ��Ӧ��ע����ǣ�FnDispatcher�ĺ�˾���BasicDispatcher��
// �����������ڣ���ֻ�ܽ��ܺ���ָ������ܽ��ܷº�����(��Ϊ����Add�����ĵ�3��ģ�����Ҫ������ⲿ���ӵĺ���ָ�룩
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
// FunctorDispatcher�Ѿ����������ˣ�����ʹ�÷��㣬�����Ͱ�ȫ�ģ����һ����Խ��ܷº��������Ѿ�̫���ˣ�
// Ψһ��ȱ���ǣ�����FnDispatcher�����෴�������ܽ�����ͨ����ָ�롣
// ���԰�FcDispatcher��FunctorDispatcher���ʹ�ò���������������
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
