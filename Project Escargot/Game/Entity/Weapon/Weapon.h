#pragma once
#include "../Entity.h"
#include "Game/Entity/Projectile/ProjectileManager.h"
namespace Snail
{
	/**
	 * \TODO Make it virtual
	 */
	class Weapon : public Entity
	{
	protected:
		std::string m_name;

		PhysicBodyRef m_physicBodyRef;

		sf::Vector2f m_wantedWosition;

		float m_offset;


	public:
		virtual void Use() = 0;

		virtual void Draw() = 0;

		virtual void Update(float dt) = 0;

		virtual void HandlerPos(sf::Vector2f handler) = 0;
	};
}

