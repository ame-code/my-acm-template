#pragma once
#include <bits/stdc++.h>

struct Lyndon {
    std::vector<std::string> operator()(std::string_view s) const  {
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
};
using Duval = Lyndon;