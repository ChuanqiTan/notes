/**
 * @file     plan_party.cpp
 * @brief    聚会规划问题
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
#include <fstream>
#include <string>
#include <numeric>
#include <set>
using namespace std;

namespace ita {
namespace {
/// 一个人
struct Human {
  vector<Human *> Childs;
  int        LovePartyValue;
  string      Name;

  int        IncludeValue;      ///< 该Human参与聚会时，以他为根的子树所能得到的最大喜欢度总和
  int        NotIncludeValue;    ///< 该Human不参与聚会时，以他为根的子树所能得到的最大喜欢度总和
  //IsValid是动态规划的备忘录方式的一个变种
  bool      IsValid;        ///< IncludeValue,NotIncludeValue值是否有效？（无效时为默认值0）

  Human( string const &name, int rank_value )
      : Name( name ), LovePartyValue( rank_value ), IncludeValue( rank_value ), IsValid( false ) {}
};

void PlanPartyViaDyanmicProgramming( Human *root ) {
  if ( root != nullptr && !root->IsValid ) {
    //root 参加的情况
    root->IncludeValue = accumulate( root->Childs.begin(), root->Childs.end(), root->LovePartyValue, []( int acc, Human * human )->int {
      PlanPartyViaDyanmicProgramming( human );
      return acc + human->NotIncludeValue;
    } );

    //root 不参加的情况
    root->NotIncludeValue = accumulate( root->Childs.begin(), root->Childs.end(), 0, []( int acc, Human * human )->int {
      PlanPartyViaDyanmicProgramming( human );
      return acc + max( human->IncludeValue, human->NotIncludeValue );
    } );

    root->IsValid = true;
  }

}
}

/// 聚会规划问题
void PlanParty() {
  Human *root = new Human( "TCQ", 4 );    //总裁结点

  Human *c1 = new Human( "WY", 2 );
  Human *c2 = new Human( "ABC", 3 );
  root->Childs.push_back( c1 );
  root->Childs.push_back( c2 );

  PlanPartyViaDyanmicProgramming( root );
  cout << max( root->IncludeValue, root->NotIncludeValue );
}
}


int main() {
  ita::PlanParty();
  return 0;
}

