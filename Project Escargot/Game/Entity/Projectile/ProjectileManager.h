#pragma once
#include "Game/Entity/Entity.h"
#include "Game/Entity/Projectile/Projectile.h"
namespace Snail
{
	enum EProjectile
	{
		NONE,
		ARROW
	};

	class ProjectileManager : public Entity
	{
	private:
		PhysicBodyManager m_physicBodyManager;
		EProjectile m_projectileReference = NONE;
	private:
		GameDataRef m_data;

		sf::Vector2f m_shooterCoord;
		sf::Vector2f m_targetPosition;

		std::vector<Projectile*> m_projectiles;


		void m_InitPhysicBody(PhysicBodyManager& pbm);
	public:

		PhysicBodyRef m_physicBodyRef;

		/**
		* \brief Constructor to not use.
		*
		*/
		ProjectileManager() {}

		ProjectileManager(GameDataRef data, sf::Vector2f shooterCoord, sf::Vector2f mousePositon);
		~ProjectileManager();

		void Init(PhysicBodyManager& pbm);

		void SetProjectile(EProjectile ref);

		void Shoot(sf::Vector2f startingPoint);

		void Update(float dt);

		void Draw();

	};
}
 