#ifndef AOC_HPP
#define AOC_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> read_aoc(const string &filename) {
  vector<string> vs;
  ifstream in(filename);
  if (!in.is_open()) {
    cerr << "Failed to open file: " << filename << endl;
    exit(1);
  }
  string s;
  while (getline(in, s)) {
    vs.push_back(s);
  }
  return vs;
}

#endif
