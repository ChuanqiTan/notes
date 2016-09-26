/**
 * @file     graphviz_shower.cpp
 * @brief    调用Graphviz显示dot语言所描述的图
 *
 * Distributed under the GPL License version 3, see: http://www.gnu.org/licenses
 * Author: chuanqi.tan(at)gmail.com
 */


#include <string>
#include <fstream>
using namespace std;

namespace qi {
void ShowGraphvizViaDot( std::string const &dot ) {
  ofstream dot_file( "/tmp/graphiv_show.dot" );
  dot_file << dot;
  dot_file.close();
  system( "dot -Tpng /tmp/graphiv_show.dot -o /tmp/graphiv_show.png" );
  system( "eog /tmp/graphiv_show.png" );
}
}
