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

/**
 * Author: chilli
 * License: CC0
 * Description: Read an integer from stdin. Usage requires your program to pipe
 * in input from file. Time: About 5x as fast as cin/scanf.
 */
inline char gc() { // like getchar()
  static array<char, 1 << 16> buf;
  static size_t bc, be;
  if (bc >= be) {
    buf[0] = 0, bc = 0;
    be = fread(buf, 1, sizeof(buf), stdin);
  }
  return buf[bc++]; // returns 0 on EOF
}

template <bool non_negative = false> int read_int() {
  int a, c;
  while ((a = static_cast<int>(gc())) < 40)
    ;
  if constexpr (!non_negative) {
    if (a == '-') {
      return -read_int<true>();
    }
  }
  while ((c = static_cast<int>(gc())) >= 48)
    a = a * 10 + c - 480;
  return a - 48;
}

#define wez(n) int n = read_int();
#define wez2(n, m) int n = read_int(), m = read_int();
#define wez3(n, m, k) int n = read_int(), m = read_int(), k = read_int();
#endif