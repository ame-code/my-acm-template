#pragma once
#include <bits/stdc++.h>

template <size_t Size = 200'000>
struct Trie
{
    std::vector<std::array<int, 26>> tree;
    std::vector<int> exist;
    size_t cnt;

    Trie() : tree(Size, std::array<int, 26>{}), exist(Size, 0) cnt(0) {}

    void insert(std::string_view s) {
        int p = 0;
        for (auto ch : s) {
            int c = ch - 'a';
            if (!tree[p][c]) tree[p][c] = ++cnt;
            p = tree[p][c];
            exist[p]++;
        }
    }
    int search(std::string_view s) const {
        int p = 0;
        for (int i = 0; i < std::ssize(s); i++) {
            int c = s[i] - 'a';
            if (!tree[p][c]) return false;
            p = tree[p][c];
        }
        return exist[p];
    }
};