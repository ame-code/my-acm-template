#pragma once
#include <bits/stdc++.h>

namespace Trie
{
struct LowerToIndex {
    int operator()(char ch) const {
        return ch - 'a';
    }
};

struct UpperToIndex {
    int operator()(char ch) const {
        return ch - 'A';
    }
};

struct AlphaToIndex {
    int operator()(char ch) const {
        if (std::isupper(ch)) {
            return ch - 'A';
        } else {
            return ch - 'a' + 'A';
        }
    }
};

struct AlnumToIndex {
    int operator()(char ch) const {
        if (std::isdigit(ch)) {
            return ch - '0';
        } else if (std::isupper(ch)) {
            return ch - 'A' + '0';
        } else {
            return ch - 'a' + '0' + 'A';
        }
    }
};

template <int ASCIISize = 26, class MapFunc = LowerToIndex>
struct ASCII
{
    using Node = std::array<int, ASCIISize>;

    ASCII(int size): tree(size, Node{}), exist(size, 0), cnt(0), mapFunc(MapFunc{}) {}

    void insert(std::string_view s) {
        int p = 0;
        for (auto ch : s) {
            int c = mapFunc(ch);
            if (!tree[p][c]) tree[p][c] = ++cnt;
            p = tree[p][c];
            exist[p]++;
        }
    }

    int search(std::string_view s) const {
        int p = 0;
        for (auto ch : s) {
            int c = mapFunc(ch);
            if (!tree[p][c]) return 0;
            p = tree[p][c];
        }
        return exist[p];
    }

private:
    std::vector<Node> tree;
    std::vector<int> exist;
    int cnt;
    [[no_unique_address]] MapFunc mapFunc;
};

template <int BitSize = 31>
struct MaxXor {
    struct Node {
        std::array<int, 2> son_idx{};
        int size{};
    };

    MaxXor(int size): tree(size, Node{}), cnt(0) {}

    void insert(int val) {
        int p = 0;
        tree[p].size++;
        for (int i = Bit - 1; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (!tree[p].son_idx[bit]) tree[p].son_idx[bit] = ++cnt;
            p = tree[p].son_idx[bit];
            tree[p].size++;
        }
    }

    int query(int val) const {
        int p = 0;
        for (int i = Bit - 1; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (!tree[p].son_idx[bit]) return 0;
            p = tree[p].son_idx[bit];
        }
        return tree[p].size;
    }

    int maxXor(int val) const {
        int res = 0, p = 0;
        for (int i = Bit - 1; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (tree[p].son_idx[bit ^ 1]) {
                res += 1 << i;
                bit ^= 1;
            }
            p = tree[p].son_idx[bit];
        }
        return res;
    }

private:
    std::vector<Node> tree;
    int cnt{};
};


template <size_t Bit = 31>
struct AllXor
{
    struct Node
    {
        std::array<int, 2> son_idx{};
        int size{};
        int xor_val{};
    };

    AllXor(size_t size = 200'000) : tree(size * Bit, Node{}), cnt{0} {}

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
private:
    std::vector<Node> tree;
    int cnt = 0;
};

} // namespace Trie