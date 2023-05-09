#include "stdafx.h"
#include "SpawnerManager.h"

namespace Snail
{
#pragma region Singleton
	SpawnerManager* SpawnerManager::m_instance = nullptr;

	SpawnerManager::SpawnerManager()
	{
		m_InitUI();
	}

	SpawnerManager::~SpawnerManager()
	{
		for (Spawner* i : m_spawnerList)
			delete i;
	}

	bool SpawnerManager::IsInstance()
	{
		return m_instance != nullptr;
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

#pragma region TimerRelated
	void SpawnerManager::m_UpdateTimer()
	{
		if (m_currentState != STARTING) return;

		if (m_clock.getElapsedTime().asSeconds() >= m_timer)
			m_currentState = ACTIVE;
	}
#pragma endregion

#pragma region StateRelated
	void SpawnerManager::m_UpdateState()
	{
		m_previousState = m_currentState;

		switch (m_currentState)
		{
		case Snail::SpawnerManager::IDLE:

			if (!m_isReady) break;

			m_clock.restart();
			m_uiManager.Texts["MAIN"]->IsActive = true;
			m_currentState = STARTING;

			break;

		case Snail::SpawnerManager::STARTING:
			if (m_uiManager.Texts["START"]->IsActive)
			{
				AssetManager::GetInstance()->LoadSoundBuffer("UI_BUTTON_PRESSED", AUDIO_UI_CONFIRM_FILEPATH);
				AssetManager::GetInstance()->PlaySound("UI_BUTTON_PRESSED");

				AssetManager::GetInstance()->LoadMusic("STATE_GAME_PLAY_MUSIC", AUDIO_MUSIC_GAME_PLAY_FILEPATH);
				AssetManager::GetInstance()->PlayMusic("STATE_GAME_PLAY_MUSIC");
				m_uiManager.Texts["START"]->IsActive = false;
			}
			
			if (m_clock.getElapsedTime().asSeconds() < m_timer) break;

			m_currentState = ACTIVE;
			m_uiManager.Texts["MAIN"]->IsActive = false;

			break;

		case Snail::SpawnerManager::ACTIVE:

			if (m_areSpawnersReady)
				m_currentState = IDLE;

			break;
		}

		m_UpdateFromState();
	}

	void SpawnerManager::m_UpdateFromState()
	{
		switch (m_currentState)
		{
		case Snail::SpawnerManager::IDLE:
			if (m_previousState == ACTIVE)
				Ready(true);
			break;
		case Snail::SpawnerManager::STARTING:
			break;
		case Snail::SpawnerManager::ACTIVE:
			if (m_previousState == STARTING)
				m_SpawnWave();
			break;
		default:
			break;
		}
	}
#pragma endregion

#pragma region UIRelated
	void SpawnerManager::m_InitUI()
	{
		sf::Font& font = AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf");

		UIText* mainText = m_uiManager.AddText("MAIN", (float)Game::m_data->window.getSize().x / 2.f, (float)Game::m_data->window.getSize().y / 2.f, 0.f, 0.f, font, "", 80);
		mainText->SetOrigin(MID_MID);
		mainText->IsActive = false;
		mainText->SetOutlineColor(sf::Color::Black);
		mainText->SetOutlineThickness(2.f);

		UIText* startText = m_uiManager.AddText("START", (float)Game::m_data->window.getSize().x / 2.f, (float)Game::m_data->window.getSize().y, 0.f, 0.f, font, "Press 'N' to start", 50);
		startText->SetOrigin(BOT_MID);
		startText->SetOutlineColor(sf::Color::Black);
		startText->SetOutlineThickness(2.f);

		m_uiManager.AddText("WAVE", (float)Game::m_data->window.getSize().x / 2.f, 0.f, 0.f, 0.f, font, "WAVE: 0", 30);
		m_uiManager.Texts["WAVE"]->SetOrigin(TOP_MID);
		m_uiManager.Texts["WAVE"]->SetOutlineColor(sf::Color::Black);
		m_uiManager.Texts["WAVE"]->SetOutlineThickness(2.f);
	}

	void SpawnerManager::m_UpdateUI()
	{
		m_UpdateTexts();
	}

	void SpawnerManager::m_UpdateTexts()
	{
		switch (m_currentState)
		{
		case Snail::SpawnerManager::IDLE:
		{
			int alpha = static_cast<int>(Math::GetSineWaveValue());

			sf::Color color = sf::Color(255U, 255U, 255U, alpha);
			sf::Color outlineColor = sf::Color(0U, 0U, 0U, alpha);

			m_uiManager.Texts["START"]->SetTextColor(color);
			m_uiManager.Texts["START"]->SetOutlineColor(outlineColor);

			break;
		}
		case Snail::SpawnerManager::STARTING:
		{
			std::string temp = std::to_string(Math::Clamp(ceil(m_timer - m_clock.getElapsedTime().asSeconds()), 0.f, m_timer));
			temp = temp.substr(0, temp.find("."));

			if (m_wave < 1)
				temp = "Wave coming in " + temp + " seconds";
			else
				temp = "Next wave coming in " + temp + " seconds";
			
			m_uiManager.Texts["MAIN"]->SetFontSize(static_cast<unsigned int>(80 + round((Math::GetSineWaveValue(.5f, 40.f) - 20.f))));
			m_uiManager.Texts["MAIN"]->SetText(temp);
			break;
		}
		case Snail::SpawnerManager::ACTIVE:
			if (m_previousState == STARTING)
				m_uiManager.Texts["WAVE"]->SetText("WAVE: " + std::to_string(Math::Clamp(m_wave, 1, 9999)));
			break;
		default:
			break;
		}
	}

	void SpawnerManager::DrawUI()
	{
		m_uiManager.Draw();
	}
#pragma endregion

	void SpawnerManager::m_SpawnWave()
	{
		if (m_spawnerList.size() <= 0) return;

		m_wave++;

		Ready(false);

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
		m_currentState = IDLE;
		Ready(true);
	}

	void SpawnerManager::Ready(bool isReady)
	{
		m_isReady = isReady;
	}

	int SpawnerManager::GetWave()
	{
		return m_wave;
	}

	std::string SpawnerManager::GetWaveString()
	{
		return std::to_string(m_wave);
	}

	void SpawnerManager::Update()
	{
		m_UpdateState();

		m_UpdateSpawners();

		m_UpdateUI();
	}
}
