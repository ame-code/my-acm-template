#pragma once
#ifndef UNIONFINDSET_HEADER
#define UNIONFINDSET_HEADER

// ========================
// 并查集
// 最后修改时间：2025-04-18
// ========================

#include<vector>

class UnionFindSet
{
private:
    std::vector<size_t> parent,rank;
public:
    UnionFindSet() = delete;
    explicit UnionFindSet(size_t n):parent(n, 0),rank(n, 0){
        for(size_t i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    UnionFindSet(const UnionFindSet& ufs):parent(ufs.parent),rank(ufs.rank){}
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

#endif