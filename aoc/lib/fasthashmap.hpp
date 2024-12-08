#ifndef FAST_HASH_MAP
#define FAST_HASH_MAP

#include <bits/extc++.h> /** keep-include */
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <utility>
#include <vector>

using namespace std;

/**
 * Author: Simon Lindholm, chilli
 * License: CC0
 * Source: http://codeforces.com/blog/entry/60737
 * Description: Hash map with mostly the same API as unordered\_map, but \tilde
 * 3x faster. Uses 1.5x memory.
 * Initial capacity must be a power of 2 (if provided).
 */
#ifndef FHM_RANDOMIZE
#define FHM_RANDOMIZE false
#endif

#if !FHM_RANDOMIZE
struct _FHM_chash {
  // To use most bits rather than just the lowest ones:
  // large odd number for C
  static const uint64_t C = uint64_t(4e18 * acos(0)) | 71;
  size_t operator()(uint64_t x) const { return __builtin_bswap64(x * C); }
};
#else
// For CodeForces, or places where hacking might be a problem:
static const int64_t _FHM_RANDOM =
    chrono::high_resolution_clock::now().time_since_epoch().count();
struct _FHM_chash {
  // To use most bits rather than just the lowest ones:
  // large odd number
  static const uint64_t C = uint64_t(4e18 * acos(0)) | 71;
  size_t operator()(uint64_t x) const {
    return __builtin_bswap64((x ^ _FHM_RANDOM) * C);
  }
};
#endif

template <typename K, typename V,
          typename Hash = std::conditional_t<std::is_integral_v<K>, _FHM_chash,
                                             std::hash<K>>>
using UMP = __gnu_pbds::gp_hash_table<K, V, Hash>;
template <typename K, typename Hash = std::conditional_t<
                          std::is_integral_v<K>, _FHM_chash, std::hash<K>>>
using UST = __gnu_pbds::gp_hash_table<K, __gnu_pbds::null_type, Hash>;

template <class T, int SZ> struct SMALL_UMP {
  vector<int> keys;
  bitset<SZ> inside;
  array<T, SZ> dat;
  void clear() {
    for (int t : keys) {
      inside[t] = 0;
    }
    keys.clear();
  }
  T &operator[](int k) {
    if (!inside[k]) {
      inside[k] = 1;
      keys.push_back(k);
      dat[k] = 0;
    }
    return dat[k];
  }
  int size() const { return keys.size(); }
  void insert(int k, T v) {
    if (!inside[k]) {
      inside[k] = 1;
      keys.push_back(k);
    }
    dat[k] = v;
  }
  void erase(int k) {
    if (inside[k]) {
      inside[k] = 0;
      keys.erase(find(keys.begin(), keys.end(), k));
    }
  }
};

#endif
