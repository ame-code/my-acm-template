#pragma once
#include <bits/stdc++.h>

template <char splitChar = '#'>
struct Manacher
{
    std::string str;
    std::vector<int> find(std::string_view s) {
        str.reserve(s.size() << 1 | 1);
        str.push_back(splitChar);
        for (auto ch : s) str.push_back(ch), str.push_back(splitChar);

        auto d = std::vector<int>(str.size());
        for (int i{}, l{}, r{}; i < std::ssize(d); i++) {
            int k = (i > r) ? 1 : std::min(d[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < std::ssize(d) && str[i - k] == str[i + k])
                k++;
            d[i] = k--;
            if (i + k > r) l = i - k, r = i + k;
        }
        return d;
    }
};
