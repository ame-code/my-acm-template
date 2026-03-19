#include <bits/stdc++.h>
#include <acm/TypeDef.hpp>

namespace FenwickTree
{
    
u32 lowbit(u32 x) {
    return x & -x;
}

template <class T>
struct PointUpdateRangeQuery
{
    PointUpdateRangeQuery(const u32 size): tree(size + 1) {}
    PointUpdateRangeQuery(const std::vector<T>& data): tree(data.size() + 1) {
        for (int i = 0; i < std::ssize(data); i++) {
            update(i, data[i]);
        }
    }

    void update(const int idx, const T& val) {
        for (int i = idx + 1; i < std::ssize(tree); i += lowbit(i)) {
            tree[i] += val;
        }
    }

    T query(int idx) const {
        T res{};
        for (int i = idx + 1; i > 0; i -= lowbit(i)) {
            res += tree[i];
        }
        return res;
    }

    T query(int begin, int end) const {
        return query(end - 1) - query(begin - 1);
    }

private:
    std::vector<T> tree;
};

template <class T>
using PURQ = PointUpdateRangeQuery<T>;

template <class T>
struct RangeUpdatePointQuery
{
    RangeUpdatePointQuery(const u32 size): tree(size + 1) {}
    RangeUpdatePointQuery(const std::vector<T>& data): tree(data.size() + 1) {
        for (int i = 0; i < std::ssize(data); i++) {
            update(i, data[i]);
        }
    }

    void update(const int idx, const T& val) {
        update(idx, idx + 1, val);
    }

    void update(const int begin, const int end, const T& val) {
        for (int i = begin + 1; i <= std::ssize(tree); i += lowbit(i)) {
            tree[i - 1] += val;
        }
        for (int i = end + 1; i <= std::ssize(tree); i += lowbit(i)) {
            tree[i - 1] -= val;
        }
    }

    T query(const int idx) const {
        T res{};
        for (int i = idx + 1; i > 0; i -= lowbit(i)) {
            res += tree[i - 1];
        }
        return res;
    }

private:
    std::vector<T> tree;
};

template <class T>
using RUPQ = RangeUpdatePointQuery<T>;

} // namespace FenwickTree