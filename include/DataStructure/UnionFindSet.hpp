#pragma once

#include<vector>

// u32
#include <acm/TypeDef.hpp>

struct UnionFindSet
{
    using UnionIndexType = u32;

    UnionFindSet() = delete;
    explicit UnionFindSet(size_t n):parent(n, 0),rank(n, 0){
        for(size_t i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    UnionFindSet(const UnionFindSet& ufs) = default;
    UnionFindSet(UnionFindSet&&) noexcept = default;
    UnionFindSet& operator=(const UnionFindSet&) = default;
    UnionFindSet& operator=(UnionFindSet&&) noexcept = default;

    UnionIndexType root(UnionIndexType x) {
        return parent[x] = (parent[x] == x ? x : root(parent[x]));
    }

    void merge(UnionIndexType x, UnionIndexType y) {
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
    
private:
    std::vector<UnionIndexType> parent,rank;
};