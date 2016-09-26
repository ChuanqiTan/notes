/**
 * @file     matrix_list_multiply.cpp
 * @brief    矩阵链乘法问题
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
namespace {
void Print( vector< vector<int> > const &pos, int i, int j ) {
  if ( i  == j ) {
    cout << "A" << i;
  } else {
    cout << "(";
    Print( pos, i, pos[i][j] );
    Print( pos, pos[i][j] + 1, j );
    cout << ")";
  }
}
}

/// @brief 矩阵链乘法问题
///
/// 给定n个矩阵{A1,A2,...,An},其中Ai与Ai+1是可乘的，i=1,2,...n-1。现在要计算这n个矩阵的连乘积。
/// 由于矩阵的乘法满足结合律，所以通过加括号可以使得计算矩阵的连乘积有许多不同的计算次序。然而采用不同的加扩号方式，所需要的总计算量是不一样的。
/// 在计算矩阵连乘积时，不同的加括号方式所导致的不同的计算对计算量有很大的影响。如何确定计算矩阵连乘积A1A2，...,An的一个计算次序，使得依此次序计算矩阵连乘积需要的数乘次数最少便成为一个问题。
void MatrixListMultiply() {
  int maxtix_length[] = {30, 35, 15, 5, 10, 20, 25};

  //初始化一个6*6的二维vector
  //times[i][j]表示从第i个矩阵到第j个矩阵之间相乘的最少计算次数，当i>j时没有意义
  vector< vector<int> > times;
  times.resize( 6 );
  for_each( times.begin(), times.end(), []( vector<int> &v ) {
    v.resize( 6 );
  } );
  //构造一个6*6的二维数组来保存每次对序列进行最优划分的位置
  //k_pos[i][j]表示在计算从第i个矩阵到第j个矩阵之间相乘的最少计算次数时，应该从k_pos[i][j]进行划分
  auto k_pos = times;

  for ( int l = 2; l <= 6; ++l ) {
    //计算长度为l的序列所需要的最少计算次数。按长度递增，因为短的序列必须在长的序列之前进行计算
    for ( int i = 0; i < 6 - l + 1; ++i ) {
      int j = i + l - 1;
      times[i][j] = numeric_limits<int>::max();

      for ( int k = i; k < j; ++k ) {
        int value = times[i][k] + times[k + 1][j] + maxtix_length[i] * maxtix_length[k + 1] * maxtix_length[j + 1];
        if ( value < times[i][j] ) {
          times[i][j] = value;
          k_pos[i][j] = k;
        }
      }
    }
  }

  //for (int i = 0; i < 6; ++i)
  //{
  //  for (int j = 0; j < 6; ++j)
  //  {
  //    cout << times[i][j] << "\t";
  //  }
  //  cout << endl;
  //}
  cout << times[0][5] << endl;
  Print( k_pos, 0, 5 );
}

}

int main() {
  ita::MatrixListMultiply();
  return 0;
}
