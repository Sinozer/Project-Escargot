#pragma once
#include "Game/Physic/PhysicBodyManager.h"
#include "Game/Physic/PhysicBody.h"
#include "Game/Entity/LivingEntity/Enemy/Enemy.h"

namespace Snail
{
	class Spawner : public PhysicBodyRef
	{
	public:

		//constructor
		Spawner(GameDataRef data);

		void Init(sf::Vector2f position = sf::Vector2f(0, 0));

		void Spawn(sf::Vector2f position = sf::Vector2f(0, 0));

		void Update();

	private:

		GameDataRef m_data;

		void m_InitPhysicBody(sf::Vector2f position);

		std::vector<Enemy*> m_enemyList;

	protected:

		PhysicBodyRef m_physicBodyRef;
	};
}
