#pragma once

#include <bits/stdc++.h>
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned i64;
using i128 = __int128_t;
using u128 = __uint128_t;
template <class T>
using ref = T&;
template <class T>
using cref = const T&;
template <class T> struct ParamTypeImpl {using type = T;};
template <class T> requires (sizeof(T) <= 16)
struct ParamTypeImpl<T> {using type = const T&;};
template <class T> using ParamType = ParamTypeImpl<T>::type;