#include "mcpch.h"
#include "RandomNumberGenerator.h"
#include <chrono>

namespace MC
{
	RandomNumberGenerator::RandomNumberGenerator()
	{
		uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
		rngEngine.seed(ss);
	}
}