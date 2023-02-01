#pragma once
#include "../../stdafx.h"
namespace Snail
{
	static class Math
	{
	public:
		static float inline Clamp(float value, float min, float max)
		{
            if (min > max)
                throw std::invalid_argument("Min is greater than max");
            
            return std::min(std::max(value, min), max);
		}
	};
}