#include "algorithm.h"

uint64_t factorial(uint_fast32_t n)
{
	uint64_t factorial = 1;

	for(int i = 2; i <= n; ++i)
		factorial *= i;

	return factorial;
}

uint64_t combination(uint32_t k, uint32_t n)
{
	uint64_t res = factorial(n) / factorial(k) * factorial(n - k);

	return res;
}
