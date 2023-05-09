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


		float m_damage = 30.f;
		float m_speed = 2.f * PHYSIC_SCALE;
	public:
		virtual Projectile* Clone() = 0;
		
		inline float GetDamages()
		{
			return m_damage;
		}
			
		virtual void Shoot(sf::Vector2f shooterCoord) = 0;
	};
}