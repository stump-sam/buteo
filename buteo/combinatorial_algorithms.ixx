// combinatorial_algorithms.ixx
module;

#include "boost_mp.h"


export module combinatorial_algorithms;

export typedef int integer;
export typedef std::vector<integer> integer_set;

// base class for custom random generators
export struct random_generator {
	virtual double rand() = 0;	// must return a random number in the range [0, 1)
};

// handy functions for counting
export mp_int binomial_coefficient(integer n, integer k)
{
	if (k < 0 || k > n) {
		return 0;
	}
	if (k == 0 || k == n) {
		return 1;
	}
	if (k > n - k) {
		k = n - k;
	}
	mp_int numer = 1, denom = 1;
	while (k > 0) {
		numer *= n;
		denom *= k;
		--n;
		--k;

	}
	return numer / denom;
}

export mp_int factorial(integer n) 
{
	mp_int result = 1;
	while (n > 1) {
		result *= n;
		--n;
	}
	return result;
}


