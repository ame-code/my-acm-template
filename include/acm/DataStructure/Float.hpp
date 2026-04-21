#pragma once

#include <cmath>
#include <iostream>
#include <utility>

template <class T = double, T Eps = 1e-7>
struct EpsFloat
{
private:
    using cr = const EpsFloat&;
    using r  = EpsFloat&;
    using s  = EpsFloat;

public:
    using value_type = T;
    T num;

    EpsFloat(): num() {}
    EpsFloat(T num_): num(num_) {}
    EpsFloat(const EpsFloat&) = default;
    EpsFloat& operator=(const EpsFloat&) = default;

    explicit operator bool() const {
        return std::abs(num) <= Eps;
    }

    bool operator!() const {
        return !bool(*this);
    }

    EpsFloat operator-() const {
        return {-num};
    }

    EpsFloat& operator++() {
        num++;
        return *this;
    }
    EpsFloat operator++(int) {
        EpsFloat result = *this;
        num++;
        return result;
    }
    EpsFloat& operator--() {
        num--;
        return *this;
    }
    EpsFloat operator--(int) {
        EpsFloat result = *this;
        num--;
        return result;
    }

    EpsFloat& operator+=(const EpsFloat& rhs) {
        num += rhs.num;
        return *this;
    }
    EpsFloat& operator-=(const EpsFloat& rhs) {
        num -= rhs.num;
        return *this;
    }
    EpsFloat& operator*=(const EpsFloat& rhs) {
        num *= rhs.num;
        return *this;
    }
    EpsFloat& operator/=(const EpsFloat& rhs) {
        num /= rhs.num;
        return *this;
    }

    friend s operator+(const EpsFloat& l, const EpsFloat& r) {return l.num + r.num;}
    friend s operator-(const EpsFloat& l, const EpsFloat& r) {return l.num - r.num;}
    friend s operator*(const EpsFloat& l, const EpsFloat& r) {return l.num * r.num;}
    friend s operator/(const EpsFloat& l, const EpsFloat& r) {return l.num / r.num;}

    friend std::partial_ordering operator<=>(const EpsFloat& lhs, const EpsFloat& rhs) {
        if (std::isnan(lhs.num) || std::isnan(rhs.num)) 
            return std::partial_ordering::unordered;
        auto diff = lhs.num - rhs.num;
        if (std::abs(diff) <= Eps) 
            return std::partial_ordering::equivalent;
        return diff <=> EpsFloat::value_type(0.0);
    }
    friend bool operator==(const EpsFloat& lhs, const EpsFloat& rhs) {
        return std::abs(lhs.num - rhs.num) <= Eps;
    }
    friend bool operator!=(const EpsFloat& lhs, const EpsFloat& rhs) {
        return !(lhs == rhs);
    }

    friend auto& operator<<(std::ostream& os, const EpsFloat& num) {
        return os << num.num;
    }

    friend auto& operator>>(std::istream& is, EpsFloat& num) {
        return is >> num.num;
    }

    EpsFloat abs() const {
        return std::abs(num);
    }

    friend auto abs(const EpsFloat& num) {
        return num.abs();
    }
};

template <class T, T Eps>
struct std::formatter<EpsFloat<T, Eps>> : std::formatter<T> {
    using std::formatter<T>::parse;

    template <class Out>
    auto format(const EpsFloat<T, Eps>& f, std::basic_format_context<Out, char>& ctx) const {
        return std::formatter<T>::format(f.num, ctx);
    }
};

using Float = EpsFloat<double, 1e-7>;
