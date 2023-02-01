#pragma once
namespace Snail
{
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		bool IsSpriteLeftClicked(sf::Sprite object, sf::RenderWindow& window);
		bool IsSpriteRightClicked(sf::Sprite object, sf::RenderWindow& window);
		
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}