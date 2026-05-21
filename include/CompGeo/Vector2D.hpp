#pragma once

#include <cmath>
#include <istream>
#include <ostream>
#include <utility>

template < typename T >
struct Vector2D {

	T x_{}, y_{};

	Vector2D() = default;
	Vector2D(T x, T y): x_(std::move(x)), y_(std::move(y)) {}
	Vector2D(const Vector2D&) = default;
	Vector2D(Vector2D&&) = default;
	Vector2D& operator=(const Vector2D&) = default;
	Vector2D& operator=(Vector2D&&) = default;

	Vector2D& operator+=(const Vector2D& other) {
		x_ += other.x_;
		y_ += other.y_;
		return *this;
	}

	Vector2D operator+(const Vector2D& other) const {
		return Vector2D(*this) += other;
	}

	Vector2D& operator-=(const Vector2D& other) {
		x_ -= other.x_;
		y_ -= other.y_;
		return *this;
	}

	Vector2D operator-(const Vector2D& other) const {
		return Vector2D(*this) -= other;
	}

	Vector2D& operator*=(const T& x) {
		x_ *= x;
		y_ *= x;
		return *this;
	}

	Vector2D operator*(const T& x) const {
		return Vector2D(*this) *= x;
	}

	Vector2D& operator/=(const T& x) {
		x_ /= x;
		y_ /= x;
		return *this;
	}

	Vector2D operator/(const T& x) const {
		return Vector2D(*this) /= x;
	}

	bool operator==(const Vector2D&) const = default;

	template< typename U = T >
	U dot(const Vector2D& rhs) const {
		U x1 = x_, y1 = y_, x2 = rhs.x_, y2 = rhs.y_;
		return x1 * x2 + y1 * y2;
	}

	template< typename U = T>
	U cross(const Vector2D& rhs) const {
		U x1 = x_, y1 = y_, x2 = rhs.x_, y2 = rhs.y_;
		return x1 * y2 - x2 * y1;
	}

	template< typename U = T>
	double len() const {
		U x = x_, y = y_;
		return std::sqrt(x * x + y * y);
	}

	template< typename U = T>
	long double len_ld() const {
		U x = x_, y = y_;
		return std::sqrtl(x * x + y * y);
	}

	template < typename U >
	Vector2D<U> to() const {
		return Vector2D<U>(static_cast<U>(x_), static_cast<U>(y_));
	}

	friend std::istream& operator>>(std::istream& is, Vector2D& vec) {
		return is >> vec.x_ >> vec.y_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
		return os << vec.x_ << " " << vec.y_;
	}
};

template < typename T >
Vector2D<T> operator*(const T& scalar, const Vector2D<T>& vec) {
	return vec * scalar;
}
