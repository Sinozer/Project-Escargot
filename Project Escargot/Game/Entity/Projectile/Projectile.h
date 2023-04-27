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
		static unsigned int m_count;
	protected:
		PhysicBodyRef m_physicBodyRef;

		sf::Vector2f m_weaponPosition;
		sf::Vector2f m_targetPosition;


		float m_damage;
		float m_speed;
		float m_range;
	public:
		bool IsDeleted;

		virtual Projectile* Clone() = 0;
		
		virtual void Shoot(sf::Vector2f shooterCoord) = 0;
	};
}