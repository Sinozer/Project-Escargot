#pragma once
#include "../Entity.h"
namespace Snail
{
	/**
	 * \TODO Make it virtual
	 */
	class Projectile : public Entity
	{
	protected:
		PhysicBodyRef m_physiBodyRef;

		sf::Vector2f m_weaponPosition;
		sf::Vector2f m_targetPosition;


		float m_damage;

		float m_range;
	public:
		virtual void AddBullet() = 0;
	};
}