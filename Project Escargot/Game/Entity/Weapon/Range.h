#pragma once
#include "Weapon.h"
#include "../Projectile/Projectile.h"

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

		std::vector<Projectile*> m_Projectiles; //lib�re ta m�moire fils

		sf::Vector2f m_shooterCoord;
		sf::Vector2f m_targetPosition;

		Projectile* m_baseProjectile; //lib�re ta m�moire fils
	public:
		//virtual ~Range();
	};
}