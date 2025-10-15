#pragma once
#include <random>

namespace Randomizer
{

inline int universal_random(int min, int max)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}

} // namespace Randomizer