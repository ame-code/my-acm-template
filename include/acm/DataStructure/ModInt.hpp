#pragma once
#include <bits/stdc++.h>

// i64
#include <acm/TypeDef.hpp>

// fastModPow
#include <acm/Math/FastPow.hpp>

// to_unsigned
#include <acm/type_traits.hpp>

template <u64 MOD = 998'244'353, class T = i64>
struct ModInt
{
    T num;
    ModInt(): ModInt(T{}) {}
    ModInt(T x): num(norm(x % MOD)) {}
    ModInt(const ModInt&) = default;
    ModInt& operator=(const ModInt&) = default;

    T norm(T x) const {
        if (x < 0) x += MOD;
        else if (to_unsigned(x) >= MOD) x -= MOD;
        return x;
    }

    explicit operator T() const {
        return num;
    }

    ModInt inv() const {
        return fast_pow<MOD, T>(num, MOD - 2);
    }

    friend auto& operator>>(std::istream& is, ModInt& mod_int) {
        is >> mod_int.num;
        mod_int.num %= MOD;
        mod_int.num = mod_int.norm(mod_int.num);
        return is;
    }

    friend auto& operator<<(std::ostream& os, const ModInt& mod_int) {
        return os << mod_int.num;
    }

    ModInt operator-() const {
        return ModInt(MOD - num);
    }

    /*
    @=[+,-]
    ModInt& operator@@() {
        num = norm(num + 1);
        return *this;
    }
    ModInt operator@@(int) {
        auto res = *this;
        @@(*this);
        return res;
    }
    */
    ModInt& operator++() {
        num = norm(num + 1);
        return *this;
    }
    ModInt operator++(int) {
        auto res = *this;
        ++(*this);
        return res;
    }
    ModInt& operator--() {
        num = norm(num - 1);
        return *this;
    }
    ModInt operator--(int) {
        auto res = *this;
        --(*this);
        return res;
    }

    ModInt& operator+=(const ModInt& other) {
        num = norm(num + other.num);
        return *this;
    }
    ModInt& operator-=(const ModInt& other) {
        num = norm(num - other.num);
        return *this;
    }
    ModInt& operator*=(const ModInt& other) {
        num = num * other.num % MOD;
        return *this;
    }
    ModInt& operator/=(const ModInt& other) {
        return *this *= other.inv();
    }
    ModInt& operator%=(u64 other) {
        return num %= other, *this;
    }

    /*
    @=[+,-,*,/,%]
    ModInt operator@(const ModInt& other) const {return ModInt(num) @= other;}
    */
    ModInt operator+(const ModInt& other) const {return ModInt(num) += other;}
    ModInt operator-(const ModInt& other) const {return ModInt(num) -= other;}
    ModInt operator*(const ModInt& other) const {return ModInt(num) *= other;}
    ModInt operator/(const ModInt& other) const {return ModInt(num) /= other;}
    ModInt operator%          (u64 other) const {return ModInt(num) %= other;}
    auto operator<=>(const ModInt& other) const = default;
    bool operator== (const ModInt& other) const = default;
};

template <u64 MOD, class T>
struct std::formatter<ModInt<MOD, T>> : std::formatter<T> {
    using std::formatter<T>::parse;

    template <class Out>
    auto format(const ModInt<MOD, T>& Int, std::basic_format_context<Out, char>& ctx) const {
        return std::formatter<T>::format(Int.num, ctx);
    }
};