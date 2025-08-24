#pragma once
#include <bits/stdc++.h>
#include <acm_template/TypeDef.h>

struct BigInt
{
    using number_type = std::vector<int>;
    using sign_type = int;

    inline static constexpr size_t base = 1'000'000'000;
    inline static constexpr size_t base_digits = 9;
    sign_type sign{1};
    number_type number;

    BigInt() : number{} {}
    template <std::integral T>
    BigInt(T num) : sign(num < 0 ? (num = -num, -1) : 1), number{int(num % base), int(num / base)} {remove_leading_zero();}
    BigInt(const std::string& str) {std::istringstream(str) >> (*this);}
    BigInt(const BigInt& num) = default;
    BigInt(BigInt&& num) = default;
    BigInt& operator=(const BigInt&) = default;
    BigInt& operator=(BigInt&&) = default;

    auto operator<=>(const BigInt& other) const {
        if (
            const auto cmp = sign <=> other.sign;
            cmp != 0
        )
            return cmp;
        if (auto cmp = (number.size() <=> other.number.size()); cmp != 0)
            return cmp;
        return std::lexicographical_compare_three_way(
            number.rbegin(), number.rend(),
            other.number.rbegin(), other.number.rend()
        );
    }
    bool operator==(const BigInt& other) const = default;

    void remove_leading_zero() {
        while (number.empty() == false && number.back() == 0)
            number.pop_back();
        sign = number.empty() ? 1 : sign;
    }

    friend BigInt abs(const BigInt& num) {
        auto tmp = num;
        tmp.sign = 1;
        return tmp;
    }
    
    static std::vector<i64> karatsuba(const std::vector<i64>& a, const std::vector<i64>& b) {
        const auto n = std::ssize(a);
        std::vector<i64> res(n << 1, 0);
        if (n <= 32) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res[i + j] += a[i] * b[j];
            return res;
        }

        const auto k = n >> 1;
        std::vector<i64>
            a1(a.begin(), a.begin() + k),
            a2(a.begin() + k, a.end()),
            b1(b.begin(), b.begin() + k),
            b2(b.begin() + k, b.end());

        const auto 
            a1b1 = karatsuba(a1, b1),
            a2b2 = karatsuba(a2, b2);

        for (int i = 0; i < k; i++)
            a2[i] += a1[i];
        for (int i = 0; i < k; i++)
            b2[i] += b1[i];

        auto c = karatsuba(a2, b2);
        for (int i = 0; i < std::ssize(a1b1); i++)
            c[i] -= a1b1[i];
        for (int i = 0; i < std::ssize(a2b2); i++)
            c[i] -= a2b2[i];

        for (int i = 0; i < std::ssize(a1b1); i++)
            res[i] += a1b1[i];
        for (int i = 0; i < std::ssize(c); i++)
            res[i + k] += c[i];
        for (int i = 0; i < std::ssize(a2b2); i++)
            res[i + n] += a2b2[i];

