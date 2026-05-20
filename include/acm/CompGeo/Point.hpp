#pragma once

#include <istream>
#include <ostream>
#include <utility>
#include "Vector2D.hpp"

template < typename T >
struct Point {
	T x_{}, y_{};

	Point() = default;
	Point(T x, T y): x_(std::move(x)), y_(std::move(y)) {}
	Point(const Point&) = default;
	Point(Point&&) = default;
	Point& operator=(const Point&) = default;
	Point& operator=(Point&&) = default;

	Point& operator+=(const Vector2D<T>& other) {
		x_ += other.x_;
		y_ += other.y_;
		return *this;
	}

	Point operator+(const Vector2D<T>& other) const {
		return Point(*this) += other;
	}

	Point& operator-=(const Vector2D<T>& other) {
		x_ -= other.x_;
		y_ -= other.y_;
		return *this;
	}

	Point operator-(const Vector2D<T>& other) const {
		return Point(*this) -= other;
	}

	Point& operator*=(const T& scalar) {
		x_ *= scalar;
		y_ *= scalar;
		return *this;
	}

	Point operator*(const T& scalar) const {
		return Point(*this) *= scalar;
	}

	Point& operator/=(const T& scalar) {
		x_ /= scalar;
		y_ /= scalar;
		return *this;
	}

	Point operator/(const T& scalar) const {
		return Point(*this) /= scalar;
	}

	bool operator==(const Point&) const = default;

	template < typename U >
	Point<U> to() const {
		return Point<U>(static_cast<U>(x_), static_cast<U>(y_));
	}

	friend std::istream& operator>>(std::istream& is, Point& p) {
		return is >> p.x_ >> p.y_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& p) {
		return os << p.x_ << " " << p.y_;
	}

	friend Vector2D<T> operator-(const Point& lhs, const Point& rhs) {
		auto [x1, y1] = lhs;
		auto [x2, y2] = rhs;
		return Vector2D(x1 - x2, y1 - y2);
	}
};

template < typename T >
Point<T> operator*(const T& scalar, const Point<T>& p) {
	return p * scalar;
}
