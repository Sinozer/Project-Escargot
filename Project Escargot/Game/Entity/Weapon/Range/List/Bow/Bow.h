#pragma once
#include "Game/Entity/Weapon/Range/Range.h"

namespace Snail
{
	class Bow : public Range
	{
	private:
		void m_InitPhysicBody(PhysicBodyManager& pbm);
	public:
		Bow(sf::Vector2f targetPosition);
		~Bow();
		
		void Use();
		
		void Init(PhysicBodyManager& pbm);

		void Update(float dt);

		void Draw();
	};
}