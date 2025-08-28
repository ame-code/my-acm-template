#pragma once
#include <bits/stdc++.h>

struct ExtendKMP {
    std::vector<int> operator()(std::string_view s) const {
        std::vector<int> z(s.size(), 0);
        int n = s.size();
        for (int i{1}, l{}, r{}; i < n; i++) {
            if (i > r)
                z[i] = 0;
            else
                z[i] = std::min(z[i - l], r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                z[i]++;
            if (i + z[i] - 1 > r)
                l = i, r = i + z[i] - 1;
        }
        return z;
    }
};