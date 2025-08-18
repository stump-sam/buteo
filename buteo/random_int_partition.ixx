// random_int_partition.ixx
module;

#include <algorithm>	// for std::sort

#include "boost_mp.h"

export module combinatorial_algorithms.random_int_partition;

import combinatorial_algorithms;

// Returns the number of integer partitions of n
// x_0 + x_1 + x_2 + ... + x_k = n, x_i > 0, order does not matter
mp_int int_partition_function(integer n)
{
	mp_int result = 0;
	static std::unordered_map <integer, mp_int> cache;
	if (n < 0) {
		return 0;
	}
	if (cache.find(n) != cache.end()) {
		return cache[n];
	}
	if (n < 0) {
		return 0;
	}
	else if (n == 0) {
		result = 1;
	}
	else {
		double klow = ceil(-(sqrt(24 * n + 1.0) - 1.0) / 6.0);
		double khigh = floor((sqrt(24 * n + 1.0) + 1.0) / 6.0);
		for (integer i = 1; i <= khigh; ++i) {
			mp_int sign = (i + 1) % 2 == 0 ? mp_int(1) : mp_int(-1);
			result += sign * (int_partition_function(n - i * (3 * i - 1) / 2) + int_partition_function(n - i * (3 * i + 1) / 2));
		}
	}
	cache[n] = result;
	return result;
}


// Returns a random pair (j, d)
std::pair<integer, integer> choose_j_d(random_generator& g, integer n)
{
	std::pair<integer, integer> result = { 1,1 };
	if (n == 1) {
		return result;
	}
	mp_real z = g.rand();
	mp_int p_n = int_partition_function(n);
	mp_real target = z;

	for (integer d = 1; d <= n; ++d) {
		for (integer j = 1; j <= n; ++j) {
			if (j * d > n) {
				break; // no more valid j for this d
			}
			mp_int term = d * int_partition_function(n - j * d);
			mp_rational zterm = mp_rational(term, n * p_n);
			if (target < (mp_real)zterm) {
				result.first = j;
				result.second = d;
				return result;
			}
			target -= (mp_real)zterm;
		}
	}
	return result;
}

export integer_set random_int_partition(random_generator& g, integer n)
{
	integer_set result;
	integer m = n;
	while (m > 0) {
		std::pair<integer, integer> p = choose_j_d(g, m);
		auto j = p.first;
		auto d = p.second;
		m -= j * d;
		while (j > 0) {
			result.push_back(d);
			--j;
		}
	}
	std::sort(result.begin(), result.end(), std::greater<integer>());
	return result;
}


/* solwer recursive implementation of p(n) function
 * This is not used in the final implementation, but kept for reference.
 * It is less efficient than the int_partition_function(n) above.
 * ---------------------------------------------------------------------
export mp_int p(int n)
{
	static std::unordered_map<int, mp_int> cache;
	if (n < 0) {
		return 0;
	}
	if (cache.find(n) != cache.end()) {
		return cache[n];
	}
	mp_int result = 1;
	if (n == 0) {
		result = 1;
	}
	else {
		mp_int sum = 0;
		for (int d = 1; d <= n; ++d) {
			for (int j = 1; j * d <= n; ++j) {
				mp_integer numer_term = d * p(n - j * d);
				sum += numer_term;
			}
		}
		result = sum / n;
	}
	cache[n] = result;
	return result;
}
* ---------------------------------------------------------------------
*/
