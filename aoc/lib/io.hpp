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
#include <tuple>

using namespace std;

template <typename T, typename TT>
ostream &operator<<(ostream &os, pair<T, TT> t) {
  return os << "(" << t.first << ", " << t.second << ")";
}

template <typename... Args>
ostream &operator<<(ostream &os, const tuple<Args...> &t) {
  os << "(";
  apply([&os](const auto &...args) {
    size_t n{0};
    ((os << (n++ ? ", " : "") << args), ...);
  }, t);
  return os << ")";
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

template <typename T> void print(T x) { cout << x << endl; }

template <typename T, typename... Args> void print(T first, Args... args) {
  cout << first << " ";
  print(args...);
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