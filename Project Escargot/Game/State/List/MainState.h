#pragma once
#include "../../Physic/PhysicBodyManager.h"
#include "../../Entity/LivingEntity/LivingEntity.h"
#include "../../Entity/LivingEntity/Player/Player.h"
#include "../../Entity/LivingEntity/Enemy/Enemy.h"
#include "../../Entity/Bullet/BulletManager.h"
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

		InputListener m_inputListener;

		Enemy m_enemy;

		GameDataRef m_data;

		sf::Clock m_clock;

		sf::Sprite m_background;

		BulletManager *m_bullet;

		int m_tempBulletCount;
		int m_timerBulletFire;
		int m_numberBullet;
	public:
		MainState(GameDataRef data);
		~MainState();

		void Init();
		void AddBullet();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void QuitEventListener();
	};
}