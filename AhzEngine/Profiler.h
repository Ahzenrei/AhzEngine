#pragma once

#include <iostream>
#include <chrono>

class Profiler
{
public:
	Profiler(const char* name) noexcept;
	~Profiler();

private:
	const char* name;
	const std::chrono::high_resolution_clock::time_point start;
};

