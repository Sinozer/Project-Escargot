#include "stdafx.h"
#include "PhysicBodyManager.h"
namespace Snail
{
	std::vector<PhysicBodyManager*> PhysicBodyManager::m_instance;

	PhysicBodyManager::PhysicBodyManager(GameDataRef data)
	{
		m_data = data;
	}

	PhysicBodyManager* PhysicBodyManager::GetInstance()
	{
		if (m_instance.size() < STATE_COUNT_MAX)
			m_instance.assign(STATE_COUNT_MAX, nullptr);

		if (m_instance[Game::m_data->stateManager.GetActiveStateID()] == nullptr)
			m_instance.insert(m_instance.begin() + Game::m_data->stateManager.GetActiveStateID(), new PhysicBodyManager(Game::m_data));

		return m_instance[Game::m_data->stateManager.GetActiveStateID()];
	}

	void PhysicBodyManager::DestroyInstance()
	{
		if (m_instance.size() < STATE_COUNT_MAX)
			m_instance.assign(STATE_COUNT_MAX, nullptr);

		if (m_instance[Game::m_data->stateManager.GetActiveStateID()] != nullptr)
		{
			delete m_instance[Game::m_data->stateManager.GetActiveStateID()];
			m_instance[Game::m_data->stateManager.GetActiveStateID()] = nullptr;
		}
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

					if (physicBody.second && otherPhysicBody.second && physicBody.second->CheckCollision(otherPhysicBody.second, direction)) {
						physicBody.second->OnCollision(direction);
						if (m_physicBodies.find("Collectible")->second->CheckCollision(physicBody.second, direction) == true) {
							std::cout << "colect\n";
						}
					}
				}
			}
		}
	}

	void PhysicBodyManager::Draw()
	{
		if (m_data == NULL || m_physicBodies.empty()) return;

		sf::RectangleShape shape;

		for (auto& physicBody : m_physicBodies)
			if (physicBody.second)
				physicBody.second->Draw(m_data->window);
	}
}