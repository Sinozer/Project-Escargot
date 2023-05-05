#pragma once
#include "Spawner.h"
namespace Snail
{
	class SpawnerManager
	{
#pragma region Singleton
	private:
		static SpawnerManager* m_instance;

		SpawnerManager();

	public:
		static SpawnerManager* GetInstance();
		static void DestroyInstance();
#pragma endregion
		
#pragma region SpawnerBehaviour
	private:
		std::vector<Spawner*> m_spawnerList;
	
		bool m_areSpawnersReady = true;

	private:
		void m_UpdateSpawners();

	public:
		void AddSpawner();
		void AddSpawner(sf::Vector2f position);
		void RemoveSpawner(int index);
		void RemoveFirstSpawner();
		void RemoveLastSpawner();
#pragma endregion
	private:
		enum CurrentState
		{
			IDLE,
			ACTIVE
		};
		CurrentState m_currentState = IDLE;
	private:
		// Define if the SpawnerManager can make his things
		bool m_isReady = false;

		// Define the current wave
		int m_wave = 0;

	private:
		void m_SpawnWave();

		void m_CheckWave();
		
	public:
		void Ready(bool isReady = false);
		
		// Get the current wave
		int GetWave();

		void Update();
	};
}