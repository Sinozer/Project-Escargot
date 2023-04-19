#include "stdafx.h"
#include "Game/Entity/Projectile/Projectile.h"


namespace Snail
{
	class Arrow : public Projectile
	{
	private :
		GameDataRef m_data;

		sf::Vector2f m_shooterCoord;
		sf::Vector2f m_targetPosition;

		void m_InitPhysicBody(PhysicBodyManager& pbm, sf::Vector2f position);

	public : 
		Arrow(GameDataRef data, sf::Vector2f shooterCoord, unsigned int id = 0);
		~Arrow();

		void Init(PhysicBodyManager& pbm, sf::Vector2f position);
		void Shoot();

		void Update(float dt);
		void Draw();
	};
}
