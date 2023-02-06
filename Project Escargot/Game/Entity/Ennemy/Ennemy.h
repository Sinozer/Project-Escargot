#pragma once
#include "../Entity.h"
namespace Snail
{
	class Ennemy : Entity
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
		Ennemy() {}

		/**
		 * \brief Constructor.
		 *
		 * \param data
		 */
		Ennemy(GameDataRef data);

		void Init();

		void HandleInput();

		void Update(float dt);

		void Draw();
	};
}