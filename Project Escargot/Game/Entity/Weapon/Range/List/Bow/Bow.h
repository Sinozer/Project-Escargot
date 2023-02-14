#pragma once
#include "Game/Entity/Weapon/Range/Range.h"

namespace Snail
{
	class Bow : public Range
	{
	private:
		void m_InitPhysicBody();
	public:
		Bow(sf::Vector2f targetPosition);
		~Bow();
		
		void Use();
		
		void Init();

		void Update(float dt);

		void Draw();
	};
}

