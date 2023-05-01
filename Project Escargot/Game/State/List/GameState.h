#pragma once
#include "Game/State/State.h"
#include "Game/Physic/PhysicBodyManager.h"
#include "Game/Entity/LivingEntity/Player/Player.h"
#include "Game/Entity/LivingEntity/Enemy/Enemy.h"
#include "Game/Entity/Spawner.h"
#include "Game/Entity/Collectables/Collectable.h"
namespace Snail
{
	/**
	 * \brief Main state used as a menu.
	 */
	class GameState : public State
	{
	private:
		Player* m_player;

		Spawner m_spawner;

		Collectable m_collectable;

		GameDataRef m_data;

		sf::Clock m_clock;

		void m_InitBackground();
		void m_InitView();
		void m_InitUIManager();
		void m_InitUITexts();
		void m_InitUIButtons();
		void m_InitMap();

		void m_UpdateView();
		void m_UpdateUIManager();

		void m_DrawUIManager();
	public:
		GameState(GameDataRef data);
		~GameState() {}

		void Init();
		void HandleInput();
		void Update();
		void Draw();
		void DrawUI();
		void End();
	};
}