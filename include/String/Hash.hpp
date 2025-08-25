#pragma once
#include <acm_template/TypeDef.h>
#include <bits/stdc++.h>
#include <dev/DataStructure/ModInt.hpp>

template <i64 Base, class T = i64>
struct PowerBase
{
    inline static std::vector<T> powerBase = std::vector<T>();
    PowerBase(size_t n) {
        Init(n);
    }
    PowerBase& Init(size_t n) {
        powerBase.resize(n + 1);
        powerBase[0] = 1;
        for (
            int i = 1;
            i <= i64(n);
            i++
        ) {
            powerBase[i] = powerBase[i - 1] * Base;
        }
        return *this;
    }
};

template <i64 Mod, i64 Base>
struct Hash : PowerBase<Base, ModInt<Mod>>
{
    std::vector<ModInt<Mod>> hash;
    Hash(const std::string& s) : PowerBase<Base, ModInt<Mod>>(s.size()), hash(1 + s.size()) {
        for (int i = 1; i <= std::ssize(s); i++) {
            hash[i] = hash[i - 1] * Base + s[i - 1];
        }
    }
    i64 get(int l, int r) const {
        return i64(hash[r + 1] - hash[l] * PowerBase<Base, ModInt<Mod>>::powerBase[r - l + 1]);
    }
};

template <
    i64 Mod1 = 1'000'000'007ll, i64 Base1 = 131ll, 
    i64 Mod2 = 1'000'000'009ll, i64 Base2 = 13331l
>
struct DoubleHash
{
    Hash<Mod1, Base1> hash_1;
    Hash<Mod2, Base2> hash_2;
    DoubleHash(const std::string& s) : hash_1(s), hash_2(s) {}
    std::pair<i64, i64> get(int l, int r) {
        return {hash_1.get(l, r), hash_2.get(l, r)};
    }
};