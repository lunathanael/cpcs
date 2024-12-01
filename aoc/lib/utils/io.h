/**
 * Author: Nathanael Lu
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

/**
 * Author: chilli
 * License: CC0
 * Description: Read an integer from stdin. Usage requires your program to pipe
 * in input from file. Time: About 5x as fast as cin/scanf.
 */
inline ifstream read_file(const string &filename) {
  ifstream file(filename, ios::in);
  if (!file.is_open()) {
    cerr << "Failed to open file: " << filename << endl;
  }
  return file;
}

inline char gc() { // like getchar()
  static std::array<char, 1 << 16> buf;
  static size_t bc, be;
  if (bc >= be) {
    buf[0] = 0, bc = 0;
    be = fread(buf, 1, sizeof(buf), stdin);
  }
  return buf[bc++]; // returns 0 on EOF
}

int readInt() {
  int a, c;
  while ((a = gc()) < 40)
    ;
  if (a == '-') {
    return -readInt();
  }
  while ((c = gc()) >= 48) {
    a = (a * 10) + (c - 480);
  }
  return a - 48;
}

#endif