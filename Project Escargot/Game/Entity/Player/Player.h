#pragma once
#include "../Entity.h"
namespace Snail
{
	class Player : Entity
	{
	private:
		GameDataRef m_data;

		float m_speed;

		void m_InitPhysicBody();
	public:
		PhysicBodyRef m_physicBodyRef;
		
		/**
		 * \brief Constructor to not use.
		 * 
		 */
		Player() {}
		
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
	};
}