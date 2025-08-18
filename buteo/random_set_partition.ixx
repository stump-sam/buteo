// random_set_partition.ixx
module;

#include <algorithm>	// for std::sort
#include "boost_mp.h"


export module combinatorial_algorithms.random_set_partition;
import combinatorial_algorithms;
import combinatorial_algorithms.random_permutation;

mp_int bell_number(integer n)
{
	static std::unordered_map<integer, mp_int> cache;
	if (cache.find(n) != cache.end()) {
		return cache[n];
	}
	mp_int result = 1;
	if (n > 0) {
		result = 0;
		for (integer k = 0; k < n; ++k) {
			result += binomial_coefficient(n - 1, k) * bell_number(k);
		}
	}
	cache[n] = result;
	return result;
}

integer choose_k(random_generator& g, integer n)
{
	if (n <= 0) {
		return 0; // no choice
	}
	integer k = 1;
	mp_int dterm = bell_number(n);
	mp_real p = g.rand();
	mp_rational t = 0;
	while (k < n) {
		mp_int nterm = binomial_coefficient(n - 1, k - 1) * bell_number(n - k);
		// TODO: consider cpp_rational
		mp_rational term = mp_rational(nterm, dterm);
		t += term;
		if ((mp_real)t >= p) {
			break; // we have chosen k
		}
		++k;
	}
	return k;
}

// returns a random partition of [n] into non-empty subsets
export std::vector<integer_set> random_set_partition(random_generator& g, integer n)
{
	integer_set q(n);
	if (n <= 0) {
		return std::vector<integer_set>(0); // empty set
	}
	integer m = n;
	integer l = 0;
	while (m > 0) {
		integer k = choose_k(g, m);
		for (integer i = m - k; i < m; ++i) {
			q[i] = l;
		}
		++l;
		m -= k;
	}
	// permute q randomly into r
	integer_set p = random_permutation(g, n);
	integer_set r(n);
	for (integer i = 0; i < n; ++i) {
		integer j = p[i];
		r[j] = q[i];
	}
	std::vector<integer_set> result(l);
	for (integer i = 0; i < n; ++i) {
		result[r[i]].push_back(i);
	}
	std::sort(result.begin(), result.end());
	return result;
}
