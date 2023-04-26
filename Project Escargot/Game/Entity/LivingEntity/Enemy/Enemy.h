#pragma once
#include "Game/Entity/LivingEntity/LivingEntity.h"
#include "Game/Entity/LivingEntity/Player/Player.h"
namespace Snail
{
	class Enemy : public LivingEntity
	{
	public:
		static unsigned int Count;

	private:
		float previousPositionX;
	private:
		GameDataRef m_data;

		Player* m_target;

		bool m_isMelee;
		float m_attackRange;
		bool m_forcePlayerPos;

		void m_InitPhysicBody(PhysicBodyManager& pbm, sf::Vector2f position);

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
		Enemy(GameDataRef data);

		void Init(PhysicBodyManager& pbm, sf::Vector2f position = sf::Vector2f(0, 0));

		void HandleInput();

		void Update(float dt);

		void Draw();

		PhysicBodyRef GetPhysicBodyRef();
	};
}