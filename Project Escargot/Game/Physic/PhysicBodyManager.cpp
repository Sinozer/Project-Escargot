#include "stdafx.h"
#include "PhysicBodyManager.h"
namespace Snail
{
	std::vector<PhysicBodyManager*> PhysicBodyManager::m_instances;

	PhysicBodyManager::PhysicBodyManager(GameDataRef data)
	{
		m_data = data;
	}

	bool PhysicBodyManager::IsInstance()
	{
		return m_instances.size() > 0;
	}

	PhysicBodyManager* PhysicBodyManager::GetInstance()
	{
		if (m_instances.size() < STATE_COUNT_MAX)
			m_instances.assign(STATE_COUNT_MAX, nullptr);

		if (m_instances[Game::m_data->stateManager.GetActiveStateID()] == nullptr)
			m_instances.insert(m_instances.begin() + Game::m_data->stateManager.GetActiveStateID(), new PhysicBodyManager(Game::m_data));

		return m_instances[Game::m_data->stateManager.GetActiveStateID()];
	}

	void PhysicBodyManager::DestroyInstance()
	{
		if (m_instances.size() < STATE_COUNT_MAX)
			m_instances.assign(STATE_COUNT_MAX, nullptr);

		if (m_instances[Game::m_data->stateManager.GetActiveStateID()] != nullptr)
		{
			delete m_instances[Game::m_data->stateManager.GetActiveStateID()];
			m_instances[Game::m_data->stateManager.GetActiveStateID()] = nullptr;
		}
	}

	void PhysicBodyManager::DestroyAllInstances()
	{
		for (PhysicBodyManager* physicBodyManager : m_instances)
		{
			if (physicBodyManager != nullptr)
			{
				delete physicBodyManager;
				physicBodyManager = nullptr;
			}
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
			if (!physicBody.second || physicBody.second->IsStatic) continue;

			physicBody.second->Update();

			for (auto& otherPhysicBody : m_physicBodies)
			{
				if (otherPhysicBody == physicBody) continue;

				if ((physicBody.second->CollideMasks & otherPhysicBody.second->Masks) == MASK_EMPTY) continue;

				if ((physicBody.second->TriggerMasks & otherPhysicBody.second->Masks) == otherPhysicBody.second->Masks)
				{
					sf::Vector2f direction;
					if (physicBody.second && otherPhysicBody.second && physicBody.second->CheckCollision(otherPhysicBody.second, direction, true))
					{
						physicBody.second->IsTriggered = true;
						otherPhysicBody.second->IsTriggered = true;
						physicBody.second->TriggeredMasks |= otherPhysicBody.second->Masks;
						otherPhysicBody.second->TriggeredMasks |= physicBody.second->Masks;
					}
				}

				if ((physicBody.second->CollideMasks & otherPhysicBody.second->Masks) == otherPhysicBody.second->Masks)
				{
					sf::Vector2f direction;

					if (physicBody.second && otherPhysicBody.second && physicBody.second->CheckCollision(otherPhysicBody.second, direction)) {
						physicBody.second->OnCollision(direction);
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