#include "stdafx.h"

namespace Snail
{
	PhysicBodyManager::PhysicBodyManager(GameDataRef data)
	{
		m_data = data;
	}

	void PhysicBodyManager::AddPhysicBody(std::string name, PhysicBodyRef newPhysicBody)
	{
		m_newPhysicBody = move(newPhysicBody);
		m_physicBodies.insert({ name, move(m_newPhysicBody) });
	}

	void PhysicBodyManager::RemovePhysicBody(std::string name)
	{
		if (m_physicBodies.find(name) != m_physicBodies.end())
			m_physicBodies.erase(name);
	}

	bool PhysicBodyManager::IsEmpty()
	{
		return m_physicBodies.empty();
	}

	void PhysicBodyManager::Update(float dt)
	{
		if (m_physicBodies.empty())
			return;

		for (auto& physicBody : m_physicBodies)
		{
			if (physicBody.second && !physicBody.second->m_IsStatic)
			{
				/**
				 * \brief The physic body check for collision.
				 *
				 * \TODO Implement physicBody.second->m_IsAffectedByGravity.
				 * ***** If true, the physic body is affected by gravity.
				 *
				 */
				physicBody.second->Update(dt);

				for (auto& otherPhysicBody : m_physicBodies)
				{
					if (otherPhysicBody == physicBody) continue;
					sf::Vector2f direction;

					if (physicBody.second && otherPhysicBody.second && physicBody.second->CheckCollision(otherPhysicBody.second, direction))
						physicBody.second->OnCollision(direction);
				}
			}
		}
	}

	void PhysicBodyManager::Draw()
	{
		if (m_data == NULL || m_physicBodies.empty()) return;

		sf::RectangleShape shape;

		for (auto& physicBody : m_physicBodies)
		{
			if (physicBody.second)
				if (physicBody.second->GetPosition() == sf::Vector2f(-1.f, -1.f))
					std::cout << "OUI\n";
			
			if (physicBody.second)
				physicBody.second->Draw(m_data->window);
		}
	}
}