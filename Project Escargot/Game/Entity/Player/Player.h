#pragma once
#include "../Entity.h"
namespace Snail
{
	class Player : Entity
	{
	private:
		GameDataRef m_data;

		enum m_dir
		{
			RIGHT,
			LEFT,
			TOP,
			DOWN
		};
		void m_InitPhysicBody();
	public:
		PhysicBodyRef m_physicBodyRef;
		int bulletCount;
		int m_playerDir;
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