
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

#include <loki/TypelistMacros.h>
#include <loki/AbstractFactory.h>

class C {
 public:
  virtual ~C() {
  }
  virtual void Do(int) = 0;
  virtual void Do(double) = 0;
  virtual void Do(std::string) = 0;
  virtual C* Clone() = 0;
};

class CA : public C {
 public:
  virtual void Do(int) {
    cout << "Do(int)" << endl;
  }
  virtual void Do(double) {
    cout << "Do(double)" << endl;
  }
  virtual void Do(std::string) {
    cout << "Do(std::string)" << endl;
  }
  virtual CA* Clone(){
    return new CA();
  }
};

// Use OpNewFactoryUnit.
typedef Loki::AbstractFactory<LOKI_TYPELIST_3(int, double, C)> AbstractFactory1;
class MyManualFactory : public AbstractFactory1 {
 public:
  virtual int* DoCreate(Loki::Type2Type<int>){return new int();}
  virtual double* DoCreate(Loki::Type2Type<double>){return new double();}
  virtual CA* DoCreate(Loki::Type2Type<C>){
    return new CA();
  }
};
typedef Loki::ConcreteFactory<AbstractFactory1, Loki::OpNewFactoryUnit, LOKI_TYPELIST_3(int, double, CA)> AutoFactory;

// Use PrototypeFactoryUnit.
typedef Loki::AbstractFactory<LOKI_TYPELIST_1(C)> AbstractFactory2;
typedef Loki::ConcreteFactory<AbstractFactory2, Loki::PrototypeFactoryUnit> PrototypeFacroty;


void chapter9() {
  AbstractFactory1 *af = new MyManualFactory();
  cout << *(af->Create<int>()) << endl;
  cout << *(af->Create<double>()) << endl;
  af = new AutoFactory();
  cout << *(af->Create<int>()) << endl;
  cout << *(af->Create<double>()) << endl;

  PrototypeFacroty *pf = new PrototypeFacroty();
  pf->SetPrototype<C>(new CA());     // set prototype.
  AbstractFactory2 *af2 = pf;
  af2->Create<C>()->Do(1.1);
}

