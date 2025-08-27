#pragma once
#include <bits/stdc++.h>

struct MinLexRotator {
    template<class T>
    size_t operator()(std::string_view arr) const {
        size_t i{}, j{1}, k{0};
        size_t n = arr.size();
        while (i < n && j < n && k < n) {
            if (arr[(i + k) % n] == arr[(j + k) % n])
                k++;
            else {
                if (arr[(i + k) % n] > arr[(j + k) % n]) 
                    i += k + 1;
                else
                    j += k + 1;
                i += (i == j);
                k = 0;
            }
        }
        return std::min(i, j);
    }
};