#pragma once
#include "Game/Entity/Weapon/Range/Range.h"
#include "Game/Entity/Projectile/list/Arrow.h"


namespace Snail
{
	class Bow : public Range
	{
	private:
		void m_InitPhysicBody(PhysicBodyManager& pbm);
		sf::Vector2f calc;
	public:
		Bow(sf::Vector2f targetPosition);
		~Bow();
		
		void Use();

		void HandlerPos(sf::Vector2f handler);
		
		void Init(PhysicBodyManager& pbm);

		void Update(float dt);

		void Draw();
	};
}