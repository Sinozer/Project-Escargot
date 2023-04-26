#pragma once
#include "Game/GameData.h"
#include "PhysicBody.h"
namespace Snail
{
	class PhysicBodyManager
	{
	private:
		GameDataRef m_data;
		
		std::map<std::string, PhysicBodyRef> m_physicBodies;
		PhysicBodyRef m_newPhysicBody;
	public:
		/**
		 * \brief Constructor to not use.
		 * 
		 */
		PhysicBodyManager() {}

		/**
		 * \brief Constructor.
		 *
		 * \param data GameDataRef.
		 */
		PhysicBodyManager(GameDataRef data);

		void AddPhysicBody(std::string name, PhysicBodyRef newPhysicBody);
		void RemovePhysicBody(std::string name);

		bool IsEmpty();

		void Update(float dt);
		void Draw();
	};
}