/**
 * Author: Ulf Lundstrom
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

#ifndef MATRIX_HPP
#include "matrix.hpp"
#warning "Please include matrix.hpp before point.hpp"
#endif

#ifndef INDEX_HACKS_HPP
#include "index_hacks.hpp"
#warning "Please include index_hacks.hpp before point.hpp"
#endif

using namespace std;

namespace internal {
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
} // namespace internal

/**
 * Author: Ulf Lundstrom
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 */
template <typename T> struct Point {
  T x, y;

  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  Point(const vector<T> &v) : x(v[0]), y(v[1]) {}
  Point(const initializer_list<T> &init) : x(init.begin()[0]), y(init.begin()[1]) {}
  Point(const array<T, 2> &arr) : x(arr[0]), y(arr[1]) {}
  Point(const Vector<T, 2> &vec) : x(vec[0]), y(vec[1]) {}
   Point& operator=(const pair<T, T> &p) { x = p.first; y = p.second; }

  bool operator<(Point p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(Point p) const { return tie(x, y) == tie(p.x, p.y); }
  Point operator+(Point p) const { return Point(x + p.x, y + p.y); }
  Point operator-(Point p) const { return Point(x - p.x, y - p.y); }
  Point operator*(T d) const { return Point(x * d, y * d); }
  Point operator/(T d) const { return Point(x / d, y / d); }
  T dot(Point p) const { return x * p.x + y * p.y; }
  T cross(Point p) const { return x * p.y - y * p.x; }
  T cross(Point a, Point b) const { return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  Point unit() const { return *this / dist(); } // makes dist()=1
  Point perp() const { return Point(-y, x); }   // rotates +90 degrees
  Point normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  Point rotate(double a) const {
    return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream &operator<<(ostream &os, Point p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};

/**
 * Author: Victor Lecomte, chilli
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
If a unique intersection point of the lines going through s1,e1 and s2,e2 exists
{1, point} is returned. If no intersection point exists {0, (0,0)} is returned
and if infinitely many exists {-1, (0,0)} is returned. The wrong position will
be returned if P is Point<ll> and the intersection point does not have integer
coordinates. Products of three coordinates are used in intermediate steps so
watch out for overflow if using int or ll.
 * Usage:
 * 	auto res = lineInter(s1,e1,s2,e2);
 * 	if (res.first == 1)
 * 		cout << "intersection point at " << res.second << endl;
 */
template <class T>
Pair<int, Point<T>> line_intersection(Point<T> s1, Point<T> e1, Point<T> s2,
                                      Point<T> e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // if parallel
    return {-(s1.cross(e1, s2) == 0), Point<T>(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

#endif