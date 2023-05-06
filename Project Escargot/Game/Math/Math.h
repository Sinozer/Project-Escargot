#pragma once
#include "stdafx.h"
namespace Snail
{
	class Math
	{
	public:
		static float inline Clamp(float value, float min, float max)
		{
            if (min > max)
                throw std::invalid_argument("Min is greater than max");
            
            return std::min(std::max(value, min), max);
		}

		static int inline Clamp(int value, int min, int max)
		{
			if (min > max)
				throw std::invalid_argument("Min is greater than max");

			return std::min(std::max(value, min), max);
		}

		static sf::Vector2f inline Clamp(sf::Vector2f value, sf::Vector2f min, sf::Vector2f max)
		{
			if (min.x > max.x || min.y > max.y)
				throw std::invalid_argument("Min is greater than max");

			return sf::Vector2f(std::min(std::max(value.x, min.x), max.x), std::min(std::max(value.y, min.y), max.y));
		}
	};
}