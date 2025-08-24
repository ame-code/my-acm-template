#pragma once
#include<vector>

struct UnionFindSet
{
    std::vector<size_t> parent,rank;
    UnionFindSet() = delete;
    explicit UnionFindSet(size_t n):parent(n, 0),rank(n, 0){
        for(size_t i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    UnionFindSet(const UnionFindSet& ufs) = default;
    UnionFindSet(UnionFindSet&&) = default;
    UnionFindSet& operator=(UnionFindSet&&) = default;

    size_t root(size_t x) {
        return parent[x] = (parent[x] == x ? x : root(parent[x]));
    }

    void merge(int x, int y) {
        x = root(x), y = root(y);
        if(x == y)
            return;
        if(rank[x] < rank[y])
            parent[x] = y;
        else {
            parent[y] = x;
            if(rank[x] == rank[y]) {
                rank[x]++;
            }
        }
    }
};