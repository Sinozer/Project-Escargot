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
		~SpawnerManager();
		
	public:
		static bool IsInstance();
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
		
#pragma region TimerRelated
	private :
		float m_timer = 5.f;
		sf::Clock m_clock;

		bool m_timerReady = false;

	private:
		void m_UpdateTimer();

#pragma endregion

#pragma region StateRelated
	private:
		enum CurrentState
		{
			IDLE,
			STARTING,
			ACTIVE
		};
		CurrentState m_previousState = IDLE;
		CurrentState m_currentState = IDLE;

	private:
		void m_UpdateState();
		void m_UpdateFromState();
#pragma endregion

#pragma region UIRelated
	private:
		UIManager m_uiManager;

	private:
		void m_InitUI();
		void m_UpdateUI();
		void m_UpdateTexts();
		
	public:
		void DrawUI();
#pragma endregion

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
		std::string GetWaveString();

	public:
		void Update();
	};
}