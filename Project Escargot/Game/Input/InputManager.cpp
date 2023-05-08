#include "stdafx.h"
#include "InputManager.h"
namespace Snail
{
	InputManager* InputManager::Instance = nullptr;

	InputManager::~InputManager()
	{
	}

	bool InputManager::IsInstance()
	{
		return Instance != nullptr;
	}

	InputManager* InputManager::GetInstance(sf::RenderWindow& window)
	{
		if (!Instance)
			Instance = new InputManager(window);

		return Instance;
	}

	InputManager* InputManager::GetInstance()
	{
		return Instance;
	}

	void InputManager::DestroyInstance()
	{
		if (!Instance) return;
		
		delete(Instance);
		Instance = nullptr;
	}

	bool InputManager::IsSpriteLeftClicked(sf::Sprite object)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return false;

		sf::IntRect tempRect((int)object.getPosition().x, (int)object.getPosition().y, (int)object.getGlobalBounds().width, (int)object.getGlobalBounds().height);

		if (!tempRect.contains(sf::Mouse::getPosition(m_window))) return false;

		return true;
	}

	bool InputManager::IsSpriteRightClicked(sf::Sprite object)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) return false;

		sf::IntRect tempRect((int)object.getPosition().x, (int)object.getPosition().y, (int)object.getGlobalBounds().width, (int)object.getGlobalBounds().height);

		if (!tempRect.contains(sf::Mouse::getPosition(m_window))) return false;

		return true;
	}

	sf::Vector2f InputManager::GetMousePosition()
	{
		return m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		//return sf::Mouse::getPosition(m_window);
	}
}