#pragma once
#include <bits/stdc++.h>
#include <acm_template/TypeDef.h>
#include <acm_template/Math/FastPow.hpp>

template <auto Mod = 998244353l, class T = decltype(Mod)>
struct ModInt
{
    T num;
    constexpr ModInt() : ModInt(T{}) {}
    constexpr ModInt(T x) : num(norm(x % Mod)) {}
    constexpr ModInt(cref<ModInt>) = default;
    constexpr ModInt(ModInt&&) noexcept = default;
    constexpr ModInt& operator=(cref<ModInt>) = default;
    constexpr ModInt& operator=(ModInt&&) noexcept = default;

    constexpr T norm(T x) const {
        [[unlikely]] if (x < 0) x += Mod;
        else [[unlikely]] if (x >= Mod) x -= Mod;
        return x;
    }
    constexpr explicit operator T() const {return num;}
    constexpr ModInt inv() const {return fastPow(num, Mod - 2);}

    friend auto& operator>>(std::istream& is, ModInt& modint) {
        T x; is >> x; modint.num = modint.norm(x);
        return is;
    }
    friend auto& operator<<(std::ostream& os, ParamType<ModInt> modint) {
        return os << modint.num;
    }
    constexpr ModInt operator-() const {
        return ModInt(Mod - num);
    }
    constexpr ModInt& operator++() {
        num = norm(num + 1);
        return *this;
    }
    constexpr ModInt operator++(int) {
        auto res = *this;
        ++(*this);
        return res;
    }
    constexpr ModInt& operator--() {
        num = norm(num - 1);
        return *this;
    }
    constexpr ModInt operator--(int) {
        auto res = *this;
        ++(*this);
        return res;
    }
    constexpr ModInt& operator+=(cref<ModInt> other) {
        num = norm(num + other.num);
        return *this;
    }
    constexpr ModInt& operator-=(cref<ModInt> other) {
        num = norm(num - other.num);
        return *this;
    }
    constexpr ModInt& operator*=(cref<ModInt> other) {
        num = i64(num) * other.num % Mod;
        return *this;
    }
    constexpr ModInt& operator/=(cref<ModInt> other) {
        return *this *= other.inv();
    }
    template <std::integral Int>
    constexpr ModInt& operator%=(Int other) {
        return num %= other, *this;
    }
    constexpr ModInt operator+(cref<ModInt> other) const {return ModInt(num) += other;}
    constexpr ModInt operator-(cref<ModInt> other) const {return ModInt(num) -= other;}
    constexpr ModInt operator*(cref<ModInt> other) const {return ModInt(num) *= other;}
    constexpr ModInt operator/(cref<ModInt> other) const {return ModInt(num) /= other;}
    template <std::integral Int>
    constexpr ModInt operator%(Int other) const {return ModInt(num) %= other;}
    auto operator<=>(cref<ModInt> other) const = default;
    bool operator==(cref<ModInt> other) const = default;
};
