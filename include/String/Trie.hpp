#pragma once
#include <bits/stdc++.h>

namespace ASCII
{
using LowerToIdx = decltype(
    [](char ch) -> int {
        return ch - 'a';
    }
);
using UpperToIdx = decltype(
    [](char ch) -> int {
        return ch - 'A';
    }
);
using AlnumToIdx = decltype(
    [](char ch) -> int {
        if (std::isdigit(ch)) return ch - '0';
        if (std::isupper(ch)) return ch - 'A' + 10;
        if (std::islower(ch)) return ch - 'a' + 10 + 26;
        return -1;
    }
);
template <size_t AsciiSize = 26, class TransFunc = LowerToIdx>
struct Trie
{
    using Node = std::array<int, AsciiSize>;
    std::vector<Node> tree;
    std::vector<int> exist;
    size_t cnt;
    TransFunc func;

    Trie(size_t size = 200'000) : tree(size, Node{}), exist(size, 0), cnt(0) {}

    void insert(std::string_view s) {
        int p = 0;
        for (auto ch : s) {
            int c = func(ch);
            if (!tree[p][c]) tree[p][c] = ++cnt;
            p = tree[p][c];
            exist[p]++;
        }
    }
    int search(std::string_view s) const {
        int p = 0;
        for (int i = 0; i < std::ssize(s); i++) {
            int c = s[i] - 'a';
            if (!tree[p][c]) return 0;
            p = tree[p][c];
        }
        return exist[p];
    }
};
} // namespace ASCII

namespace MaxXor
{

template <size_t Bit = 31>
struct Trie
{
    // inline static constexpr size_t Bit = 31;
    struct Node
    {
        std::array<int, 2> son_idx{};
        size_t size{};
    };
    std::vector<Node> tree;
    int cnt{};

    Trie(size_t size = 200'000) : tree(size, Node{}), cnt(0) {}

    void insert(int val) {
        int now = 0;
        tree[now].size++;
        for (int i = Bit - 1; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (!tree[now].son_idx[bit]) tree[now].son_idx[bit] = ++cnt;
            now = tree[now].son_idx[bit];
            tree[now].size++;
        }
    }

    int query(int val) const {
        int now = 0;
        for (int i = Bit - 1; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (!tree[now].son_idx[bit]) return 0;
            now = tree[now].son_idx[bit];
        }
        return tree[now].size;
    }

    int maxXor(int val) const {
        int res = 0, now = 0;
        for (int i = Bit - 1; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (tree[now].son_idx[bit ^ 1])
                res += 1 << i,
                bit ^= 1;
            now = tree[now].son_idx[bit];
        }
        return res;
    }
};

} // namespace MaxXor

namespace AllXor
{

template <size_t Bit = 31>
struct Trie
{
    // inline static constexpr size_t Bit = 31;
    struct Node
    {
        std::array<int, 2> son_idx{};
        size_t size{};
        int xor_val{};
    };
    std::vector<Node> tree;
    int cnt = 0;

    Trie(size_t size = 200'000) : tree(size * Bit, Node{}), cnt{0} {}

    void xorSon(int idx) {
        tree[idx].size = tree[idx].xor_val = 0;
        if (tree[idx].son_idx[0]) {
            tree[idx].size += tree[tree[idx].son_idx[0]].size;
            tree[idx].xor_val ^= tree[tree[idx].son_idx[0]].xor_val << 1;
        }
        if (tree[idx].son_idx[1]) {
            tree[idx].size += tree[tree[idx].son_idx[1]].size;
            tree[idx].xor_val ^= tree[tree[idx].son_idx[1]].xor_val << 1 | (tree[tree[idx].son_idx[1]].size & 1);
        }
        tree[idx].size &= 1;
    }

    void insert(int val) {
        std::vector<int> stack;
        stack.reserve(Bit + 1);
        int now = 0;
        stack.push_back(now);
        for (int i = 0; i < (long)(Bit); i++) {
            int bit = (val >> i) & 1;
            if (tree[now].son_idx[bit] == 0) tree[now].son_idx[bit] = ++cnt;
            now = tree[now].son_idx[bit];
            stack.push_back(now);
        }
        tree[stack.back()].size++;
        stack.pop_back();
        while(stack.size()) {
            xorSon(stack.back());
            stack.pop_back();
        }
    }

    int search(int val) const {
        int now = 0;
        for (int i = 0; i < Bit; i++) {
            int bit = (val >> i) & 1;
            if (!tree[now].son_idx[bit]) return 0;
            now = tree[now].son_idx[bit];
        }
        return tree[now].size;
    }

    void erase(int val) {
        if (search(val) == 0)
            return;
        std::vector<int> stack;
        stack.reserve(Bit + 1);
        int now = 0;
        stack.push_back(now);
        for (int i = 0; i < Bit; i++) {
            int bit = (val >> i) & 1;
            now = tree[now].son_idx[bit];
            stack.push_back(now);
        }
        tree[stack.back()].size--;
        stack.pop_back();
        while (tree.size()) {
            xorSon(stack.back());
            stack.pop_back();
        }
    }

    void add() {
        std::vector<int> stack;
        stack.reserve(Bit + 1);
        int now = 0;
        std::swap(tree[now].son_idx[0], tree[now].son_idx[1]);
        stack.push_back(now);
        while(tree[now].son_idx[0]) {
            now = tree[now].son_idx[0];
            std::swap(tree[now].son_idx[0], tree[now].son_idx[1]);
            stack.push_back(now);
        }
        while(stack.size()) {
            xorSon(stack.back());
            stack.pop_back();
        }
    }

    int allXorValue() const {
        return tree[0].xor_val;
    }
};

} // namespace AllXor
