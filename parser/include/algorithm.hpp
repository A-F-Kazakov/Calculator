#ifndef CALCULATOR_ALBORITHM_HPP
#define CALCULATOR_ALBORITHM_HPP

namespace calc::algorithm
{
	template<typename T>
	T factorial(T n)
	{
		T factorial = 1;

		for(T i = 2; i <= n; ++i)
			factorial *= i;

		return factorial;
	}

	template<typename T>
	T combination(T k, T n)
	{
		T res = factorial(n) / factorial(k) * factorial(n - k);
		return res;
	}
} // namespace calc

#endif
