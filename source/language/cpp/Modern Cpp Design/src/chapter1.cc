#include <iostream>
using namespace std;

namespace {

class SimplyWelcomePolicy{
public:
	static void ShowWelcome(){
		cout << "Welcome!" << endl;
	}
};
class ComplexWelcomPolicy{
public:
	static void ShowWelcome(){
		cout << "*************************************" << endl;
		cout << "*                                   *" << endl;
		cout << "*   You are welcome to this game!!  *" << endl;
		cout << "*                                   *" << endl;
		cout << "*************************************" << endl;
	}
};
template<typename WelcomePolicy>
class Game{
public:
	Game(){}
	void BeginGame(){
		WelcomePolicy::ShowWelcome();
	}
};
void PolicyTest(){
	// Policy，我对它的最简短、最直接、最透彻的理解就是可以视为一个编译期的Strategy!!!
	// C++ Templates中区分Policy和Traits时说：Policy侧重行为；而Traits侧重类型
	// 而行为就是Strategy模式要解决的问题，所以我想把Policy视为编译期的Strategy是有助于理解Policy的。
	Game<SimplyWelcomePolicy> game1;
	game1.BeginGame();
	Game<ComplexWelcomPolicy> game2;
	game2.BeginGame();
}



//迭代器的5种分类
struct InputIterator{};
struct OutputIterator{};
struct ForwardIterator : public InputIterator{};
struct BidirectionalIterator : public ForwardIterator{};
struct RandomIteratorIterator : public BidirectionalIterator{};

//类别分别归为5类的迭代器
template<typename T>
struct InIterator
{
	typedef InputIterator iterator_category;
};

template<typename T>
struct OutIterator
{
	typedef OutputIterator iterator_category;
};

template<typename T>
struct ListIterator
{
	typedef ForwardIterator iterator_category;
};

template<typename T>
struct BidirectListIterator
{
	typedef BidirectionalIterator iterator_category;
};

template<typename T>
struct VectorIterator
{
	typedef RandomIteratorIterator iterator_category;
};


//类型Traits
template<typename T>
struct IteratorTraits
{
	typedef typename T::iterator_category iterator_category;
};
//这个偏特化是为了解决和原生指针的兼容性，如果不需要和原生指针的兼容性，真正的traits类在Traits体系中
//的必要性是否应打一个问号？毕竟可以在ShowIteratorType里使用T::iterator_category直接来
template<typename T>
struct IteratorTraits<T *>
{
	typedef RandomIteratorIterator iterator_category;
};


//5个针对不同类型的函数重载
//函数重载简直就是编译期的if选择分支
template<typename T>
void Show(T &, InputIterator)
{
	cout << "I am a InputIterator" << endl;
}

template<typename T>
void Show(T &, OutputIterator)
{
	cout << "I am a OutputIterator" << endl;
}

template<typename T>
void Show(T &, ForwardIterator)
{
	cout << "I am a ForwardIterator" << endl;
}

template<typename T>
void Show(T &, BidirectionalIterator)
{
	cout << "I am a BidirectionalIterator" << endl;
}

template<typename T>
void Show(T &, RandomIteratorIterator)
{
	cout << "I am a RandomIteratorIterator" << endl;
}


// 这才是惟一公开的函数，会根据迭代器的类别采取不同的措施
// !!! 一个BUG !!!
// 为什么这里一定要加这个const写成ShowIteratorType(T const &t)，理论上不加也应该可以啊，这样的话T就是InIterator<int> const类型，不可以吗？
// 经过测试，如果这里不加const，的话，显式的指定函数模板类型才可以调用成功：ShowIteratorType<InIterator<int> const>(InIterator<int>());
// 为什么不能正确的推导为InIterator<int> const类型呢？但是MSVC10就可以正确的推导，看来GCC4.6.2的实参演绎有问题啊！
template<typename T>
void ShowIteratorType(T const &t)
{
	//Show(t, T::iterator_category());	//如果不需要兼容指针，Traits体系就可以不需要真正的Traits类
	Show(t, typename IteratorTraits<T>::iterator_category());
}

void TraitsTest()
{
	ShowIteratorType(InIterator<int>());
	ShowIteratorType(OutIterator<int>());
	ShowIteratorType(ListIterator<int>());
	ShowIteratorType(BidirectListIterator<int>());
	ShowIteratorType(VectorIterator<int>());
	int *p;
	ShowIteratorType(p);		//由于traits的偏特化而实现与指针的兼容
}


} // end of anonymous-namespace.


void chapter1(){
	PolicyTest();
	TraitsTest();
}
