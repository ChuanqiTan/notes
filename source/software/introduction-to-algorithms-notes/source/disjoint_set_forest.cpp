/**
 * @file     disjoint_set_forest.cpp
 * @brief    用于不相交集合的数据结构（并查集）
 *
 * Distributed under the GPL License version 3, see: http://www.gnu.org/licenses
 * Author: chuanqi.tan(at)gmail.com
 */

#include <iostream>
#include <vector>
using namespace std;

#include "disjoint_set_forest.h"

namespace ita {
/// 用于不相交集合的数据结构（并查集）
void testDisjointSetForest() {
  vector<DisjointSetForest::DisjointSet<int> *> nodes;
  for ( int i = 0; i < 10; ++i ) {
    nodes.push_back( DisjointSetForest::MakeSet( i ) );
  }


  for ( int i = 0; i < 5; ++i ) {
    int index1 = rand() % 10;
    int index2 = rand() % 10;
    DisjointSetForest::Union( nodes[index1], nodes[index2] );
    cout << "Union : " << index1 << "---" << index2 << endl;
  }

  for ( int i = 0; i < 10; ++i ) {
    cout << i << "-------------->" << DisjointSetForest::FindSet( nodes[i] )->Item << endl;
  }

  //for (int i = 0; i < nodes.size(); ++i)
  //{
  //  FindSet(nodes[i]);
  //  cout << FindSet(nodes[i])->Item << endl;
  //}
}
}

int main() {
  ita::testDisjointSetForest();
  return 0;
}

