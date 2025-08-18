// random_composition.ixx
module;

#include <vector>

export module combinatorial_algorithms.random_composition;
import combinatorial_algorithms;
import combinatorial_algorithms.random_subset;

// compositions into k parts: x_0 + x_1 + x_2 + ... + x_k = n
// where x_i >= 0, and order matters
export integer_set random_composition(random_generator& g, integer n, integer k)
{
	integer_set result(k);
	integer_set a = random_subset(g, n + k - 1, k - 1);
	auto ps = a[0];
	result[0] = a[0];
	for (integer i = 1; i < k - 1; ++i) {
		result[i] = a[i] - a[i - 1] - 1;
		ps += result[i];
	}
	result[k - 1] = n - ps;
	return result;
}
