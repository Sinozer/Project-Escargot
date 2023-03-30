#pragma once
#include "Game/Entity/Entity.h"
#include "Game/Entity/Projectile/Projectile.h"
namespace Snail
{
	class BulletManager : Entity
	{
	private:
		GameDataRef m_data;

		// Bullet
		// Entity who's shooting
		sf::Vector2f m_shooterCoord;
		sf::Vector2f m_targetPosition;

		std::vector<Projectile*> m_projectiles;


		/*enum m_dir
		{
			RIGHT,
			LEFT,
			TOP,
			DOWN
		};*/
		//int m_playerDir;

		// Bullet
		// Offset the position to avoid collision bugs
		//float m_offset;

		// Entity
		// - Player
		//		(sf::vector2f)m_mousePosition
		// - Enemy
		//		m_tagetPosition

		// Weapon	[Convert wantedWosition and weaponPosition into wantedAngle into deltaTargetPosition]
		// sf::Vector2f m_deltaTargetPosition	[Where to shoot]

		// Bullet
		// Get the mouse position to know where to shoot


		void m_InitPhysicBody(PhysicBodyManager& pbm);
	public:

		// Bullet
		// Contains his physic object and properties
		PhysicBodyRef m_physicBodyRef;

		/**
		* \brief Constructor to not use.
		*
		*/
		BulletManager() {}

		BulletManager(GameDataRef data, sf::Vector2f shooterCoord, sf::Vector2f mousePositon);
		~BulletManager();

		void FireBullet(Projectile &type);

		void Init(PhysicBodyManager& pbm);

		void Update(float dt);

		void Draw();

	};
}
