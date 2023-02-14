#pragma once
#include "Game/Entity/Weapon/Range.h"

namespace Snail
{
	class Bow : public Range
	{
	private:


		void m_InitPhysicBody();
	public:
		Bow();
		~Bow();
		void Use();
		void Init();


		void Update(float dt);

		void Draw();
	};
}

