#pragma once
#include <bits/stdc++.h>

// 最小表示法: 对于字符串s,如果s[i..n] + s[1..i-1] = t,则称s与t循环同构,找到与S循环同构的字符串中字典序最小的字符串

template<class T>
size_t minLexRotator(std::string_view arr) {
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