#include "stdafx.h"
#include "SpawnerManager.h"

namespace Snail
{
#pragma region Singleton
	SpawnerManager* SpawnerManager::m_instance = nullptr;

	SpawnerManager::SpawnerManager()
	{
	}

	SpawnerManager* SpawnerManager::GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new SpawnerManager();

		return m_instance;
	}

	void SpawnerManager::DestroyInstance()
	{
		if (m_instance != nullptr)
			delete m_instance;
		m_instance = nullptr;
	}
#pragma endregion

#pragma region SpawnerBehaviour
	void SpawnerManager::m_UpdateSpawners()
	{
		if (m_spawnerList.size() <= 0) return;

		m_areSpawnersReady = true;

		for (Spawner* spawner : m_spawnerList)
		{
			spawner->Update();

			if (!spawner->Ready)
				m_areSpawnersReady = false;
		}
	}

	void SpawnerManager::AddSpawner()
	{
		m_spawnerList.push_back(new Spawner());
		m_spawnerList.back()->Init();
	}

	void SpawnerManager::AddSpawner(sf::Vector2f position)
	{
		m_spawnerList.push_back(new Spawner());
		m_spawnerList.back()->Init(position);
	}

	void SpawnerManager::RemoveSpawner(int index)
	{
		if (m_spawnerList.size() >= index)
			throw std::invalid_argument("Index out of range");

		m_spawnerList.erase(m_spawnerList.begin() + index);
	}

	void SpawnerManager::RemoveFirstSpawner()
	{
		RemoveSpawner(0);
	}

	void SpawnerManager::RemoveLastSpawner()
	{
		m_spawnerList.pop_back();
	}
#pragma endregion

	void SpawnerManager::m_SpawnWave()
	{
		if (!m_isReady || !m_areSpawnersReady) return;
		if (m_spawnerList.size() <= 0) return;
		
		m_isReady = false;

		// Change difficulty formula
		int amount = STATE_GAME_BASE_ENEMIES_AMOUNT + m_wave;

		for (size_t i = 0; i < amount; i++)
		{
			int s = rand() % m_spawnerList.size();
			m_spawnerList[s]->Spawn();
		}
		
		m_areSpawnersReady = false;
	}

	void SpawnerManager::m_CheckWave()
	{
		if (m_currentState != ACTIVE || !m_areSpawnersReady) return;
		
		Ready(true);
	}

	void SpawnerManager::Ready(bool isReady)
	{
		m_isReady = isReady;
		if (!isReady) return;
		m_wave++;
		m_currentState = ACTIVE;
	}

	int SpawnerManager::GetWave()
	{
		return m_wave;
	}

	void SpawnerManager::Update()
	{
		m_UpdateSpawners();
		m_SpawnWave();
		m_CheckWave();
	}
}
