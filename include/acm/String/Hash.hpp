#pragma once
#include <bits/stdc++.h>

#include <acm/TypeDef.hpp>
#include <acm/DataStructure/ModInt.hpp>

template <i64 Base, class T = i64>
struct PowerBase
{
    inline static std::vector<T> powerBase = std::vector<T>(1, 1);
    PowerBase(size_t n) {
        Init(n);
    }
    PowerBase& Init(size_t n) {
        std::size_t prev_size = powerBase.size();
        powerBase.resize(std::max(prev_size, n + 1));
        for (std::size_t i = prev_size; i <= n; i++) {
            powerBase[i] = powerBase[i - 1] * Base;
        }
        return *this;
    }
};

template <i64 Mod, i64 Base>
struct Hash : PowerBase<Base, ModInt<Mod>>
{
    std::vector<ModInt<Mod>> hash;

    template <class T, std::size_t Extent>
    Hash(std::span<T, Extent> s) : PowerBase<Base, ModInt<Mod>>(s.size()), hash(1 + s.size()) {
        for (int i = 1; i <= std::ssize(s); i++) {
            hash[i] = hash[i - 1] * Base + s[i - 1];
        }
    }

    Hash(const Hash&) = default;
    Hash(Hash&&) noexcept = default;

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

    template <class T, std::size_t Extent>
    DoubleHash(std::span<T, Extent> s) : hash_1(s), hash_2(s) {}
    std::pair<i64, i64> get(int l, int r) {
        return {hash_1.get(l, r), hash_2.get(l, r)};
    }
};