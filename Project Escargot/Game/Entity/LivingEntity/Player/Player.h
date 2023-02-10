#pragma once
#include "Game/Entity/LivingEntity/LivingEntity.h"
namespace Snail
{
	class Player : LivingEntity
	{
	private:
		GameDataRef m_data;

		void m_InitPhysicBody();
		void m_UpdateDirection(Direction direction = NONE);
	public:
		int bulletCount;
		
		/**
		 * \brief Constructor.
		 * 
		 * \param data
		 */
		Player(GameDataRef data);
		
		void Init();

		void HandleInput();

		void Update(float dt);

		void Draw();

		PhysicBodyRef GetPhysicBodyRef();
	};
}