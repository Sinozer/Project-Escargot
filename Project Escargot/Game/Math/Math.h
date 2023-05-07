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

	public:
		
		static double inline GetSineWaveValue(float frequency = .5f, float mapValue = 255.f)
		{
			auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000.0;

			return ((1 + 1.f * std::sin(2 * PI * frequency * time)) / 2.0) * mapValue;
		}
	};
}