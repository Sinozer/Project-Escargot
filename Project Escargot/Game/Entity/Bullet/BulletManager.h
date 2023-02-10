#pragma once
#include "Game/Entity/Entity.h"
namespace Snail
{
	class BulletManager : Entity
	{
	private:
		GameDataRef m_data;

		// Bullet
		// Entity who's shooting
		sf::Vector2f m_shooterCoord;


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
		float m_offset;

		// Entity
		// - Player
		//		(sf::vector2f)m_mousePosition
		// - Enemy
		//		m_tagetPosition

		// Weapon	[Convert wantedWosition and weaponPosition into wantedAngle into deltaTargetPosition]
		// sf::Vector2f m_deltaTargetPosition	[Where to shoot]

		// Bullet
		// Get the mouse position to know where to shoot
		sf::Vector2f m_targetPosition;
		

		void m_InitPhysicBody();
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

		void Init();
		void fireAmmo();

		void Update(float dt);

		void Draw();

	};
}
