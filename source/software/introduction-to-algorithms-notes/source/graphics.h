/**
 * @file     graphics.h
 * @brief    图的两种表示方法：（1）邻接表法；（2）邻接矩阵法
 *
 * Distributed under the GPL License version 3, see: http://www.gnu.org/licenses
 * Author: chuanqi.tan(at)gmail.com
 */
#pragma once

#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

namespace ita {
/// 图的类型：有向图还是无向图
enum GraphicsType :
short {
  Digraph,      ///< 有向图
  Undigraph      ///< 无向图
};

/// 使用邻接表法表示一个图
template<typename T>
class GraphicsViaAdjacencyList {
public:
  /// 邻接表上的一个结点
  struct AdjacencyListNode {
    size_t      AimNodeIndex;  ///< 目标顶点的编号
    double      Weight;      ///< 该条连接边的权值
    AdjacencyListNode  *Next;      ///< 指向下一个结点
  };

public:
  /// 通过结点来初始化一个图
  GraphicsViaAdjacencyList( vector<T> const &v, GraphicsType type ) : _v( v ), _e( v.size(), nullptr ), _type( type ) {

  }

  ~GraphicsViaAdjacencyList() {
    for_each( _e.begin(), _e.end(), []( AdjacencyListNode * e ) {
      while ( e ) {
        AdjacencyListNode *temp = e;
        e = e->Next;
        delete temp;
      }
    } );
  }


  /// 标识图中两个标点之间有一条边
  void Link2Vertex( size_t index1, size_t index2, double weight = 1 ) {
    AdjacencyListNode *node = new AdjacencyListNode();
    node->AimNodeIndex = index2;
    node->Next = _e[index1];
    node->Weight = weight;
    _e[index1] = node;

    if ( _type == Undigraph ) {
      //无向图
      node = new AdjacencyListNode();
      node->AimNodeIndex = index1;
      node->Next = _e[index2];
      node->Weight = weight;
      _e[index2] = node;
    }
  }

  /// @brief 查询两个顶点是否连接
  ///
  /// 返回两个顶点是否相连，同时还返回该条边的权值。如果不相连，就返回<false, 0>，这里的权值无意义
  pair<bool, AdjacencyListNode *> IsLinked( size_t index1, size_t index2 ) const {
    AdjacencyListNode *l = _e[index1];
    while ( l ) {
      if ( l->AimNodeIndex == index2 ) {
        return make_pair( true, l );
      }
      l = l->Next;
    }
    return make_pair( false, nullptr );
  }

  /// 返回所有的顶点
  inline vector<T> & GetVertex() {
    return _v;
  }

  /// 返回所有的边的邻接表
  inline vector<AdjacencyListNode *> & GetEdges() {
    return _e;
  }

  /// 返回所有的边的编号值对
  vector<pair<size_t, size_t>> GetAllEdges() {
    vector<pair<size_t, size_t>> edges;
    for ( size_t i = 0; i < _e.size(); ++i ) {
      AdjacencyListNode *l = _e[i];
      while ( l ) {
        edges.push_back( make_pair( i, l->AimNodeIndex ) );
        l = l->Next;
      }
    }
    return edges;
  }


private:
  //GraphicsViaAdjacencyList(GraphicsViaAdjacencyList<T> const &);
  //GraphicsViaAdjacencyList<T> & operator=(GraphicsViaAdjacencyList<T> &);

  vector<T>        _v;    ///< 图的顶点的集合
  vector<AdjacencyListNode *>  _e;    ///< 图的边，即邻接表
  GraphicsType      _type;  ///< 图的类型
};


/// 使用邻接矩阵来表示一个图
template<typename VertexType, typename WeightType>
class GrpahicsViaAdjacencyMatrix {
public:
  GrpahicsViaAdjacencyMatrix( vector<VertexType> const &v, GraphicsType type = Digraph ) : _v( v ), _e( v.size(), vector<WeightType>( v.size() ) ), _type( type ) {

  }

  /// 标识两个顶点之间有一条权值为weight的边
  void Link2Vertex( size_t index1, size_t index2, WeightType weight ) {
    _e[index1][index2] = weight;
    if ( _type == Undigraph ) {
      _e[index2][index1] = weight;
    }
  }

  /// 查询两个顶点是否连接
  bool IsLinked( size_t index1, size_t index2 ) const {
    return _e[index1][index2] != WeightType();
  }

  /// 返回所有的顶点
  inline vector<VertexType> & GetVertex() {
    return _v;
  }
  /// 返回所有的边
  inline vector<vector<WeightType>> & GetEdge() {
    return _e;
  }



private:
  vector<VertexType>        _v;    ///< 图的顶点的集合
  vector<vector<WeightType>>    _e;    ///< 图的边，即邻接矩阵
  GraphicsType          _type;  ///< 图的类型
};

}
