#pragma once
#include "Game/Entity/LivingEntity/LivingEntity.h"
#include "Game/Entity/LivingEntity/Player/Player.h"
namespace Snail
{
	class Enemy : LivingEntity
	{
	private:
		GameDataRef m_data;

		Player& m_target;

		void m_InitPhysicBody();

		void m_UpdateDirection(Direction direction = NONE);
		void m_UpdatePosition();

	public:
		/**
		 * \brief Constructor.
		 *
		 * \param data
		 */
		Enemy(GameDataRef data, Player& target);

		void Init();

		void HandleInput();

		void Update(float dt);

		void Draw();

		PhysicBodyRef GetPhysicBodyRef();
	};
}