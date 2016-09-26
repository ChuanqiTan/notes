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
	// Policy���Ҷ��������̡���ֱ�ӡ���͸���������ǿ�����Ϊһ�������ڵ�Strategy!!!
	// C++ Templates������Policy��Traitsʱ˵��Policy������Ϊ����Traits��������
	// ����Ϊ����StrategyģʽҪ��������⣬���������Policy��Ϊ�����ڵ�Strategy�����������Policy�ġ�
	Game<SimplyWelcomePolicy> game1;
	game1.BeginGame();
	Game<ComplexWelcomPolicy> game2;
	game2.BeginGame();
}



//��������5�ַ���
struct InputIterator{};
struct OutputIterator{};
struct ForwardIterator : public InputIterator{};
struct BidirectionalIterator : public ForwardIterator{};
struct RandomIteratorIterator : public BidirectionalIterator{};

//���ֱ��Ϊ5��ĵ�����
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


//����Traits
template<typename T>
struct IteratorTraits
{
	typedef typename T::iterator_category iterator_category;
};
//���ƫ�ػ���Ϊ�˽����ԭ��ָ��ļ����ԣ��������Ҫ��ԭ��ָ��ļ����ԣ�������traits����Traits��ϵ��
//�ı�Ҫ���Ƿ�Ӧ��һ���ʺţ��Ͼ�������ShowIteratorType��ʹ��T::iterator_categoryֱ����
template<typename T>
struct IteratorTraits<T *>
{
	typedef RandomIteratorIterator iterator_category;
};


//5����Բ�ͬ���͵ĺ�������
//�������ؼ�ֱ���Ǳ����ڵ�ifѡ���֧
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


// �����Ωһ�����ĺ���������ݵ�����������ȡ��ͬ�Ĵ�ʩ
// !!! һ��BUG !!!
// Ϊʲô����һ��Ҫ�����constд��ShowIteratorType(T const &t)�������ϲ���ҲӦ�ÿ��԰��������Ļ�T����InIterator<int> const���ͣ���������
// �������ԣ�������ﲻ��const���Ļ�����ʽ��ָ������ģ�����Ͳſ��Ե��óɹ���ShowIteratorType<InIterator<int> const>(InIterator<int>());
// Ϊʲô������ȷ���Ƶ�ΪInIterator<int> const�����أ�����MSVC10�Ϳ�����ȷ���Ƶ�������GCC4.6.2��ʵ�����������Ⱑ��
template<typename T>
void ShowIteratorType(T const &t)
{
	//Show(t, T::iterator_category());	//�������Ҫ����ָ�룬Traits��ϵ�Ϳ��Բ���Ҫ������Traits��
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
	ShowIteratorType(p);		//����traits��ƫ�ػ���ʵ����ָ��ļ���
}


} // end of anonymous-namespace.


void chapter1(){
	PolicyTest();
	TraitsTest();
}
