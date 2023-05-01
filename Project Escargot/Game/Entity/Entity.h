#pragma once
#include "Game/Physic/PhysicBodyManager.h"
namespace Snail
{
	/**
	 * \TODO Make it virtual
	 */
	class Entity : public PhysicBodyRef
	{
	protected:
		PhysicBodyRef m_physicBodyRef;

		float m_speed = 1.25f * PHYSIC_SCALE;
		sf::Vector2f m_clampVelocity;

		float m_jumpHeight = 2.f * PHYSIC_SCALE;

		virtual void m_InitPhysicBody(sf::Vector2f) = 0;
	public:
		std::string Name;
		bool IsDeleted;

		inline void Destroy()
		{
			PhysicBodyManager::GetInstance()->RemovePhysicBody(Name);
		}

		virtual void Init(sf::Vector2f) = 0;

		virtual void Update() = 0;

		virtual void Draw() = 0;
	};
}