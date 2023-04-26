#pragma once
#include "Game/Entity/Entity.h"
#include "Game/Entity/Projectile/Projectile.h"
namespace Snail
{
	class ProjectileManager
	{
	private:
		sf::Vector2f m_shooterCoord;
		sf::Vector2f m_targetPosition;

		Projectile* m_projectileRef;
		std::vector<Projectile*> m_projectiles;
	public:

		PhysicBodyRef m_physicBodyRef;

		ProjectileManager();
		~ProjectileManager();

		void SetProjectile(Projectile* projectile);

		void Shoot(sf::Vector2f startingPoint);

		void Update();

		void Draw();

	};
}
 