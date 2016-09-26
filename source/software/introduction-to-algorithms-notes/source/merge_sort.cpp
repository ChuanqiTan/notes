/**
 * @file     quick_sort.cpp
 * @brief    归并排序
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
void _MergeSort(vector<int> &v, int begin, int end) {
  if (begin >= end) {
    return;
  }

  int middle = begin + (end-begin)/2;
  _MergeSort(v, begin, middle);
  _MergeSort(v, middle + 1, end);

  vector<int> out;
  int i = begin;
  int j = middle+1;
  while (i <= middle && j <= end) {
    if (v[i] < v[j]) {
      out.push_back(v[i]);
      ++i;
    } else {
      out.push_back(v[j]);
      ++j;
    }
  }
  if (i <= middle) {
    out.insert(out.end(), v.begin() + i, v.begin() + middle + 1);
  }
  if (j <= end) {
    out.insert(out.end(), v.begin() + j, v.begin() + end + 1);
  }
 
  for (int i = 0; i < out.size(); ++i) {
    v[begin+i] = out[i];
  }
}

void MergeSort(vector<int> &v) {
  _MergeSort(v, 0, v.size() - 1);
}

}

int main() {
  vector<int> v;
  for (int i = 0; i < 30; ++i) {
    v.push_back(rand() % 100);
  }

  copy(v.begin(), v.end(), ostream_iterator<int>(cout, "  ")); cout << endl;
  ita::MergeSort(v);
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, "  ")); cout << endl;
  return 0; 
}
