#pragma once
namespace Snail
{
	class InputManager
	{
	private:
		static InputManager* Instance;
		
		sf::RenderWindow& m_window;
		InputManager(sf::RenderWindow& window) : m_window(window) {}
		~InputManager();
	public:
		static bool IsInstance();
		static InputManager* GetInstance(sf::RenderWindow& window);
		static InputManager* GetInstance();
		static void DestroyInstance();


		bool IsSpriteLeftClicked(sf::Sprite object);
		bool IsSpriteRightClicked(sf::Sprite object);
		
		sf::Vector2f GetMousePosition();
	};
}