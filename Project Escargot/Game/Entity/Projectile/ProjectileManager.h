#pragma once
#include "Game/Entity/Entity.h"
#include "Game/Entity/Projectile/Projectile.h"
namespace Snail
{
	class ProjectileManager
	{
	private:
		//PhysicBodyManager m_physicBodyManager;
	private:
		GameDataRef m_data;

		sf::Vector2f m_shooterCoord;
		sf::Vector2f m_targetPosition;

		Projectile* m_projectileRef;
		std::vector<Projectile*> m_projectiles;


		void m_InitPhysicBody(sf::Vector2f position);
	public:

		PhysicBodyRef m_physicBodyRef;

		/**
		* \brief Constructor to not use.
		*
		*/
		ProjectileManager() {}

		ProjectileManager(GameDataRef data, sf::Vector2f shooterCoord, sf::Vector2f mousePositon);
		~ProjectileManager();

		void SetProjectile(Projectile* projectile);

		void Shoot(sf::Vector2f startingPoint);

		void Update(float dt);

		void Draw();

	};
}
 