#include<vector>

using i64 = long long;

struct EularSieve
{
    std::vector<int> primes;
    std::vector<int> min_factor;

    EularSieve(const i64 N): min_factor(N + 1, 0) {
        min_factor[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (min_factor[i] == 0) {
                min_factor[i] = i;
                primes.push_back(i);
            }
            for (auto p : primes) {
                if (i64(i) * p > N) {
                    break;
                }
                min_factor[i * p] =  p;
                if (p == min_factor[i]) {
                    break;
                }
            }
        }
    }

    int operator[](int idx) const {
        return primes[idx - 1];
    }

    bool is_prime(int val) const {
        return min_factor[val] == 0;
    }
};
