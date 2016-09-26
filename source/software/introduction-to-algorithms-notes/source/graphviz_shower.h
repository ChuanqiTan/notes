/**
 * @file     graphviz_shower.h
 * @brief    调用Graphviz显示dot语言所描述的图
 *
 * Distributed under the GPL License version 3, see: http://www.gnu.org/licenses
 * Author: chuanqi.tan(at)gmail.com
 */

#include <string>

namespace qi {
/// 调用Graphviz显示dot语言所描述的图
void ShowGraphvizViaDot( std::string const &dot );
}
