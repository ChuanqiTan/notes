/**
 * @file     hash_table.cpp
 * @brief    散列表
 *
 * Distributed under the GPL License version 3, see: http://www.gnu.org/licenses
 * Author: chuanqi.tan(at)gmail.com
 */


#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
using namespace std;


namespace ita {
/// @brief Noraml Hash Table
template<typename T>
class HashTable {
  struct Node {
    T     value;
    Node  *pre;
    Node  *next;
  };

public:
  explicit HashTable(int n) : data_(n, nullptr) {
  }    

  ~HashTable() {
    for (Node *n : data_) {
      while (n) {
        Node *p = n;
        n = n->next;
        delete p;
      }
    }
  }

  Node* Find(T const &v) {
    Node *p = data_[GetHashValue(v)];
    while (p) {
      if (p->value == v) {
        return p;
      }
      p = p->next;
    }
    return nullptr;
  }

  bool Insert(T const &v){
    if (Find(v) != nullptr) {
      return false;
    }

    int shared = GetHashValue(v);
    Node *old_node = data_[shared];
    Node *new_node = new Node();
    new_node->value = v;
    new_node->pre = nullptr;
    new_node->next = old_node;
    if (old_node != nullptr) {
      old_node->pre = new_node;
    }
    data_[shared] = new_node;
    
    return true;
  }

  bool Delete(T const &v) {
    Node *p = Find(v);
    if (p == nullptr) {
      return false;
    }

    if (p->pre == nullptr) {
      data_[GetHashValue(v)] = p->next;
    } else {
      p->pre->next = p->next;
    }

    if (p->next != nullptr) {
      p->next->pre = p->pre;
    }

    delete p;
    p = nullptr;
    return true;
  }

  void Display() {
    for (int i = 0; i < data_.size(); ++i) {
      cout << "槽[" << setw( 3 ) << i << setw( 3 ) << "] ";

      Node *p = data_[i];
      while (p) {
        cout << " --> " << p->value;
        p = p->next;
      }

      cout << endl;
    }
    cout << endl;
  }


private:
  int GetHashValue(T const &v) {
    return v % data_.size();
  }

  vector<Node*> data_;
};

/// @brief 全域散列表
///
/// - 全域散列表是一种使用“键接法”来解决碰撞问题的散列表方法。\n
/// - 随机化保证了对于任何输入，算法都具有较好的平均性能。\n
/// - 全域的散列函数组：设H为一组散列函数，它将给定的关键字域U映射到{0,1,…,m-1}
///   中，这样的一个函数组称为是全域的。如果从H中随机地选择一个散列函数，当关键
///   字K≠J时，两者发生碰撞的概率不大于1/m。
/// - 明白这个散列函数的选取是在“<b>执行开始</b>”随机的选取一个是很重要的，要
///   不然就会不明白到时候怎么进行查找。\n
///   这里所谓的随机性应该这样理解：对于某一个散列表来说，它在初始化时已经把a,b
///   固定了，但是对于一个还未初始化的全域散列表来说，a,b是随机选取的。
///
/// 全域散列函数类，首先选择一个足够大的质数p ，使得每一个可能的关键字k 都落到0 到p-1 的范围内，包括首尾的0 和p-1。\n
/// 这里我们假设全域是0 – 15，p 为17。设集合Zp 为{0, 1, 2, …, p-1}，集合Zp* 为{1, 2, 3, …, p-1}。\n
/// 由于p 是质数，我们可以定义散列函数\n
///                     h(a, b, k) = ((a*k + b) mod p) mod m\n
/// 其中a 属于Zp，b 属于Zp*。由所有这样的a 和b 构成的散列函数，组成了函数簇。即全域散列。\n
/// 全域散列的基本思想是在执行<b>开始</b>时，从一族仔细设计的函数中，随机的选择一个作为散列函数。\n
/// 使之独立于要存储的关键字。不管对手选择了怎样的关键字，其平均性态都很好。\n
/// @param  T  散列表里要存储的元素类型
template<typename T>
class UniversalHashTable {
public:
  /// 构造一个全域散列表,同时从一族仔细设计的函数中，随机的选择一个作为散列函数。
  UniversalHashTable() {
    _p = 101;    //一个足够大的质数
    _m = 10;    //槽的个数
    _items.resize( _m, nullptr );
    for ( int i = 0; i < _m; ++i ) {
      //全部先设置好头结点
      _items[i] = new _Node();
      _items[i]->Next = nullptr;
    }

    // 全域散列的基本思想是在执行<b>开始</b>时，从一族仔细设计的函数中，随机的选择一个作为散列函数。
    _a = rand() % ( _p - 1 ) + 1;
    _b = rand() % _p;
  }

