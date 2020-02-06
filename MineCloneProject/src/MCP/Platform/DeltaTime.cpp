#include "mcpch.h"
#include "DeltaTime.h"
#include <Windows.h>

namespace MC
{	
	DeltaTime::DeltaTime() : currentTime(0), previousTime(0), deltaTime(0.0f), secondsPerCount(0.0f)
	{
		long long int frequency = 0;
		if (QueryPerformanceFrequency((LARGE_INTEGER*)&frequency))
		{
			secondsPerCount = 1.0f / (double)frequency;
		}
	}

	void DeltaTime::tick()
	{
		if (QueryPerformanceCounter((LARGE_INTEGER*)&currentTime))
		{
			deltaTime = (currentTime - previousTime) * secondsPerCount;

			previousTime = currentTime;
		}
	}

	double DeltaTime::getDeltaTime()
	{
		return deltaTime;
	}

}