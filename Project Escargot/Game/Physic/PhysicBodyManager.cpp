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

	void PhysicBodyManager::Update()
	{
		if (m_physicBodies.empty())
			return;

		for (auto& physicBody : m_physicBodies)
		{
			if (physicBody.second && !physicBody.second->IsStatic)
			{
				physicBody.second->Update();

				for (auto& otherPhysicBody : m_physicBodies)
				{
					if (otherPhysicBody == physicBody) continue;

					if ((physicBody.second->CollideMasks & otherPhysicBody.second->Masks) == MASK_EMPTY) continue;

					if ((physicBody.second->TriggerMasks & otherPhysicBody.second->Masks) == otherPhysicBody.second->Masks)
					{
						sf::Vector2f direction;
						if (physicBody.second && otherPhysicBody.second && physicBody.second->CheckCollision(otherPhysicBody.second, direction))
							physicBody.second->IsTriggered = true;
					}

					if ((physicBody.second->CollideMasks & otherPhysicBody.second->Masks) == otherPhysicBody.second->Masks)
					{
						sf::Vector2f direction;

						if (physicBody.second && otherPhysicBody.second && physicBody.second->CheckCollision(otherPhysicBody.second, direction)) {
							physicBody.second->OnCollision(direction);
							/*if (m_physicBodies.find("Collectable")->second->CheckCollision(physicBody.second, direction) == true) {
								std::cout << "colect\n";
							}*/
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