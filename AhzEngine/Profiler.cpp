#include "Profiler.h"

Profiler::Profiler(const char* name) noexcept
	: name(name), start (std::chrono::high_resolution_clock::now())
{
}

Profiler::~Profiler()
{
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	//TO DO : Log elapsedTime
}
