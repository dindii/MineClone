#pragma once
#include <random>
namespace MC
{
	class RandomNumberGenerator
	{
	public:
		RandomNumberGenerator();

		template<typename T>
		double Gen(T min, T max)
		{
			std::uniform_real_distribution<double> unif(min, max);
			return unif(rngEngine);
		}

	private:
		std::mt19937_64 rngEngine;
	};
}