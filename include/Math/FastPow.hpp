#pragma once
#include <bits/stdc++.h>

// 循环实现
template<class Int = int>
constexpr Int fastPow(Int base, Int power) {
    Int ret = 1;
    for (; power; power /= 2, base *= base) {
        if (power % 2) ret *= base;
    }
    return ret;
}

// 带模运算的循环实现
template<class Int = int>
constexpr Int fastPow(Int base, Int power, Int mod) {
    Int ret = 1;
    base %= mod;
    for (; power; power /= 2, base = base * base % mod) {
        if (power % 2) ret = ret * base % mod;
    }
    return ret;
}