#pragma once
#include "Game/Physic/PhysicBody.h"
namespace Snail
{
	class Spawner : public PhysicBodyRef
	{
	public:

		//constructor
		Spawner(GameDataRef data);

		void Init(PhysicBodyManager& pbm, sf::Vector2f position = sf::Vector2f(0, 0));

		void Spawn(PhysicBodyManager& pbm, Enemy enemy, sf::Vector2f position = sf::Vector2f(0, 0));

	private:

		GameDataRef m_data;

		void m_InitPhysicBody(PhysicBodyManager& pbm, sf::Vector2f position);


	protected:

		PhysicBodyRef m_physicBodyRef;
	};
}
