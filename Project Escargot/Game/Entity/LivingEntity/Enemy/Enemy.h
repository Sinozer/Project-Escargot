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

		void m_InitPhysicBody(PhysicBodyManager& pbm);
		bool m_isMelee;
		float m_attackRange;

		void m_InitPhysicBody();

		void m_ChangeDirection(Direction direction = NONE);
		void m_UpdatePosition();

		bool m_IsPlayerInRange();
		bool m_IsAttackRange(bool isMelee);

	public:
		/**
		 * \brief Constructor.
		 *
		 * \param data
		 */
		Enemy(GameDataRef data, Player& target);

		void Init(PhysicBodyManager& pbm);

		void HandleInput();

		void Update(float dt);

		void Draw();

		PhysicBodyRef GetPhysicBodyRef();
	};
}