#pragma once
#include "Game/Entity/Weapon/Weapon.h"
#include "Game/Entity/Projectile/Projectile.h"

namespace Snail
{
	/**
	 * \TODO Make it virtual
	 */
	class Range : public Weapon
	{
	protected:
		float m_DamageMultiplier;
		float m_rangeMultiplier;

		ProjectileManager m_projectileManager;

		sf::Vector2f m_shooterCoord;
		sf::Vector2f m_targetPosition;
	public:
		/*Range();*/
		//virtual ~Range();
	};
}