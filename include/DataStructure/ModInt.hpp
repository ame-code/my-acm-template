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
    constexpr ModInt(): ModInt(T{}) {}
    constexpr ModInt(T x): num(norm(x % MOD)) {}
    constexpr ModInt(const ModInt&) = default;
    constexpr ModInt& operator=(const ModInt&) = default;

    constexpr T norm(T x) const {
        if (x < 0) x += MOD;
        else if (to_unsigned(x) >= MOD) x -= MOD;
        return x;
    }

    constexpr operator T() const {
        return num;
    }

    constexpr ModInt inv() const {
        return fastModPow<MOD, T>(num, MOD - 2);
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

    constexpr ModInt operator-() const {
        return ModInt(MOD - num);
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
        --(*this);
        return res;
    }

    constexpr ModInt& operator+=(const ModInt& other) {
        num = norm(num + other.num);
        return *this;
    }

    constexpr ModInt& operator-=(const ModInt& other) {
        num = norm(num - other.num);
        return *this;
    }

    constexpr ModInt& operator*=(const ModInt& other) {
        num = i64(num) * other.num % MOD;
        return *this;
    }

    constexpr ModInt& operator/=(const ModInt& other) {
        return *this *= other.inv();
    }

    constexpr ModInt& operator%=(u64 other) {
        return num %= other, *this;
    }

    constexpr ModInt operator+(const ModInt& other) const {return ModInt(num) += other;}

    constexpr ModInt operator-(const ModInt& other) const {return ModInt(num) -= other;}

    constexpr ModInt operator*(const ModInt& other) const {return ModInt(num) *= other;}

    constexpr ModInt operator/(const ModInt& other) const {return ModInt(num) /= other;}
    
    constexpr ModInt operator%(u64 other) const {return ModInt(num) %= other;}
    auto operator<=>(const ModInt& other) const = default;
    bool operator==(const ModInt& other) const = default;
};

template <u64 MOD, class T>
struct std::formatter<ModInt<MOD, T>> : std::formatter<T> {
    using std::formatter<T>::parse;

    template <class Out>
    auto format(const ModInt<MOD, T>& Int, std::basic_format_context<Out, char>& ctx) const {
        return std::formatter<T>::format(Int.num, ctx);
    }
};

/*

template <u64 MOD = 998'244'353, class T = i64>
struct ModInt
{
    #define CE constexpr
    #define C const
    #define CR const ModInt&
    #define OP operator

    T num;
    CE ModInt(): ModInt(T{}) {}
    CE ModInt(T x): num(norm(x % MOD)) {}

    CE ModInt(CR) = default;
    CE ModInt& operator=(CR) = default;
    auto operator<=>(CR) C = default;
    bool operator==(CR) C = default;

    CE T norm(T x) C {
        if (x < 0) x += MOD;
        else if (to_unsigned(x) >= MOD) x -= MOD;
        return x;
    }

    CE explicit operator T() C { return num; }

    CE ModInt inv() C { return fastModPow<MOD, T>(num, MOD - 2); }

    friend auto& operator>>(std::istream& is, ModInt& n) {
        is >> n.num;
        n.num %= MOD;
        n.num = n.norm(n.num);
        return is;
    }

    friend auto& operator<<(std::ostream& os, const ModInt& n) {
        return os << n.num;
    }

    CE ModInt operator-() C {
        return ModInt(MOD - num);
    }

    #define OP1(A) CE ModInt OP##A##A##() { \
        num = norm(num A 1); \
        return *this; \
    } \
    CE ModInt OP##A##A##(int) { \
        auto res = *this; \
        A##A##(*this); \
        return *this; \
    }

    OP1(+) OP1(-)

    #define OP2(A) CE ModInt& OP##A##=(CR o) { \
        num = norm(num A o.num); \
        return *this; \
    } \
    CE ModInt OP##A(CR o) C { return ModInt(num) A##= o; }

    // + - * / % 
    // regex: from "(.) ", to "OP2($1) "
    OP2(+) OP2(-) OP2(*) OP2(/) OP2(%) 

    // CE C CR OP OP1 OP2
    // regex: from "(\w+)", to "#undef $1 [shift + enter]"
    #undef CE
    #undef C
    #undef CR
    #undef OP
    #undef OP1
    #undef OP2
};

*/