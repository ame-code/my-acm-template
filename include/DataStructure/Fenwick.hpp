#include <bits/stdc++.h>
using u32 = unsigned int;
using i64 = long long;
struct Fenwick
{
    std::vector<int> nodes;
    const int N;
    Fenwick(const int size): nodes(size + 1, 0), N(size) {}

    static int lowbit(u32 x) {
        return x & -x;
    }

    void update(int idx, int val) {
        for (int i = idx + 1; i <= N; i += lowbit(i)) {
            nodes[i] += val;
        }
    }

    i64 query(int idx) const {
        i64 res = 0;
        for (int i = idx + 1; i > 0; i -= lowbit(i)) {
            res += nodes[i];
        }
        return res;
    }

    i64 find(i64 val) const {
        i64 res = 0;
        int pos = 0;
        for (i64 pw = 1ll << std::bit_width(u32(N)); pw > 0; pw >>= 1) {
            if (pos + pw <= N && res + nodes[pos + pw] <= val) {
                pos += pw;
                res += nodes[pos];
            }
        }
        return res;
    }
};
