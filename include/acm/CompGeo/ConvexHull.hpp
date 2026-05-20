#pragma once
#include "../TypeDef.hpp"

std::vector<Point> getConvexHull(std::vector<Point> points, bool keep_collinear = false) {
    std::ranges::sort(points);
    auto erase_range = std::ranges::unique(points);
    points.erase(erase_range.begin(), erase_range.end());

    int n = ssize(points);
    if (n <= 1) {
        return points;
    }
    std::vector<Point> lower;
    for (int i = 0; i < n; i++) {
        while (ssize(lower) >= 2) {
            auto cross_multi_res = cross_multi(
                lower.back() - lower.at(ssize(lower) - 2),
                points.at(i) - lower.back()
            );
            if (keep_collinear) {
                if (cross_multi_res < 0) lower.pop_back();
                else break;
            } else {
                if (cross_multi_res <= 0) lower.pop_back();
                else break;
            }
        }

        lower.push_back(points[i]);
    }

    std::vector<Point> upper;
    for (int i = n - 1; i >= 0; i--) {
        while (ssize(upper) >= 2) {
            auto cross_multi_res = cross_multi(
                upper.back() - upper.at(ssize(upper) - 2),
                points.at(i) - upper.back()
            );
            if (keep_collinear) {
                if (cross_multi_res < 0) upper.pop_back();
                else break;
            } else {
                if (cross_multi_res <= 0) upper.pop_back();
                else break;
            }
        }

        upper.push_back(points[i]);
    }

    if(!lower.empty()) lower.pop_back();
    if(!upper.empty()) upper.pop_back();
    std::vector<Point> hull(lower.size() + upper.size());
    std::ranges::copy(lower, hull.begin());
    std::ranges::copy(upper, hull.begin() + lower.size());

    if (hull.empty() && !points.empty()) {
        if (keep_collinear) {
            return points;
        } else {
            std::vector<Point> endpts;
            endpts.push_back(points.front());
            if (!(points.front() == points.back())) endpts.push_back(points.back());
            return endpts;
        }
    }

    return hull;
}
