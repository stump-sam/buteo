// random_permutation.ixx
module;

#include <vector>
#include <algorithm>	// for std::generate, std::swap

export module combinatorial_algorithms.random_permutation;
import combinatorial_algorithms;

// returns a random permutation of {0, 1, 2, ..., n-1}
export integer_set random_permutation(random_generator& g, integer n)
{
	integer_set perm(n);
	integer x = 0;
	generate(perm.begin(), perm.end(), [&x] { return x++; });
	for (integer i = 0; i < perm.size() - 1; ++i) {
		integer j = i + (integer)(g.rand() * (perm.size() - i));
		std::swap(perm[i], perm[j]);
	}
	return perm;
}
