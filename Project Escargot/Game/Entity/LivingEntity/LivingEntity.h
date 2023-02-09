#pragma once
#include "../Entity.h"
namespace Snail
{
	class LivingEntity : Entity
	{
	protected:
		PhysicBodyRef m_physicBodyRef;

		enum Direction
		{
			NONE, LEFT, RIGHT
		};
		Direction m_direction;

		float m_speed;
		sf::Vector2f m_clampVelocity;

		float m_jumpHeight;

		virtual void m_UpdateDirection(Direction direction = NONE) = 0;
		inline void m_UpdateSprite()
		{
			switch (m_direction)
			{
			case LEFT:
				if (m_physicBodyRef->GetScale().x > 0)
					m_physicBodyRef->Scale({ -1.f, 1.f });
				break;
			case RIGHT:
				if (m_physicBodyRef->GetScale().x < 0)
					m_physicBodyRef->Scale({ -1.f, 1.f });
				break;
			default:
				break;
			}
		}
	public:
		virtual PhysicBodyRef GetPhysicBodyRef() = 0;
	};
}
