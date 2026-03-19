#pragma once

#include <type_traits>
#include <acm/TypeDef.hpp>

template <class T>
auto to_unsigned(T Int) {
    return std::make_unsigned_t<T>(Int);
}

u128 to_unsigned(const i128& Int) {
    return u128(Int);
}

u128 to_unsigned(const u128& Int) {
    return Int;
}

template <class T>
auto to_signed(T Int) {
    return std::make_signed_t<T>(Int);
}

i128 to_signed(const i128& Int) {
    return Int;
}

i128 to_signed(const u128& Int) {
    return i128(Int);
}