// random_subset.ixx
module;

#include <vector>
#include <algorithm>	// for std::generate

export module combinatorial_algorithms.random_subset;
import combinatorial_algorithms;

// Returns:
//  k == 0, a random subset of [n], having 0 <= k <= n elements
//	k > 0, a random k-element subset of [n], k > n or n == 0 gives {}
export integer_set random_subset(random_generator& g, integer n, integer k = 0)
{
	integer_set result;
	if (n == 0 || k > n) {
		// empty set
		return result;
	}
	if (k == n) {
		integer x = 0;
		result.resize(n);
		generate(result.begin(), result.end(), [&x] { return x++; });
		return result;
	}
	// random subset case...
	if (k == 0) {
		for (integer i = 0; i < n; ++i) {
			if (g.rand() > 0.5) {
				result.push_back((integer)i);
			}
		}
		return result;
	}
	// random k-subset case: k > 0 and k < n
	integer nn = n, kk = k;
	for (integer i = 0; result.size() < k && i < n; ++i) {
		if (g.rand() < (double)kk / nn) {
			result.push_back((integer)i);
			--kk;
		}
		--nn;
	}
	return result;
}
