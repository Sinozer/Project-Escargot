#include "stdafx.h"
#include "Game/Entity/Projectile/Projectile.h"


namespace Snail
{
	class Arrow : public Projectile
	{
	private:
		sf::Vector2f m_targetPosition;

		void m_InitPhysicBody(sf::Vector2f position);
	
	public:
		virtual Arrow* Clone() override;

	public: 
		Arrow();
		~Arrow();

		void Init(sf::Vector2f position);
		void Shoot(sf::Vector2f shooterCoord) override;

		void Update();
		void Draw();
	};
}
