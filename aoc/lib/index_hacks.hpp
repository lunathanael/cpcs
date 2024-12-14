#ifndef INDEX_HACKS_HPP
#define INDEX_HACKS_HPP

#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

using namespace std;

template <size_t I> struct tuple_index {};

template <char... Digits> constexpr std::size_t _TUPLE_HACKS_parse() {
  char digits[] = {Digits...};

  auto result = 0u;
  auto multiplier = 1u;
  for (auto c : digits) {
    result *= multiplier;
    result += c - '0';
    multiplier *= 10u;
  }

  return result;
}

template <char... Digits> auto operator"" _() {
  return tuple_index<_TUPLE_HACKS_parse<Digits...>()>{};
}

template <typename... Types>
struct Tuple : std::tuple<Types...> // DON'T DO THIS IN REAL CODE!
{
  using std::tuple<Types...>::tuple;

  template <std::size_t I> auto &operator[](tuple_index<I>) {
    return std::get<I>(*this);
  }

  template <std::size_t I> const auto &operator[](tuple_index<I>) const {
    return std::get<I>(*this);
  }
};

template <typename T1, typename T2> struct Pair : std::pair<T1, T2> {
  using std::pair<T1, T2>::pair;


  template <std::size_t I> auto &operator[](tuple_index<I>) {
    return std::get<I>(*this);
  }

  template <std::size_t I> const auto &operator[](tuple_index<I>) const {
    return std::get<I>(*this);
  }
};

using PII = Pair<int, int>;
using PLL = Pair<long long, long long>;
using PSS = Pair<string, string>;

using VLL = vector<PLL>;
using VII = vector<PII>;

template <typename... Args> using VT = vector<Tuple<Args...>>;
template <typename T1, typename T2> using VP = vector<Pair<T1, T2>>;

#endif