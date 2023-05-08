#include "stdafx.h"
#include "CollectableManager.h"

namespace Snail
{
	
#pragma region Singleton
	CollectableManager* CollectableManager::m_instance = nullptr;

	CollectableManager::CollectableManager()
	{
		AssetManager::GetInstance()->LoadTexture("Collectable_0", STATE_GAME_COLLECTABLE_LIFE);
		AssetManager::GetInstance()->LoadTexture("Collectable_1", STATE_GAME_COLLECTABLE_AMMO);
	}

	CollectableManager* CollectableManager::GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CollectableManager();

		return m_instance;
	}

	void CollectableManager::DestroyInstance()
	{
		if (m_instance != nullptr)
			delete m_instance;
		m_instance = nullptr;
	}
#pragma endregion

#pragma region Destructor
	CollectableManager::~CollectableManager()
	{
		for (auto& i : m_collectables)
			delete i;
	}
#pragma endregion

#pragma region CollectableBehaviour
	void CollectableManager::m_UpdateCollectables()
	{
		if (m_collectables.size() <= 0) return;

		for (Collectable* collectable : m_collectables)
		{
			collectable->Update();
		}
	}

	void CollectableManager::AddCollectable(sf::Vector2f position)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(0.0f, 1.0f);
		
		float roll = dis(gen);
		
		if (roll > 0.16f) return;
		
		m_collectables.push_back(new Collectable());
		m_collectables.back()->Init(position);
	}

	void CollectableManager::AddCollectable(sf::Vector2f position, Collectable::Type type)
	{
		m_collectables.push_back(new Collectable(type));
		m_collectables.back()->Init(position);
	}

	void CollectableManager::RemoveCollectable(int index)
	{
		if (m_collectables.size() >= index)
			throw std::invalid_argument("Index out of range");

		m_collectables.erase(m_collectables.begin() + index);
	}

	void CollectableManager::RemoveFirstCollectable()
	{
		RemoveCollectable(0);
	}

	void CollectableManager::RemoveLastCollectable()
	{
		m_collectables.pop_back();
	}
#pragma endregion
	
	void CollectableManager::Update()
	{
		std::vector<Collectable*> temp;

		for (int i = (int)m_collectables.size() - 1; i >= 0; i--)
		{
			if (m_collectables[i]->IsDeleted)
			{
				temp.push_back(m_collectables[i]);
				continue;
			}

			m_collectables[i]->Update();
		}

		for (auto& p : temp)
		{
			p->Destroy();
			delete p;
			std::vector<Collectable*>::iterator toDelete = std::find(m_collectables.begin(), m_collectables.end(), p);

			if (toDelete != m_collectables.end())
				m_collectables.erase(toDelete);
		}
	}

	void CollectableManager::Draw()
	{
		for (auto& i : m_collectables)
			i->Draw();
	}
}
