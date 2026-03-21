#pragma once

#include <acm/TypeDef.hpp>

template <class T>
T fastPow(T base, u64 power) {
    T res = 1;
    for (; power; power >>= 1, base *= base) {
        if (power & 1) {
            res *= base;
        }
    }
    return res;
}

template <u64 MOD = 998'244'353, class T>
T fastModPow(T base, u64 power) {
    T res = 1;
    for (base %= MOD; power; power >>= 1, base = base * base % MOD) {
        if (power & 1) {
            res = res * base % MOD;
        }
    }
    return res;
}

template <class T>
T fastModPow(T base, u64 power, u64 MOD) {
    T res = 1;
    for (base %= MOD; power; power >>= 1, base = base * base % MOD) {
        if (power & 1) {
            res = res * base % MOD;
        }
    }
    return res;
}
