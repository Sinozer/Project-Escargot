#pragma once
#include "Game/Physic/PhysicBody.h"
namespace Snail
{
	/**
	 * \TODO Make it virtual
	 */
	class Entity : public PhysicBodyRef
	{
	protected:
		PhysicBodyRef m_physicBodyRef;

		std::string m_name;

		float m_speed;
		sf::Vector2f m_clampVelocity;

		float m_jumpHeight;

		virtual void m_InitPhysicBody() = 0;
	public:
		virtual void Init() = 0;

		virtual void Update(float dt) = 0;

		virtual void Draw() = 0;
	};
}