#pragma once
#include <bits/stdc++.h>

// 循环实现
template<std::integral Int = int>
Int fastPow(Int base, Int index) {
    Int ret = 1;
    for (; index; index >>= 1, base *= base) {
        if (index & 1) ret *= base;
    }
    return ret;
}

// 带模运算的循环实现
template<std::integral Int = int>
Int fastPow(Int base, Int index, Int mod) {
    Int ret = 1;
    base %= mod;
    for (; index; index >>= 1, base = base * base % mod) {
        if (index & 1) ret = ret * base % mod;
    }
    return ret;
}