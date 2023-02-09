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
		static sf::Vector2f inline Clamp(sf::Vector2f value, float min, float max)
		{
			if (min > max)
				throw std::invalid_argument("Min is greater than max");

			return sf::Vector2f(std::min(std::max(value.x, min), max), std::min(std::max(value.y, min), max));
		}
	};
}