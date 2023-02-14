#pragma once
#include "Game/Entity/Weapon/Range.h"

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
		void Init(sf::Vector2f targetPosition);


		void Update(float dt);

		void Draw();
	};
}

