/**
 * Author: Nathanael Lu
 * Source: folklore
 * Description: Common macros taken from various sources with personal tweaks
 */
#ifndef MACROS_HPP
#define MACROS_HPP

#include <array>
#include <cmath>
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using I32 = int32_t;
using U32 = uint32_t;
using I64 = int64_t;
using U64 = uint64_t;
using F32 = float;
using F64 = double;
#ifdef __SIZEOF_INT128__
using I128 = __int128_t;
using U128 = __uint128_t;
#endif

using LL = long long;
using ULL = unsigned long long;

using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using PSS = pair<string, string>;
using VI = vector<int>;
using VVI = vector<VI>;
using VII = vector<PII>;
using VL = vector<LL>;
using VVL = vector<VL>;
using VLL = vector<PLL>;
using VS = vector<string>;
using STR = string;

/*
template <typename K, typename V> using UMP = unordered_map<K, V>;
template <typename K, typename V> using UMP = __gnu_pbds::gp_hash_table<K, V>;
*/

template <typename T> using UST = unordered_set<T>;
template <typename T> using PQ = priority_queue<T>;
template <typename T> using PQI = priority_queue<T, vector<T>, greater<T>>;

static const double PI = acos(-1);
static constexpr const array<array<int, 2>, 4> DIRXY = {
    {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};
static constexpr const array<array<int, 2>, 8> DIRDIAG = {
    {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}};

#ifdef TESTING
[[maybe_unused]] static int _GLOBAL_PRINT_COUNT = 0;
#define DMARK cout << "====TESTING==== " << ++_GLOBAL_PRINT_COUNT << endl;
#define DLOG(...) cout << __VA_ARGS__;
#define DVALUE(x) DLOG("The value of " << #x << " is " << x << endl);
#define TEST_ONLY(code) code
#define IOSOPT
#else
#define DMARK
#define DLOG(...)
#define DVALUE(x)
#define TEST_ONLY(code)
#define IOSOPT                                                                 \
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#endif

#define FOR(a, b, c)                                                           \
  for (int a = static_cast<int>(b); a < static_cast<int>(c); ++a)
#define FORN(a, b, c)                                                          \
  for (int a = static_cast<int>(b); a <= static_cast<int>(c); ++a)
#define FORR(a, b, c)                                                          \
  for (int a = static_cast<int>(b); a >= static_cast<int>(c); --a)
#define FORSR(a, b, c)                                                         \
  for (int a = static_cast<int>(b); a * a <= static_cast<int>(c); ++a)
#define FORC(a, b, c)                                                          \
  for (char a = static_cast<char>(b); a <= static_cast<char>(c); ++a)
#define FORE(ele, ds) for (auto ele : ds)
#define REP(i, n) FOR(i, 0, n)
#define REPN(i, n) FORN(i, 1, n)
#define REPR(i, n) FORR(i, n, 0)
#define RESET(a, b) memset(a, b, sizeof(a));

#define fi first
#define se second
#define mp make_pair
#define pb push_back

#define ALL(v) begin(v), end(v)
#define ALLR(v) rbegin(v), rend(v)
#define SZ(v) static_cast<int>(size(v))
#define SORT(v) sort(ALL(v));
#define REVERSE(v) reverse(ALL(v));
#define FORTC(tc)                                                              \
  unsigned int tc;                                                             \
  tc = read_int<true>();                                                       \
  while (tc--)

#define HAS(v, x) (v.find(x) != v.end())
#define AHAS(ds, x) (find(ALL(ds), x) != end(ds))

#define REMIN(a, b) a = min(a, b);
#define REMAX(a, b) a = max(a, b);

#define IN(i, l, r)                                                            \
  ((l) < (i) && (i) < (r)) // the next for are for checking bounds
#define LINR(i, l, r) ((l) <= (i) && (i) <= (r))
#define LIN(i, l, r) ((l) <= (i) && (i) < (r))
#define INR(i, l, r) ((l) < (i) && (i) <= (r))

#define BINOP(name, ...)                                                       \
  template <typename T = void> struct name;                                    \
  template <typename T> struct name {                                          \
    constexpr T operator()(const T &x, const T &y) const {                     \
      return __VA_ARGS__;                                                      \
    }                                                                          \
  };                                                                           \
  template <> struct name<void> {                                              \
    template <typename T>                                                      \
    constexpr T operator()(const T &x, const T &y) const {                     \
      return __VA_ARGS__;                                                      \
    }                                                                          \
  };

#define SCAST(type, x) static_cast<type>(x)

#define bi_popcount(x) __builtin_popcount(x)
#define bi_popcountl(x) __builtin_popcountl(x)
#define bi_popcountll(x) __builtin_popcountll(x)
#define bi_clz(x) __builtin_clz(x)
#define bi_clzl(x) __builtin_clzl(x)
#define bi_clzll(x) __builtin_clzll(x)
#define bi_ctz(x) __builtin_ctz(x)
#define bi_ctzl(x) __builtin_ctzl(x)
#define bi_ctzll(x) __builtin_ctzll(x)
#define bi_ffs(x) __builtin_ffs(x)
#define bi_ffsl(x) __builtin_ffsl(x)
#define bi_ffsll(x) __builtin_ffsll(x)
#define bi_parity(x) __builtin_parity(x)
#define bi_parityl(x) __builtin_parityl(x)
#define bi_parityll(x) __builtin_parityll(x)

#endif
