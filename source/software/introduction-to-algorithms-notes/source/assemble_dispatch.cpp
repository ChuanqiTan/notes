/**
 * @file     assemble_dispatch.cpp
 * @brief    装配线调度问题
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
using namespace std;

namespace ita {
/// @brief 装配线调度问题
///
/// 某汽车工厂有2个装配线，每个装配线有n 个装配站（按顺序编号1～n ），两个装配线对应的装配站执行相同的功能，但所用的时间可能不同。经过第i条流水线（i=1，2）
/// 的第j 个装配站所花的时间为s[i][j]。从第i条流水线的第j 个装配站移到第j+1个装配站的时间可以忽略，而移到另外一个流水线的下一个装配站则需要一定的时间t[i][j]。
/// - 汽车进入流水线需要花时间e[i]，出流水线时需要花时间x[i]。
/// - 汽车的装配需要按顺序经过所有装配站。
/// - 现在已知装配时间s[i][j]和转移时间t[i][j]以及进入时间e[i]、出流水线时间x[i]，要求输出装配一辆汽车所需要的最短时间。
void AssembleDispatch() {
  int e[] = {2, 4};
  int x[] = {3, 2};
  int S0[] = {7, 9, 3, 4, 8, 4};
  int S1[] = {8, 5, 6, 4, 5, 7};
  int *s[] = {S0, S1};
  int T0[] = {2, 3, 1, 3, 4};
  int T1[] = {2, 1, 2, 2, 1};
  int *t[] = {T0, T1};

  //f[i][j]表示完成第i条装配线的第j个装配站的装配工作完成之后，需要的最少时间
  vector< vector<int> > f( 2 );
  f[0].resize( 6 );
  f[1].resize( 6 );

  //l[i][j]表示第i条装配线上的第j个装配站完成工作的最少时间所选用的是哪一条装配线上的j-1装配站
  //j = 0, l[i][j]时没有意义，因为第0个装配站没有选择
  vector< vector<int> > l( 2 );
  l[0].resize( 6 );
  l[1].resize( 6 );

  f[0][0] = e[0] + s[0][0];
  f[1][0] = e[1] + s[1][0];
  for ( int i = 1; i < 6; ++i ) {
    //更新f[0][i]
    if ( f[0][i - 1] + s[0][i] < f[1][i - 1] + s[0][i] + t[1][i - 1] ) {
      f[0][i] = f[0][i - 1] + s[0][i];
      l[0][i] = 0;
    } else {
      f[0][i] = f[1][i - 1] + s[0][i] + t[1][i - 1];
      l[0][i] = 1;
    }

    //更新f[1][i]
    if ( f[1][i - 1] + s[1][i] < f[0][i - 1] + s[1][i] + t[0][i - 1] ) {
      f[1][i] = f[1][i - 1] + s[1][i];
      l[1][i] = 1;
    } else {
      f[1][i] = f[0][i - 1] + s[1][i] + t[0][i - 1];
      l[1][i] = 0;
    }

    //如果不需要记录l[i][j]，这样就很方便的实现了，可见动态规划其实比递归还简单易实现
    //f[0][i] = min( f[0][i - 1] + s[0][i], f[1][i - 1] + s[0][i] + t[1][i - 1] );
    //f[1][i] = min( f[1][i - 1] + s[1][i], f[0][i - 1] + s[1][i] + t[0][i - 1] );
  }

  int l_star = ( f[0][5] + x[0] < f[1][5] + x[1] ? 0 : 1 );
  int final_min_time = min( f[0][5] + x[0], f[1][5] + x[1] );
  cout << "最短的装配路线需要时间：" << final_min_time << endl;

  vector<int> route;
  for ( int i = 5; i >= 0; --i ) {
    route.push_back( l_star );
    l_star = l[l_star][i];
  }
  reverse( route.begin(), route.end() );    //逆转
  copy( route.begin(), route.end(), ostream_iterator<int>( cout, " --> " ) );
}

}

int main() {
  ita::AssembleDispatch();
  return 0;
}
