/**
 * @file     binary_search.cpp
 * @brief    二分查找
 *
 * Distributed under the GPL License version 3, see: http://www.gnu.org/licenses
 * Author: chuanqi.tan(at)gmail.com
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
using namespace std;

namespace ita {

bool BinarySearch(vector<int> const &vec, int begin, int end, int value) {
  if (begin > end) {
    return false;
  }

  int middle = begin + (end-begin)/2; 
  if (vec[middle] == value) {
    return true;
  }

  if (value < vec[middle]) {
    return BinarySearch(vec, begin, middle-1, value);
  } else {
    return BinarySearch(vec, middle+1, end, value);
  }
}

}

int main() {
  vector<int> v;
  for (int i = 0; i < 20; ++i) {
    v.push_back(rand() % 100);
  }
  sort(v.begin(), v.end());
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, "  ")); cout << endl;

  for (int i = 0; i < 100; ++i) {
    cout << i << boolalpha << ita::BinarySearch(v, 0, v.size()-1, i) << "\t";
    if ((i + 1) % 10 == 0) {
      cout << endl;
    }
  }
  return 0; 
}