  ~UniversalHashTable() {
    for_each( _items.begin(), _items.end(), []( _Node * item ) {
      while ( item ) {
        auto next = item->Next;
        delete item;
        item = next;
      }
    } );
  }

  /// 向散列表中插入一个元素
  void Insert( T const &new_value ) {
    //始终插入在键表的头，头结点之后的第1个位置
    _Node *new_item = new _Node;
    new_item->Item = new_value;
    new_item->Next = nullptr;
    int hash_value = _HashFunction( new_value );

    new_item->Next = _items[hash_value]->Next;
    _items[hash_value]->Next = new_item;
  }

  /// @brief 从散列表中删除一个元素
  ///
  /// @return  是否成功的删除这样的元素
  bool Delete( T const &delete_value ) {
    int hash_value = _HashFunction( delete_value );
    _Node *root = _items[hash_value];

    while ( root->Next ) {
      if ( root->Next->Item == delete_value ) {
        auto temp = root->Next;
        root->Next = root->Next->Next;
        delete temp;
        return true;
      } else {
        root = root->Next;
      }
    }

    return false;
  }

  /// 在散列表中搜索一个元素
  T * Search( T const &search_value ) {
    int hash_value = _HashFunction( search_value );
    _Node *root = _items[hash_value]->Next;

    while ( root ) {
      if ( root->Item == search_value ) {
        return &( root->Item );
      }
      root = root->Next;
    }
    return nullptr;
  }

  /// 将散列表中的所有的元素显示在输出流中
  void Display() {
    for ( int i = 0; i < _m; ++i ) {
      _Node *item = _items[i]->Next;  //跳过头结点

      cout << "槽[" << setw( 3 ) << i << setw( 3 ) << "]";
      while ( item ) {
        cout << " -> " << item->Item;
        item = item->Next;
      }
      cout << endl;
    }
  }


private:
  /// @brief 节点（使用单键表）
  ///
  /// 要是用双键表就会方便很多啊
  struct _Node {
    T Item;
    _Node *Next;
  };

  /// @brief 全域散列函数
  ///
  /// 本函数、一开始时随机选取_a,_b、再加上选取_p,_m的方法，就是全域散列的核心所在！！！
  /// h(a, b, k) = ((a*k + b) mod p) mod m
  int _HashFunction( T k ) {
    return static_cast<int>( _a * k + _b ) % _p % _m;
  }


  int _p, _m, _a, _b;      ///< 全域散列表的各个参数
  vector<_Node *> _items;    ///< 槽：存储真正的键表，使用的是带头结点的单键表
};


/// 测试全域散列表类
int testUniversalHashTable() {
  UniversalHashTable<int> table;
  cout << "开始往UniversalHashTable里添加内容[0,100)：" << endl;
  for ( int i = 0; i < 100; ++i ) {
    table.Insert( i );
  }
  table.Display();

  cout << "开始删除内容[0,5)：" << endl;
  for ( int i = 0; i < 5; ++i ) {
    table.Delete( i );
  }
  table.Display();

  for ( int i = 0; i < 10; ++i ) {
    auto finded = table.Search( i );
    cout << "开始检索结点[" << i << "]：";
    if ( finded ) {
      cout << *finded << endl;
    } else {
      cout <<  "未找到" << endl;
    }
  }

  return 0;
}

int testNormalHashTable() {
  HashTable<int> ht(10);
  for (int i = 0; i < 20; ++i) {
    ht.Insert(rand() % 100);
  } 
  ht.Display();

  for (int i = 0; i < 50; ++i) {
    ht.Delete(i);
  }
  ht.Display();

  for (int i = 0; i < 20; ++i) {
    ht.Insert(rand() % 100);
  } 
  ht.Display();
}

}

int main() {
  ita::testUniversalHashTable();
  cout << "=============================================" << endl;
  ita::testNormalHashTable();
  return 0;
}
