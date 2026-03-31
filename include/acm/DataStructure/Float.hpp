#pragma once

#include <cmath>
#include <iostream>
#include <utility>

template <class T = double, T Eps = 1e-7>
struct FloatWithEps
{
    using value_type = T;
    value_type num_;

    FloatWithEps(): num_() {}
    FloatWithEps(value_type num): num_(std::move(num)) {}
    FloatWithEps(const FloatWithEps&) = default;
    FloatWithEps(FloatWithEps&&) = default;
    FloatWithEps& operator=(const FloatWithEps&) = default;
    FloatWithEps& operator=(FloatWithEps&&) = default;

    FloatWithEps operator-() const {
        return {-num_};
    }

    friend FloatWithEps operator+(const FloatWithEps& lhs, const FloatWithEps& rhs) {
        return lhs.num_ + rhs.num_;
    }

    friend FloatWithEps operator-(const FloatWithEps& lhs, const FloatWithEps& rhs) {
        return lhs.num_ - rhs.num_;
    }

    friend FloatWithEps operator*(const FloatWithEps& lhs, const FloatWithEps& rhs) {
        return lhs.num_ * rhs.num_;
    }

    friend FloatWithEps operator/(const FloatWithEps& lhs, const FloatWithEps& rhs) {
        return lhs.num_ / rhs.num_;
    }

    explicit operator bool() const {
        using std::abs;
        return abs(num_) <= Eps;
    }

    bool operator!() const {
        return !bool(*this);
    }

    friend std::partial_ordering operator<=>(const FloatWithEps& lhs, const FloatWithEps& rhs) {
        auto diff = lhs.num_ - rhs.num_;
        using std::abs;
        if (abs(diff) <= Eps) {
            return std::partial_ordering::equivalent;
        }
        return diff <=> FloatWithEps::value_type(0.0);
    }

    friend bool operator==(const FloatWithEps& lhs, const FloatWithEps& rhs) {
        using std::abs;
        return abs(lhs.num_ - rhs.num_) <= Eps;
    }

    friend bool operator!=(const FloatWithEps& lhs, const FloatWithEps& rhs) {
        return !(lhs == rhs);
    }

    FloatWithEps& operator+=(const FloatWithEps& rhs) {
        num_ += rhs.num_;
        return *this;
    }

    FloatWithEps& operator-=(const FloatWithEps& rhs) {
        num_ -= rhs.num_;
        return *this;
    }

    FloatWithEps& operator*=(const FloatWithEps& rhs) {
        num_ *= rhs.num_;
        return *this;
    }

    FloatWithEps& operator/=(const FloatWithEps& rhs) {
        num_ /= rhs.num_;
        return *this;
    }

    FloatWithEps& operator++() {
        num_++;
        return *this;
    }

    FloatWithEps operator++(int) {
        FloatWithEps result = *this;
        num_++;
        return result;
    }

    FloatWithEps& operator--() {
        num_--;
        return *this;
    }

    FloatWithEps operator--(int) {
        FloatWithEps result = *this;
        num_--;
        return result;
    }

    friend auto& operator<<(std::ostream& os, const FloatWithEps& num) {
        return os << num.num_;
    }

    friend auto& operator>>(std::istream& is, FloatWithEps& num) {
        return is >> num.num_;
    }

    FloatWithEps abs() const {
        return std::abs(num_);
    }

    friend auto abs(const FloatWithEps& num) {
        return num.abs();
    }
};

using Float = FloatWithEps<double, 1e-7>;
