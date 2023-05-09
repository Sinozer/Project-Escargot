#pragma once
#include "Game/Entity/LivingEntity/LivingEntity.h"
#include "Game/Entity/LivingEntity/Player/Player.h"
namespace Snail
{
	class Enemy : public LivingEntity
	{
	private:
		float previousPositionX = 0.f;
	private:
		Player* m_target;

		bool m_isMelee;
		float m_attackRange;
		bool m_forcePlayerPos;

		void m_InitPhysicBody(sf::Vector2f position);

		void m_ChangeDirection(Direction direction = NONE);
		void m_UpdatePosition();

		bool m_IsPlayerInRange();
		bool m_IsAttackRange(bool isMelee);

	public:
		/**
		 * \brief Constructor.
		 */
		Enemy();

		void Init(sf::Vector2f position = sf::Vector2f(0, 0));

		void HandleInput();

		void Update();

		void Draw();

		static unsigned int Count;

		PhysicBodyRef GetPhysicBodyRef();
	};
}