#ifndef IO_H
#define IO_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename TT>
ostream &operator<<(ostream &os, pair<T, TT> t) {
  return os << "(" << t.fi << "," << t.se << ")";
}
template <typename T> ostream &operator<<(ostream &os, vector<T> vec) {
  for (auto &ele : vec) {
    os << ele << " ";
  }
  return os;
}

#endif