/**
 * Author: Nathanael Lu
 * Source: folklore
 * Description: Common macros taken from various sources with personal tweaks
 */
#ifndef MACROS_HPP
#define MACROS_HPP

#include <array>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using PSS = pair<string, string>;
using VI = vector<int>;
using VVI = vector<VI>;
using VII = vector<PII>;
using VL = vector<LL>;
using VVL = vector<VL>;
using VLL = vector<PLL>;

static constexpr const double EPS = 1e-9;
static constexpr const int INF = 1000000005;
static constexpr const long long INFF = 1000000000000000005LL;
static const double PI = acos(-1);
static constexpr const array<array<int, 2>, 4> dirx = {
    {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};
static constexpr const array<array<int, 2>, 8> dirxx = {
    {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}};

#ifdef TESTING
[[maybe_unused]] static int _GLOBAL_PRINT_COUNT = 0;
#define DMARK cout << "====TESTING==== " << ++_GLOBAL_PRINT_COUNT << "\n"
#define DLOG(...) cout << __VA_ARGS__
#define DVALUE(x) DLOG("The value of " << #x << " is " << x << endl)
#define TEST_ONLY(code) code
#else
#define DMARK
#define DLOG(...)
#define DVALUE(x)
#define TEST_ONLY(code)
#endif

#define FOR(a, b, c)                                                           \
  for (int a = static_cast<int>(b); a < static_cast<int>(c); ++a)
#define FORN(a, b, c)                                                          \
  for (int a = static_cast<int>(b); a <= static_cast<int>(c); ++a)
#define FORR(a, b, c)                                                          \
  for (int a = static_cast<int>(b); a >= static_cast<int>(c); --a)
#define FORSQ(a, b, c)                                                         \
  for (int a = static_cast<int>(b); a * a <= static_cast<int>(c); ++a)
#define FORC(a, b, c)                                                          \
  for (char a = static_cast<char>(b); a <= static_cast<char>(c); ++a)
#define FORE(a, b) for (auto &a : b)
#define REP(i, n) FOR(i, 0, n)
#define REPN(i, n) FORN(i, 1, n)
#define REPR(i, n) FORR(i, n, 0)
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define SQR(x) (static_cast<LL>(x) * (x))
#define RESET(a, b) memset(a, b, sizeof(a))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ALL(v) begin(v), end(v)
#define SIZE(v) static_cast<int>(size(v))
#define SORT(v) sort(ALL(v))
#define REVERSE(v) reverse(ALL(v))
#define PERMUTE next_permutation
#define TC(t) while (t--)

#endif
