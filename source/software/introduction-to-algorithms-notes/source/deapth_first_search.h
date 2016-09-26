/**
 * @file     deapth_first_search.h
 * @brief    深度优先搜索核心递归程序
 *
 * Distributed under the GPL License version 3, see: http://www.gnu.org/licenses
 * Author: chuanqi.tan(at)gmail.com
 */
#pragma once

#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <bitset>
#include "graphics.h"

using namespace std;

namespace ita {
/// @brief 深度优先遍历的递归函数
///
/// 从顶点index开始，按照深度优先的规则依次遍历。只会遍历从index顶点可以访问的结果，对于index不可到达的结点不会访问。
/// @param  g           要遍历的图，使用邻接表的表示方法
/// @param  index       从index顶点开始进行遍历
/// @param  d           时间戳d
/// @param  f           时间戳f
/// @param  traversed   标识顶点是否已经被遍历
/// @param  time        全局时间，用于设置时间戳d和f
/// @return             返回本次深度优先遍历得到的子树依次所遍历过的结点的编号
template<typename T>
vector<int> DFS_Visit( GraphicsViaAdjacencyList<T> &g, size_t index, vector<int> &d, vector<int> &f, vector<bool> &traversed, int &time ) {
  vector<int> this_time_traversed;
  this_time_traversed.push_back( index );
  traversed[index] = true;
  ++time;
  d[index] = time;

  for ( size_t i = 0; i < g.GetVertex().size(); ++i ) {
    if ( !traversed[i] && g.IsLinked( index, i ).first ) {
      vector<int> v = DFS_Visit( g, i, d, f, traversed, time );
      this_time_traversed.insert( this_time_traversed.end(), v.begin(), v.end() );
    }
  }

  ++time;
  f[index] = time;
  return this_time_traversed;
}

}
