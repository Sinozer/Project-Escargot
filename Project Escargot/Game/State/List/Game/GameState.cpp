#include "stdafx.h"
#include "GameState.h"
#include "End/GameEndState.h"
#include "Game/Spawner/SpawnerManager.h"
#include "Game/Entity/Collectables/CollectableManager.h"
namespace Snail
{
	GameState::GameState(GameDataRef data) : m_data(data)
	{
		Name = "GameState";
		m_player = Player::GetInstance();
	}

	void GameState::Init()
	{
		m_InitBackground();
		m_InitView();
		m_InitUIManager();
		m_InitMap();
		m_InitSpawnerManager();

		m_player->Init(sf::Vector2f(800.f, 250.f));
	}

	void GameState::m_InitBackground()
	{
		AssetManager::GetInstance()->LoadTexture("STATE_GAME_BACKGROUND", STATE_GAME_BACKGROUND_FILEPATH);
		m_background.setTexture(AssetManager::GetInstance()->GetTexture("STATE_GAME_BACKGROUND"));
		m_background.scale(sf::Vector2f(0.273f, 0.273f));
	}

	void GameState::m_InitView()
	{
		m_view.setSize(sf::Vector2f((float)m_data->window.getSize().x, (float)m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f((float)m_data->window.getSize().x / 2.f, (float)m_data->window.getSize().y / 2.f));
		m_view.zoom(0.25f);
		//m_view.setRotation(45.f);
		m_data->window.setView(m_view);
	}

	void GameState::m_InitUIManager()
	{
		m_InitUITexts();
		m_InitUIButtons();
	}

	void GameState::m_InitUITexts()
	{
		sf::Font& font = AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf");

		m_uiManager.AddText("SCORE", (float)m_data->window.getSize().x, 0.f, 0.f, 0.f, font, "SCORE: X", 60);
		m_uiManager.Texts["SCORE"]->SetOrigin(TOP_RIGHT);
		m_uiManager.Texts["SCORE"]->SetOutlineColor(sf::Color::Black);
		m_uiManager.Texts["SCORE"]->SetOutlineThickness(2.f);

		m_uiManager.AddText("AMMO", (float)m_data->window.getSize().x, (float)m_data->window.getSize().y, 0.f, 0.f, font, "X | Y", 46);
		m_uiManager.Texts["AMMO"]->SetOrigin(BOT_RIGHT);
		m_uiManager.Texts["AMMO"]->SetOutlineColor(sf::Color::Black);
		m_uiManager.Texts["AMMO"]->SetOutlineThickness(2.f);

		m_uiManager.AddText("LIFE", 0.f, (float)m_data->window.getSize().y, 0.f, 0.f, font, "X / Y HP", 46);
		m_uiManager.Texts["LIFE"]->SetOrigin(BOT_LEFT);
		m_uiManager.Texts["LIFE"]->SetOutlineColor(sf::Color::Black);
		m_uiManager.Texts["LIFE"]->SetOutlineThickness(2.f);
	}

	void GameState::m_InitUIButtons()
	{
	}

	void GameState::m_InitMap()
	{
		m_map = Map(m_data, "Resources/Data/Map/VerticalSlice/Main.json");
	}

	void GameState::m_InitSpawnerManager()
	{
		SpawnerManager::GetInstance()->AddSpawner(sf::Vector2f(150.f, 100.f));
		SpawnerManager::GetInstance()->AddSpawner(sf::Vector2f(800.f, 250.f));
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (m_data->window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				m_data->window.close();
				break;
			}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && (DEBUG || DEBUG_CONTROL))
			SpawnerManager::GetInstance()->Ready(true);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_data->stateManager.RemoveState();

		m_player->HandleInput();
	}

	void GameState::Update()
	{
		m_UpdateView();

		PhysicBodyManager::GetInstance()->Update();
		m_player->Update();
		SpawnerManager::GetInstance()->Update();
		CollectableManager::GetInstance()->Update();

		m_UpdateUIManager();
	}

	void GameState::m_UpdateView()
	{
		sf::Vector2f position;
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			position = (sf::Vector2f)sf::Mouse::getPosition(m_data->window);
		else
			position = (sf::Vector2f)m_player->GetPhysicBodyRef()->GetPosition();

		// Get the size of the background image and the view
		sf::Vector2f viewSize = m_view.getSize();
		sf::Vector2f windowSize = (sf::Vector2f)m_data->window.getSize();

		// Calculate the maximum view position based on the background, view, and window sizes
		sf::Vector2f maxViewPos = m_map.MaxSize - viewSize;
		maxViewPos.x = std::max(maxViewPos.x, 0.f);
		maxViewPos.y = std::max(maxViewPos.y, 0.f);

		// Clamp the position to the maximum view position
		sf::Vector2f clampedPos = Math::Clamp(position, viewSize / 2.f, maxViewPos + viewSize / 2.f);
		clampedPos.x -= 8.f;
		clampedPos.y -= 8.f;

		// Calculate the background origin based on the clamped position and the map/background ratio
		sf::Vector2f backgroundOrigin = (clampedPos - viewSize / 2.f) / 8.f;
		backgroundOrigin += sf::Vector2f(30.f, 30.f);
			
		// Set the background origin and the view center
		m_background.setOrigin(backgroundOrigin);
		m_view.setCenter(clampedPos);

		m_data->window.setView(m_view);
	}

	void GameState::m_UpdateUIManager()
	{
		m_uiManager.Update();

		m_uiManager.Texts["SCORE"]->SetText("SCORE: " + std::to_string(Player::GetInstance()->GetScore()));

		m_uiManager.Texts["AMMO"]->SetText(m_player->GetMunitionsString() + " | " + m_player->GetAllMunitionsString());

		m_uiManager.Texts["LIFE"]->SetText(m_player->GetLifeString() + " / " + m_player->GetMaxLifeString() + " HP");
	}

	void GameState::Draw()
	{
		m_data->window.draw(m_background);
		if (!PhysicBodyManager::GetInstance()->IsEmpty())
			PhysicBodyManager::GetInstance()->Draw();
	}

	void GameState::DrawUI()
	{
		m_DrawUIManager();

		SpawnerManager::GetInstance()->DrawUI();
	}

	void GameState::m_DrawUIManager()
	{
		m_uiManager.Draw();
	}

	void GameState::End()
	{
		Player::DestroyInstance();
		SpawnerManager::DestroyInstance();
		CollectableManager::GetInstance()->DestroyInstance();
	}
}