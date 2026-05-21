#pragma once
#include "../TypeDef.hpp"
#include "Point.hpp"
#include "Vector2D.hpp"
#include <tuple>
#include <vector>
#include <algorithm>
#include <type_traits>

template < typename T,
           typename CrossType = std::conditional_t<std::is_integral_v<T>, long long, T> >
std::vector<Point<T>> getConvexHull(std::vector<Point<T>> points, bool keep_collinear = false) {
    std::ranges::sort(points, [](const Point<T>& lhs, const Point<T>& rhs) -> bool {
        return std::tie(lhs.x_, lhs.y_) < std::tie(rhs.x_, rhs.y_);
    });
    auto erase_range = std::ranges::unique(points);
    points.erase(erase_range.begin(), erase_range.end());

    int n = ssize(points);
    if (n <= 1) {
        return points;
    }
    std::vector<Point<T>> lower;
    for (int i = 0; i < n; i++) {
        while (ssize(lower) >= 2) {
            auto cross_val = (lower.back() - lower.at(std::ssize(lower) - 2)).template cross<CrossType>(points.at(i) - lower.back());
            if (keep_collinear) {
                if (cross_val < 0) lower.pop_back();
                else break;
            } else {
                if (cross_val <= 0) lower.pop_back();
                else break;
            }
        }

        lower.push_back(points[i]);
    }

    std::vector<Point<T>> upper;
    for (int i = n - 1; i >= 0; i--) {
        while (ssize(upper) >= 2) {
            auto cross_val = (upper.back() - upper.at(std::ssize(upper) - 2)).template cross<CrossType>(points.at(i) - upper.back());
            if (keep_collinear) {
                if (cross_val < 0) upper.pop_back();
                else break;
            } else {
                if (cross_val <= 0) upper.pop_back();
                else break;
            }
        }

        upper.push_back(points[i]);
    }

    if (!lower.empty()) lower.pop_back();
    if (!upper.empty()) upper.pop_back();
    std::vector<Point<T>> hull(lower.size() + upper.size());
    std::ranges::copy(lower, hull.begin());
    std::ranges::copy(upper, hull.begin() + lower.size());

    return hull;
}
