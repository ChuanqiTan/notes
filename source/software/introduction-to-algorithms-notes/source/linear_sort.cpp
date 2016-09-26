/**
 * @file     linear_sort.cpp
 * @brief    线性时间排序算法
 *
 * Distributed under the GPL License version 3, see: http://www.gnu.org/licenses
 * Author: chuanqi.tan(at)gmail.com
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

namespace ita {
/// @brief 计数排序
///
/// 计数排序的思想是：假定所有的元素都处于[0, k_max_size)区间，然后在n的时间内统计所有的元素的个数。\n
/// 有了这些元素的个数信息之后，就可以重构出它们的排序结果了。\n
/// 计数排序的特征：
/// - 计数排序的一个重要性就是它是稳定的排序算法，这个稳定性是基数排序的基石。
/// - 计数排序的想法真的很简单、高效、可靠
/// - 缺点在于：
///    -# 需要很多额外的空间（当前类型的值的范围）
///    -# 只能对离散的类型有效比如int（double就不行了）
///    -# 基于假设：输入是小范围内的整数构成的。
void CountingSort() {
  int const k_max_size = 100;    //待排序的所有元素都必须位于区间[0, k_max_size)
  //初始化区间为[0, k_max_size)之间的随机数作为输入
  std::vector<int> v;
  for ( int i = 0; i < 15; ++i ) {
    v.push_back( rand() % k_max_size );
  }

  //进行计数 c[i] = j代表着i在输入数据中出现了j次
  std::vector<int> c( k_max_size, 0 );
  std::for_each( v.begin(), v.end(), [&]( int i ) {
    ++c[i];
  } );

  //对所有的计数从依次总结出最后的排序，并没有使用原书上的方法
  //比书上的算法更直接，将二步合成了一步，效率上是同样的渐近时间复杂度的，似乎更好点。
  v.clear();
  for ( int i = 0; i < k_max_size; ++i ) {
    for ( int k = 0; k < c[i]; ++k ) {
      v.push_back( i );
    }
  }

  copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, "  " ) );
}


/// @brief 基数排序
///
/// 基数排序就是按照从底位到高位的顺序依次选取待排序的元素，然后在稳定的前提下放入下一次排序之中，和放扑克牌很相似。
/// - 基数排序时对每一维进行调用子排序算法时要求这个子排序算法必须是稳定的。
/// - 基数排序与直觉相反：它是按照从底位到高位的顺序排序的。\n
///   我觉得原因在于：高有效位对底有效位有着决定性的作用。
/// @note  基数排序内部所使用的子排序算法必须是稳定的
void RadixSort(std::vector<int> &v) {
  int max_dim = 0;
  for (int i = 0; i < v.size(); ++i) {
    int dim = 0;
    int j = v[i];
    while (j > 0) {
      ++dim;
      j /= 10;
    }

    max_dim = max(max_dim, dim);
  }
  cout << "max dim = " << max_dim << endl;

  //得到一个数的某一维的值
  //eg:  GetDim(987, 0) = 7
  //     GetDim(987, 1) = 8
  //     GetDim(987, 2) = 9
  auto GetDim = []( int number, int d ) -> int {
    for ( int i = 0; i < d; ++i ) {
      number /= 10;
    }
    return number % 10;
  };

  int dim = 0;
  while (dim < max_dim) {
    vector<vector<int>> barrel(10);

    for (int i = 0; i < v.size(); ++i) {
      barrel[GetDim(v[i], dim)].push_back(v[i]);
    }

    v.clear();
    for (int i = 0; i < barrel.size(); ++i) {
      v.insert(v.end(), barrel[i].begin(), barrel[i].end());
    }
    ++dim;
  }
}

/// 基数排序算法的初始化和调用
void RadixSortCaller() {
  //初始化[0,999]之间的随机数作为输入
  std::vector<int> v;
  for ( int i = 0; i < 10; ++i ) {
    v.push_back( rand() % 100);
  }
  std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, "  " ) );
  std::cout << std::endl;

  RadixSort( v );
  std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, "  " ) );
}

/// @brief 桶排序
///
/// 桶排序的算法步骤：
/// - 构建桶，并将所有的元素放入到相应的桶中去；\n
///    比如（0.21  0.45  0.24  0.72  0.7  0.29  0.77  0.73  0.97  0.12）根据它们的小数点后第1位，放入到相应的10个桶中去
/// - 对每一个桶里的元素进行排序\n
///   比如对于桶2，其中有2个元素0.21, 0,24。 对它们进行好内部排序。
/// - 依次把每个桶中的元素提取出来并组合在一起\n
///   得到最后的结果（0.12  0.21  0.24  0.29  0.45  0.7  0.72  0.73  0.77  0.97）
///
/// 桶排序也只是期望运行时间能达到线性，对于最坏的情况，它的运行时间取决于它内部使用的子排序算法的运行时间，一般为O(nlgn)。
/// - 桶排序基于假设：输入的的元素均匀的分布在区间[0, 1]上。
/// - 感觉桶排没有什么大的实现价值，因为它限定了输入的区间，还要求最好是均匀分布，它的最坏情况并不好。
void BucketSort() {
  //初始化[0,1)之间的随机数
  vector<double> v;
  for ( int i = 0; i < 10; ++i ) {
    v.push_back( ( rand() % 100 ) * 1.0 / 100.0 );
  }
  copy( v.begin(), v.end(), ostream_iterator<double>( cout, "  " ) );
  cout << endl;

  //构建桶，并将所有的元素放入到相应的桶中去
  vector< vector<double> > bucket( 10 );  //10个桶
  for_each( v.begin(), v.end(), [&]( double d ) {
    bucket[d * 10].push_back( d );
  } );

  //对每一个桶里的元素进行排序
  for_each( bucket.begin(), bucket.end(), []( vector<double> &sub_v ) {
    sort( sub_v.begin(), sub_v.end() );
  } );

  //依次把每个桶中的元素提取出来并组合在一起
  v.clear();
  for_each( bucket.begin(), bucket.end(), [&]( vector<double> &sub_v ) {
    v.insert( v.end(), sub_v.begin(), sub_v.end() );
  } );

  copy( v.begin(), v.end(), ostream_iterator<double>( cout, "  " ) );
}

/// 测试计数排序 基数排序 桶排序
int testLinearSort() {
  cout << endl << "===========开始计数排序===========" << endl;
  CountingSort();
  cout << endl << "===========开始基数排序===========" << endl;
  RadixSortCaller();
  cout << endl << "===========开始桶排序===========" << endl;
  BucketSort();

  return 0;
}

}

int main() {
  ita::testLinearSort();
  return 0;
}
