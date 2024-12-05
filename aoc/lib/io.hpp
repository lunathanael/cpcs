/**
 * Author: Nathanael Lu
 * Source: Own work
 * Description: Common IO utilities
 */
#ifndef IO_H
#define IO_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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

inline ifstream read_file(const string &filename) {
  ifstream file(filename, ios::in);
  if (!file.is_open()) {
    cerr << "Failed to open file: " << filename << endl;
  }
  return file;
}

template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '{';
  string sep;
  for (const T &x : v) {
    os << sep << x;
    sep = ", ";
  };
  return os << '}';
}

#define wez(n)                                                                 \
  int n;                                                                       \
  cin >> n;
#define wez2(n, m)                                                             \
  int n, m;                                                                    \
  cin >> n >> m;
#define wez3(n, m, k)                                                          \
  int n, m, k;                                                                 \
  cin >> n >> m >> k;
#endif