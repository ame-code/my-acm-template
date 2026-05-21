#pragma once

#include "../ConstNumber.hpp"
#include "../TypeDef.hpp"
#include "Inv.hpp"
#include <cstddef>
#include <vector>
#include <cassert>

template < auto MOD = MOD2 >
class Combination {
	std::vector<u64> fac, inv_fac;

public:
	Combination() = default;
	Combination(std::size_t n) {
		init(n);
	}

	void init(std::size_t n) {
		fac.resize(n + 1);
		inv_fac.resize(n + 1);

		fac[0] = 1;
		for (std::size_t i = 1; i < fac.size(); i++) {
			fac[i] = fac[i - 1] * i % MOD;
		}

		inv_fac[n] = inv<MOD>(fac[n]);
		for (std::size_t i = n; i >= 1; i--) {
			inv_fac[i - 1] = inv_fac[i] * i % MOD;
		}
	}

	u64 operator()(std::size_t n, std::size_t m) const {
		assert(n < fac.size() && m <= n);
		return fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
	}
};
