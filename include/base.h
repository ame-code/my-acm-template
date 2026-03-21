#pragma once

#include <bits/stdc++.h>
#include <acm/TypeDef.hpp>
template <class T>
constexpr auto limit_min = std::numeric_limits<int>::min();
template <class T>
constexpr auto limit_max = std::numeric_limits<int>::max();
std::array<char, 1 << 10 << 10 << 3> cin_buffer{};
std::array<char, 1 << 10 << 10 << 3> cout_buffer{};
void solve();
void preProcess() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.rdbuf()->pubsetbuf(cin_buffer.data(), cin_buffer.size());
    std::cout.rdbuf()->pubsetbuf(cout_buffer.data(), cout_buffer.size());
}
#define SINGLE_SOLVE int main() {\
    preProcess();\
    solve();\
}
#define MULTI_SOLVE int main() {\
    preProcess();\
    int t = 1;\
    std::cin >> t;\
    while (t--) solve();\
}
