#include "stdafx.h"
#include "Game/Entity/Projectile/ProjectileManager.h"


namespace Snail
{
	class Arrow : Projectile
	{
	private :
		GameDataRef m_data;

		sf::Vector2f m_shooterCoord;
		sf::Vector2f m_targetPosition;

		void Init();

		void m_InitPhysicBody();

		void fireAmmo();
	public : 

		Arrow(GameDataRef data, sf::Vector2f shooterCoord, sf::Vector2f mousePositon);
		~Arrow();


	};
}
