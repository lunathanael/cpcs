/**
 * Author: Nathanael Lu
 * Source: folklore
 * Description: Combinations of bit manipulations taken from various sources.
 */
#ifndef BITMANIP_H
#define BITMANIP_H

#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;

#define bit(x, i) (x & (1 << i))
#define set_bit(x, i) (x | (1 << i))
#define clear_bit(x, i) (x & ~(1 << i))
#define toggle_bit(x, i) (x ^ (1 << i))

#define lsb(x) ((x) & (-x))
#define clr_lsb(x) (x & (x - 1))
// set last cleared bit of x
#define set_lcb(x) (x | (x + 1))
// clear trailing ones of x
#define clr_to(x) (x & (x + 1))

#define odd(x) ((x) & 1)
#define even(x) (!odd(x))

#define is_pow2(x) (x && !(x & (x - 1)))

// Clears all bits of x from LSB to ith bit
#define clear_left(x, i) (x & ((1 << i) - 1))
// Clears all bits of x from MSB to ith bit
#define clear_right(x, i) (x & (~((1 << (i + 1)) - 1)))

// clears all trailing ones of x
#define clr_to(x) (x & (x + 1))
// clears all trailing zeroes of x
#define clr_tz(x) (~x & (x - 1))

#endif
