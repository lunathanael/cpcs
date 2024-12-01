/**
 * Author: Nathanael Lu
 * Source: folklore
 * Description: Combinations of bit manipulations taken from various sources.
 */
#ifndef BITMANIP_H
#define BITMANIP_H

#define bit(x, i) (x & (1 << i))
#define lowbit(x) ((x) & (~(x - 1)))
#define clr_lowbit(x) (x & (x - 1))

#define odd(x) ((x) & 1)
#define even(x) (!odd(x))

#define is_pow2(x) (x && !(x & (x - 1)))

#endif
