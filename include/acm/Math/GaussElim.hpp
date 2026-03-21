#pragma once

#include <vector>
#include <cmath>
#include <utility>

#include <acm/DataStructure/Float.hpp>

template <class T = Float>
struct GaussElimSolver {
    using value_type = T;

    enum Solution {None, Infinte, Unique};

    struct Result {
        Solution sol_case;
        std::vector<value_type> solution;
    };

    Result operator()(std::vector<std::vector<value_type>> A, std::vector<value_type> b) const {
        auto matrix_size = A.size();
        assert(matrix_size != 0 && b.size() == matrix_size && "Invalid matrix dimensions");
        for (auto& row : A) {
            assert(row.size() == matrix_size && "Invalid matrix dimensions");
        }

        int n = matrix_size;

        for (int i = 0; i < n; i++) {
            int max_value_row = i;
            for (int j = 0; j < n; j++) {
                if (j < i && A[j][j] != 0) {
                    continue;
                }
                using std::abs;
                if (abs(A[j][i]) > abs(A[max_value_row][i])) {
                    max_value_row = j;
                }
            }
            std::swap(A[i], A[max_value_row]);
            std::swap(b[i], b[max_value_row]);
            max_value_row = i;
            if (A[max_value_row][i] != 0) {
                auto tmp = A[max_value_row][i];
                for (int j = i; j < n; j++) {
                    A[max_value_row][j] /= tmp;
                }
                b[max_value_row] /= tmp;

                for (int j = 0; j < n; j++) {
                    if (i == j) continue;
                    auto rate = A[j][i] / A[max_value_row][i];
                    for (int k = 0; k < n; k++) {
                        A[j][k] -= A[max_value_row][k] * rate;
                    }
                    b[j] -= b[max_value_row] * rate;
                }
            }
        }

        Result result;
        result.sol_case = Unique;

        for (int i = 0; i < n; i++) {
            if (A[i][i] == 0) {
                if (b[i] == 0) {
                    result.sol_case = Infinte;
                    break;
                } else {
                    result.sol_case = None;
                    break;
                }
            }
        }
        result.solution = std::move(b);
        return result;
    }
};

using GaussElim = GaussElimSolver<>;

constexpr GaussElim gauss_elim;