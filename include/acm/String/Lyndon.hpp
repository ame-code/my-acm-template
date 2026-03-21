#pragma once
#include <bits/stdc++.h>

// Lydon串: 字符串 s 的字典序严格小于s的所有后缀
// Lydon分解: 字符串 s = w_1 w_2 w_3 .. w_k,其中w_i为Lydon串,且字典序w_i >= w_i+1,这样的分解成为Lydon分解,这样的分解存在且唯一
std::vector<std::string> lyndon(std::string_view s)  {
    int n = s.size(), i = 0;
    std::vector<std::string> factorization;
    while (i < n) {
    int j = i + 1, k = i;
    while (j < n && s[k] <= s[j]) {
        if (s[k] < s[j])
        k = i;
        else
        k++;
        j++;
    }
    while (i <= k) {
        factorization.emplace_back(s.substr(i, j - k));
        i += j - k;
    }
    }
    return factorization;
}