#pragma once
#include "../Entity.h"
namespace Snail
{
	class BulletManager : Entity
	{
	private:
		GameDataRef m_data;

		sf::Vector2f m_shooterCoord;
		float m_speed;
		enum m_dir
		{
			RIGHT,
			LEFT,
			TOP,
			DOWN
		};

		int m_playerDir;
		void m_InitPhysicBody();
	public:
		PhysicBodyRef m_physicBodyRef;

		/**
		* \brief Constructor to not use.
		*
		*/
		BulletManager() {}

		BulletManager(GameDataRef data, sf::Vector2f shooterCoord, int dir);
		~BulletManager();

		void Init();
		void fireAmmo();

		void Update(float dt);

		void Draw();

	};
}
