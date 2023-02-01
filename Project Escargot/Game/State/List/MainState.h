#pragma once
#include "../../Physic/PhysicBodyManager.h"
#include "../../Entity/Player/Player.h"
namespace Snail
{
	/**
	 * \brief Main state used as a menu.
	 */
	class MainState : public State
	{
	private:
		PhysicBodyManager m_physicBodyManager;
		Player m_player;

		GameDataRef m_data;

		sf::Clock m_clock;

		sf::Sprite m_background;
	public:
		MainState(GameDataRef data);
		~MainState() {}

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}