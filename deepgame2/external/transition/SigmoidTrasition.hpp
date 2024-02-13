#include <cmath>

#ifndef SIGMOID_HPP
#define SIGMOID_HPP

inline float sigmoidTransition(float startValue, float endValue, float currentTime, float startTime, float k)
{
	return (startValue - endValue) + (endValue - (startValue - endValue)) * (1.0f / (1.0f + std::exp((-k * 5.0f) * (currentTime - startTime))));
}

#endif