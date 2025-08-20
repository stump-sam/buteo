// buteo.cpp
//

#include <iostream>
#include <random>

#include "boost_mp.h"

import combinatorial_algorithms;
import combinatorial_algorithms.random_subset;
import combinatorial_algorithms.random_permutation;
import combinatorial_algorithms.random_composition;
import combinatorial_algorithms.random_int_partition;
import combinatorial_algorithms.random_set_partition;

// my random generator ...
struct uniform01_generator : public random_generator {
	uniform01_generator() : gen(rd()), dis(0, 1) {
	}
	std::random_device rd;
	std::mt19937_64 gen;
	std::uniform_real_distribution<> dis;

	virtual double rand() {
		return dis(gen);
	}
};

// output stream of std::vector<T> ...
template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& a)
{
	o << "[";
	size_t n = a.size(), i = 0;
	for (auto e : a) {
		o << e;
		if (i++ < n - 1) {
			o << ", ";
		}
	}
	return o << "]";
}

struct PairHash {
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2>& p) const {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);

		// A common way to combine hashes, inspired by Boost's hash_combine
		// This is generally better than simple XOR for avoiding collisions.
		return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
	}
};

struct VectorHash {
	template <typename T>
	std::size_t operator()(const std::vector<T>& v) const {
		std::size_t seed = 0;
		for (const auto& elem : v) {
			seed ^= std::hash<T>{}(elem)+0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};



/* Pseudo - Tests */

integer test_repeats = 20;

void test_random_subet(uniform01_generator& g, integer n, integer k)
{
	std::cout << k << "-subsets of [" << n << "]" << std::endl;
	integer_set S;
	for (integer i = 0; i < test_repeats; ++i) {
		S = random_subset(g, n, k);
		std::cout << i << ": " << S << std::endl;
	}
}

void test_random_permutation(uniform01_generator& g, integer n)
{
	std::cout << "permutations of [" << n << "]" << std::endl;
	integer_set perm(n);
	for (integer i = 0; i < test_repeats; ++i) {
		std::cout << i << ": " << random_permutation(g, n) << std::endl;
	}
}

void test_random_composition(uniform01_generator& g, integer n, integer k)
{
	std::cout << "compositions of " << n << " into " << k << " parts" << std::endl;

	for (integer i = 0; i < test_repeats; ++i) {
		integer_set v = random_composition(g, n, k);
		std::cout << i << ": " << v << std::endl;
	}
}

void test_random_int_partition(uniform01_generator& g, integer n)
{
	std::cout << "integer partitions of " << n << std::endl;
	for (integer i = 0; i < test_repeats; ++i) {
		integer_set v = random_int_partition(g, 1 + g.rand() * n);
		std::cout << i << ": " << v << std::endl;
	}
}

void test_random_set_partition(uniform01_generator& g, integer n)
{
	std::cout << "set partitions of " << n << std::endl;
	for (integer i = 0; i < test_repeats; ++i) {
		std::vector<integer_set> p = random_set_partition(g, 1 + g.rand() * n);
		std::cout << i << ": " << p << std::endl << std::endl;
	}
	
}

void test_factorial_and_binomial(uniform01_generator& g, integer nn)
{	
	for (integer i = 0; i < test_repeats; ++i) {
		integer n = 1 + integer(g.rand() * nn);
		integer k = n / 2;
		std::cout << i << ": factorial and binomial coefficient tests for n = " << n << ", k = " << k << std::endl;
		mp_int binom = binomial_coefficient(n, k);
		mp_int fact = factorial(n) / (factorial(k) * factorial(n - k));
		std::cout << "binomial coefficient: " << binom << std::endl;
		std::cout << "factorial test: " << fact << std::endl;
		std::cout << (binom == fact ? "equal" : "not equal") << std::endl;
	}
}

void run_tests()
{
	integer n = 1000, k = 500;
	uniform01_generator g;
	test_random_subet(g, n, k);
	test_random_permutation(g, n);
	test_random_composition(g, n, k);
	test_random_int_partition(g, n);
	test_random_set_partition(g, n);
	test_factorial_and_binomial(g, 5 * n);
}



int main(int argc, char* argv[])
{
	run_tests();
	return 0;
}

