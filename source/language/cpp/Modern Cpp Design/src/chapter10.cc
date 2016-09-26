#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <typeinfo>
#include <exception>
#include <stdexcept>
#include <loki/Visitor.h>
using namespace std;
using namespace Loki;


namespace acyclic_visitor {


class MyClassBase;
class MyClass1;
class MyClass2;

class MyVisitorBase {
public:
	virtual ~MyVisitorBase() {}
};

class MyClass1Visitor {
public:
	virtual ~MyClass1Visitor() {}
	virtual void VisitorMyClass1(MyClass1 *c) = 0;
};

class MyClass2Visitor {
public:
	virtual ~MyClass2Visitor() {}
	virtual void VisitorMyClass2(MyClass2 *c) = 0;
};

class MyClassAllVisitor : public MyVisitorBase
						, public MyClass1Visitor
						, public MyClass2Visitor {
public:
	virtual void VisitorMyClass1(MyClass1 *c) {
		cout << "MyClassAllVisitor visit a MyClass1" << endl;
	}

	virtual void VisitorMyClass2(MyClass2 *c) {
		cout << "MyClassAllVisitor visit a MyClass2" << endl;
	}

};

class MyClassBase {
public:
	virtual ~MyClassBase() {}
	virtual void Accept(MyVisitorBase *visitor) = 0;
};

class MyClass1 : public MyClassBase {
public:
	virtual void Accept(MyVisitorBase *visitor) {
		if (MyClass1Visitor *p1v = dynamic_cast<MyClass1Visitor*>(visitor)) {
			p1v->VisitorMyClass1(this);
		}
	}
};

class MyClass2 : public MyClassBase {
public:
	virtual void Accept(MyVisitorBase *visitor) {
		if (MyClass2Visitor *p2v = dynamic_cast<MyClass2Visitor*>(visitor)) {
			p2v->VisitorMyClass2(this);
		}
	}
};

/*!
 * 手工实现Acylic Visitor模式
 */
void ManualImplementAcyclicVisitor() {
	MyClass1 mc1;
	MyClass2 mc2;
	MyClassAllVisitor mv;
	mc1.Accept(&mv);
	mc2.Accept(&mv);
}


} // end of acyclic_visitor-namespace.



///////////////////////////////////////////////////
///    Use Loki to implement Acyclic-Visitor    ///
///////////////////////////////////////////////////
class MyClassBase : public BaseVisitable<> {
public:
	virtual ~MyClassBase() {}
	LOKI_DEFINE_VISITABLE()
};

class MyClass1 : public MyClassBase {
public:
	LOKI_DEFINE_VISITABLE()
};

class MyClass2 : public MyClassBase {
public:
	LOKI_DEFINE_VISITABLE()
};

class MyClassAllVisitor : public BaseVisitor
						, public Visitor<MyClass1>
						, public Visitor<MyClass2> {
public:
	virtual void Visit(MyClass1 &c) {
		cout << "MyClassAllVisitor visit a MyClass1" << endl;
	}

	virtual void Visit(MyClass2 &c) {
		cout << "MyClassAllVisitor visit a MyClass2" << endl;
	}
};


void chapter10() {
	cout << "Manual Implement Acyclic-Visitor Pattern" << endl;
	acyclic_visitor::ManualImplementAcyclicVisitor();

	cout << endl << "Loki Implement Acyclic-Visitor Pattern" << endl;
	MyClassAllVisitor v;
	MyClass1 mc1;
	MyClass2 mc2;
	mc1.Accept(v);
	mc2.Accept(v);
}
