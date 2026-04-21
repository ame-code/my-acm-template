#pragma once

#include <vector>

// i64
#include <acm/TypeDef.hpp>

// fast_pow
#include <acm/Math/FastPow.hpp>

template <u64 MOD>
i64 inv(i64 x) {
    return fast_pow<MOD>(x, MOD - 2);
}

template <u64 MOD, class T>
std::vector<T> batch_inv(const std::vector<T>& a) {
    const int n = a.size();
    std::vector<T> prod(n);
    i64 s = 1;
    for (int i = 0; i < n; i++) {
        prod[i] = s;
        s = s * a[i] % MOD;
    }
    s = inv<MOD>(s);
    std::vector<T> res(n);
    for (int i = n - 1; i >= 0; i--) {
        res[i] = s * prod[i] % MOD;
        s = s * a[i] % MOD;
    }
    return res;
}

template <u64 MOD>
std::vector<i64> linear_inv(const int n) {
    std::vector<i64> res(n + 1);
    res[1] = 1;
    for (int i = 2; i <= n; i++) {
        res[i] = (MOD - MOD / i) * res[MOD % i] % MOD;
    }
    return res;
}