        return res;
    }

    template<std::integral T, std::integral U>
    static std::vector<T> convert_base(const std::vector<U>& a, const int old_digits, const int new_digits) {
        std::vector<u64> pow(new_digits + 1);
        pow[0] = 1;
        for (int i = 1; i <= new_digits; i++)
            pow[i] = pow[i - 1] * 10;

        std::vector<T> res;
        res.reserve((std::ssize(a) * old_digits + new_digits - 1) / new_digits + 1);
        
        i64 cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < std::ssize(a); i++) {
            cur += a[i] * pow[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back((T)(cur % pow[new_digits]));
                cur /= pow[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((T)(cur));
        while (res.empty() == false && res.back() == 0)
            res.pop_back();

        return res;
    }

    friend std::pair<BigInt, BigInt> divmod(
        const BigInt& a,
        const BigInt& b
    ) {
        int norm = base / (b.number.back() + 1);
        BigInt
            x = abs(a) * norm,
            y = abs(b) * norm,
            quot, rem;
        quot.number.resize(x.number.size());
        rem.number.reserve(y.number.size() + 1);
        for (int i = std::ssize(x.number) - 1; i >= 0; i--) {
            rem *= base;
            rem += x.number[i];
            int 
                s1 = (rem.number.size() > y.number.size() ? rem.number[y.number.size()] : 0),
                s2 = (rem.number.size() > y.number.size() - 1 ? rem.number[y.number.size() - 1] : 0);
            int d = (i64(base) * s1 + s2) / y.number.back();
            rem -= y * d;
            while (rem < 0)
                rem += b, d--;
            quot.number[i] = d;
        }

        quot.sign = a.sign * b.sign;
        rem.sign = a.sign;
        quot.remove_leading_zero();
        rem.remove_leading_zero();
        return std::make_pair(quot, rem / norm);
    }

    friend std::istream& operator>>(std::istream& is, BigInt& num) {
        std::string str;
        is >> str;
        num.sign = 1;
        size_t pos = 0;
        while (pos < str.length() && (str[pos] == '-' || str[pos] == '+')) {
            if (str[pos] == '-') num.sign = -1;
            pos++;
        }
        for (int i = int(str.length()) - 1; i >= i64(pos); i -= BigInt::base_digits) {
            u32 tmp = 0;
            for (int j = std::max(i64(pos), i - i64(BigInt::base_digits) + 1); j <= i; j++)
                (tmp *= 10) += (str[j] - '0');
            num.number.push_back(tmp);
        }
        num.remove_leading_zero();
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num) {
        auto& [sign, number] = num;
        if (num.number.empty() == true)
            return os << '0';

        if (num.sign == -1)
            os << '-';
        os << (num.number.empty() ? 0 : num.number.back());
        for (int i = std::ssize(num.number) - 2; i >= 0; i--)
            os << std::setw(BigInt::base_digits) << std::setfill('0') << number[i];

        return os;
    }

    BigInt operator-() const {
        auto res = *this;
        res.sign = -sign;
        return res;
    }

    BigInt operator+(const BigInt& other) const {
        if (sign != other.sign)
            return *this - (-other);

        auto res = BigInt{};
        res.sign = this->sign;
        const auto& [shorter, longer] =
            number.size() < other.number.size() ? 
            std::tie(this->number, other.number) :
            std::tie(other.number, this->number);
        res.number.resize(longer.size() + 1);
        
        number_type& res_num = res.number;
        i64 short_len = shorter.size();
        for (int i = 0; i < short_len; i++)
            res_num[i] = shorter[i] + longer[i];
        std::ranges::copy(longer.begin() + short_len, longer.end(), res_num.begin() + short_len);
        for (int i = 0, rem = 0; i < std::ssize(res_num) || rem != 0; i++) {
            res_num[i] += rem;
            rem = res_num[i] >= i64(base);
            if (rem)
                res_num[i] -= base;
        }
        res.remove_leading_zero();

        return res;
    }

    BigInt operator-(const BigInt& other) const {
        if (sign != other.sign)
            return *this + (-other);

        if (abs(*this) < abs(other))
            return -(other - *this);
        
        
        const auto& [subed_num, sub_num] = std::tie(number, other.number);

        auto res = BigInt(0);
        res.sign = this->sign;
        auto& res_num = res.number;
        res_num.resize(subed_num.size() + 1);
        auto len = std::ssize(sub_num);;
        for (int i = 0; i < len; i++)
            res_num[i] = subed_num[i] - sub_num[i];
        
        std::ranges::copy(subed_num.begin() + len, subed_num.end(), res_num.begin() + len);
        for (int i = 0, rem = 0; i < std::ssize(res_num) || rem; i++) {
            res_num[i] -= rem;
            rem = res_num[i] < 0;
            if (rem) {
                res_num[i] += base;
            }
        }

        res.remove_leading_zero();

        return res;
    }

    BigInt operator*(const BigInt& other) const {
        std::vector<i64>
            a6 = convert_base<i64>(number, base_digits, 6),
            b6 = convert_base<i64>(other.number, base_digits, 6);
        const auto max_n = std::bit_ceil(std::ranges::max(a6.size(), b6.size()));
        a6.resize(max_n), b6.resize(max_n);
        auto c = karatsuba(a6, b6);
        BigInt res;
        res.sign = sign * other.sign;
        res.number.reserve((std::ssize(c) * 6 + base_digits - 1) / base_digits);
        for (int i = 0, rem = 0; i < std::ssize(c); i++) {
            i64 cur = c[i] + rem;
            res.number.push_back(int(cur % 1'000'000));
            rem = int(cur / 1'000'000);
        }
        res.number = convert_base<int>(res.number, 6, base_digits);
        res.remove_leading_zero();

        return res;
    }

    BigInt operator/(int num) const {
        BigInt res = *this;
        res.sign *= (num < 0 ? -1 : 1);
        num *= (num < 0 ? -1 : 1);
        for (int i = std::ssize(res.number) - 1, rem = 0; i >= 0; i--) {
            i64 cur = res.number[i] + rem * i64(base);
            res.number[i] = int(cur / num);
            rem = int(cur % num);
        }
        res.remove_leading_zero();
        return res;
    }

    BigInt& operator/=(int num) {
        return *this = *this / num;
    }

    BigInt operator/(i64 num) const {
        return *this / BigInt(num);
    }

    BigInt& operator/=(i64 num) {
        return *this /= BigInt(num);
    }

    BigInt operator/(const BigInt& other) const {
        return divmod(*this, other).first;
    }

    BigInt operator%(const BigInt& other) const {
        return divmod(*this, other).second;
    }

    BigInt& operator+=(const BigInt& num) {
        return *this =  *this + num;
    }

    BigInt& operator-=(const BigInt&& num) {
        return *this = *this - num;
    }

    BigInt& operator*=(const BigInt&& num) {
        return *this = *this * num;
    }

    BigInt& operator/=(const BigInt&& num) {
        return *this = *this / num;
    }

    BigInt& operator%=(const BigInt&& num) {
        return *this = *this % num;
    }
};