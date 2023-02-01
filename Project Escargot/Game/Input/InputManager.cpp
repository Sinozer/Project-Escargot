#include "stdafx.h"

namespace Snail
{
	bool InputManager::IsSpriteLeftClicked(sf::Sprite object, sf::RenderWindow& window)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return false;
		
		sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (!tempRect.contains(sf::Mouse::getPosition(window))) return false;
		
		return true;
	}

	bool InputManager::IsSpriteRightClicked(sf::Sprite object, sf::RenderWindow& window)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) return false;

		sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (!tempRect.contains(sf::Mouse::getPosition(window))) return false;

		return true;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
}