#pragma once
#include <type_traits>

// Iterate all bits of an integer from LSB to MSB
template <typename T>
    requires std::is_integral_v<T>
class BitLowTraverser {
    static constexpr int N = sizeof(T) * 8;
    using U = std::make_unsigned_t<T>;

    struct sentinel_t {};
    static constexpr sentinel_t sentinel{};

    class Iter {
        U val_;
        int pos_ = 0;
    public:
        explicit constexpr Iter(U v) noexcept : val_(v) {}
        constexpr Iter(U v, sentinel_t) noexcept : val_(v), pos_(N) {}

        constexpr unsigned char operator*() const noexcept { return (val_ >> pos_) & 1; }
        constexpr Iter& operator++() noexcept { ++pos_; return *this; }
        constexpr bool operator!=(const Iter& o) const noexcept { return pos_ != o.pos_; }
    };

    U val_;
public:
    explicit constexpr BitLowTraverser(T v) noexcept : val_(static_cast<U>(v)) {}

    constexpr Iter begin() const noexcept { return Iter(val_); }
    constexpr Iter end()   const noexcept { return Iter(val_, sentinel); }
};

// Iterate all bits of an integer from MSB to LSB
template <typename T>
    requires std::is_integral_v<T>
class BitHighTraverser {
    static constexpr int N = sizeof(T) * 8;
    using U = std::make_unsigned_t<T>;

    struct sentinel_t {};
    static constexpr sentinel_t sentinel{};

    class Iter {
        U val_;
        int pos_;
    public:
        explicit constexpr Iter(U v) noexcept : val_(v), pos_(N - 1) {}
        constexpr Iter(U v, sentinel_t) noexcept : val_(v), pos_(-1) {}

        constexpr unsigned char operator*() const noexcept { return (val_ >> pos_) & 1; }
        constexpr Iter& operator++() noexcept { --pos_; return *this; }
        constexpr bool operator!=(const Iter& o) const noexcept { return pos_ != o.pos_; }
    };

    U val_;
public:
    explicit constexpr BitHighTraverser(T v) noexcept : val_(static_cast<U>(v)) {}

    constexpr Iter begin() const noexcept { return Iter(val_); }
    constexpr Iter end()   const noexcept { return Iter(val_, sentinel); }
};
