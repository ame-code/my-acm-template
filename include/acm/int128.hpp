#pragma once

#include <iostream>
#include <string>
#include <algorithm>

using i128 = __int128_t;
using u128 = __uint128_t;

std::istream& operator>>(std::istream& is, i128& n) {
    std::string s;
    if (!(is >> s)) return is;

    n = 0;
    std::size_t i = 0;
    bool negetive = false;

    if (s[0] == '-') {
        negetive = true;
        i = 1;
    } else if (s[0] == '+') {
        i = 1;
    }

    for (; i < s.size(); i++) {
        if (isdigit(s[i])) {
            n = n * 10 + (s[i] - '0');
        } else [[unlikely]] {
            is.setstate(std::ios::failbit);
            break;
        }
    }

    if (negetive) n = -n;
    return is;
}

std::istream& operator>>(std::istream& is, u128& n) {
    std::string s;
    if (!(is >> s)) return is;

    n = 0;
    std::size_t i = 0;

    if (s[0] == '-') {
        is.setstate(std::ios::failbit);
        return is;
    } else if (s[0] == '+') {
        i = 1;
    }

    for (; i < s.size(); i++) {
        if (isdigit(s[i])) {
            n = n * 10 + (s[i] - '0');
        } else [[unlikely]] {
            is.setstate(std::ios::failbit);
            break;
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, i128 n) {
    if (n == 0) return os << "0";
    if (n < 0) {
        os << "-";
        n = -n;
    }
    std::string s;
    while (n > 0) {
        s += (char)('0' + (n % 10));
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}

std::ostream& operator<<(std::ostream& os, u128 n) {
    if (n == 0) return os << "0";
    std::string s;
    while (n > 0) {
        s += (char)('0' + (n % 10));
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}