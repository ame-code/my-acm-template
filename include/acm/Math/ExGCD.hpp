#pragma once
#include <tuple>

template <class T>
struct ExgcdResult {
    T gcd{}, x{}, y{};
};

template <class T>
ExgcdResult<T> exgcd(T a, T b) {
    if (b == 0) {
        return ExgcdResult<T>{a, 1, 0};
    }
    auto [d, x, y] = exgcd(b, a % b);
    return ExgcdResult<T>{d, y, x - (a / b) * y};
};