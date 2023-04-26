#pragma once
#include "GameData.h"
#include "Input/InputManager.h"

namespace Snail
{
	

	/**
	 * \brief Main class.
	 * 
	 * Manage all of what appens in the game.
	 */
	class Game
	{
	private:
		sf::Text m_text;
		
		float m_dt;
		sf::Clock m_clock;
		void m_UpdateDt();

		GameDataRef m_data = std::make_shared<GameData>();

		void Run();

		void End();
	public:
		/**
		 * Create and init window then push the JoinState onto the StateManager.
		 *
		 * \param width Window width.
		 * \param height Window height.
		 * \param title Window title.
		 */
		Game(int width, int height, std::string title);
	};
}