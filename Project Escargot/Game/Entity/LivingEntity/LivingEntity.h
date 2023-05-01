#pragma once
#include "Game/Entity/Entity.h"
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
		Direction m_direction = RIGHT;

		float m_speed;
		sf::Vector2f m_clampVelocity;

		float m_jumpHeight;

		virtual void m_ChangeDirection(Direction direction = NONE) = 0;
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

	protected:
		float m_maxLife = 100.f;
		float m_life = m_maxLife;

		float m_damageBuffer = 1.5f;
		float m_damageBufferDelta = 0.f;
		
		float m_damageRangeBuffer = .1f;
		float m_damageRangeBufferDelta = 0.f;

		inline void m_UpdateDamageBuffer()
		{
			if (m_damageBufferDelta > 0.f)
				m_damageBufferDelta = Math::Clamp(m_damageBufferDelta -= Game::m_data->deltaTime, 0.f, m_damageBuffer);
			
			if (m_damageRangeBufferDelta > 0.f)
				m_damageRangeBufferDelta = Math::Clamp(m_damageRangeBufferDelta -= Game::m_data->deltaTime, 0.f, m_damageRangeBuffer);
		}

		inline bool m_TakeDamage(float damages)
		{
			if (m_damageBufferDelta > 0.f) return false;
			m_damageBufferDelta = m_damageBuffer;

			m_life = Math::Clamp(m_life - damages, 0.f, m_maxLife);

			if (m_life <= 0.f)
			{
				IsDeleted = true;
				PhysicBodyManager::GetInstance()->RemovePhysicBody(Name);
			}

			return true;
		}
		
		inline bool m_TakeRangeDamage(float damages)
		{
			if (m_damageRangeBufferDelta > 0.f) return false;
			m_damageRangeBufferDelta = m_damageRangeBuffer;

			m_life = Math::Clamp(m_life - damages, 0.f, m_maxLife);

			if (m_life <= 0.f)
			{
				IsDeleted = true;
				PhysicBodyManager::GetInstance()->RemovePhysicBody(Name);
			}

			return true;
		}
		
	public:
		inline float GetLife() { return m_life; }
		inline std::string GetLifeString()
		{
			std::string temp = std::to_string((int)m_life);
			temp = temp.substr(0, temp.find('.'));
			return temp;
		}
		inline float GetMaxLife() { return m_maxLife; }
		inline std::string GetMaxLifeString()
		{
			std::string temp = std::to_string((int)m_maxLife);
			temp = temp.substr(0, temp.find('.'));
			return temp;
		}

	public:
		std::string Name;

		virtual PhysicBodyRef GetPhysicBodyRef() = 0;
	};
}

