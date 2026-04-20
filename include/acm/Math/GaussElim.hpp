#pragma once

#include <vector>
#include <cmath>
#include <utility>

#include <acm/DataStructure/Float.hpp>

template <class T = Float>
struct GaussElimSolver {
    using value_type = T;

    enum Solution {None, Infinte, Unique};

    Solution operator()(std::vector<std::vector<value_type>>& augment) const {
        const auto matrix_size = augment.size();
        assert(matrix_size != 0 && "Invalid matrix dimensions");
        for (auto& row : augment) {
            assert(row.size() == matrix_size + 1 && "Invalid matrix dimensions");
        }

        const int n = matrix_size;

        for (int i = 0; i < n; i++) {
            int max_value_row = i;
            for (int j = 0; j < n; j++) {
                if (j < i && augment[j][j] != 0) {
                    continue;
                }
                using std::abs;
                if (abs(augment[j][i]) > abs(augment[max_value_row][i])) {
                    max_value_row = j;
                }
            }
            std::swap(augment[i], augment[max_value_row]);
            max_value_row = i;
            if (augment[max_value_row][i] != 0) {
                auto tmp = augment[max_value_row][i];
                for (int j = i; j <= n; j++) {
                    augment[max_value_row][j] /= tmp;
                }

                for (int j = 0; j < n; j++) {
                    if (i == j) continue;
                    auto rate = augment[j][i] / augment[max_value_row][i];
                    for (int k = 0; k <= n; k++) {
                        augment[j][k] -= augment[max_value_row][k] * rate;
                    }
                }
            }
        }

        Solution result{Unique};

        for (int i = 0; i < n; i++) {
            if (augment[i][i] == 0) {
                if (augment[i][n] == 0) {
                    result = Infinte;
                    break;
                } else {
                    result = None;
                    break;
                }
            }
        }
        return result;
    }
};

using GaussElim = GaussElimSolver<>;

constexpr GaussElim gauss_elim;