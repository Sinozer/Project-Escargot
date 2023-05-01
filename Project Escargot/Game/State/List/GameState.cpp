#include "stdafx.h"
#include "GameState.h"
#include "Game/Map/Map.h"
namespace Snail
{
	GameState::GameState(GameDataRef data) : m_data(data), m_spawner(m_data)
	{
		m_player = Player::GetInstance();
	}

	void GameState::Init()
	{
		m_InitBackground();
		m_InitView();
		m_InitUIManager();
		m_InitMap();

		m_player->Init();
		m_spawner.Init();
		m_collectable.Init();
	}

	void GameState::m_InitBackground()
	{
		AssetManager::GetInstance()->LoadTexture("STATE_GAME_BACKGROUND", STATE_MAIN_BACKGROUND_FILEPATH);
		m_background.setTexture(AssetManager::GetInstance()->GetTexture("STATE_GAME_BACKGROUND"));
		m_background.scale(sf::Vector2f(0.25f, 0.25f));
	}

	void GameState::m_InitView()
	{
		m_view.setSize(sf::Vector2f(m_data->window.getSize().x, m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f(m_data->window.getSize().x / 2, m_data->window.getSize().y / 2));
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
		m_uiManager.AddText("SCORE", m_data->window.getSize().x, 0.f, 0.f, 0.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "SCORE: X", 60, sf::Color::White, sf::Color::Transparent);
		m_uiManager.Texts["SCORE"]->SetOrigin(TOP_RIGHT);
		m_uiManager.Texts["SCORE"]->SetOutlineColor(sf::Color::Black);
		m_uiManager.Texts["SCORE"]->SetOutlineThickness(2.f);
		
		m_uiManager.AddText("AMMO", m_data->window.getSize().x, m_data->window.getSize().y, 0.f, 0.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "X / Y", 46, sf::Color::White, sf::Color::Transparent);
		m_uiManager.Texts["AMMO"]->SetOrigin(BOT_RIGHT);
		m_uiManager.Texts["AMMO"]->SetOutlineColor(sf::Color::Black);
		m_uiManager.Texts["AMMO"]->SetOutlineThickness(2.f);
	}

	void GameState::m_InitUIButtons()
	{
	}

	void GameState::m_InitMap()
	{
		Map map(m_data, "Resources/Data/Map/TestDebug.json");
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_data->stateManager.RemoveState();
		
		m_player->HandleInput();
	}

	void GameState::Update()
	{
		m_UpdateView();
		
		PhysicBodyManager::GetInstance()->Update();
		m_player->Update();
		m_spawner.Update();

		m_UpdateUIManager();
	}

	void GameState::m_UpdateView()
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(m_data->window);
			mousePosition = Math::Clamp(mousePosition, sf::Vector2f(0.f, 0.f), (sf::Vector2f)m_data->window.getSize());
			m_background.setOrigin(mousePosition / /*value*/8.f); // Value = map size / background size
			m_view.setCenter(mousePosition);
			m_spawner.Spawn();
		}
		else
		{
			m_background.setOrigin(m_player->GetPhysicBodyRef()->GetPosition() / /*value*/8.f); // Value = map size / background size
			m_view.setCenter(m_player->GetPhysicBodyRef()->GetPosition());
		}
		m_data->window.setView(m_view);
	}

	void GameState::m_UpdateUIManager()
	{
		m_uiManager.Update((sf::Vector2i)InputManager::GetInstance(m_data->window)->GetMousePosition());
	
		m_uiManager.Texts["SCORE"]->SetText("SCORE: " + std::to_string(Player::GetInstance()->GetScore()));

		m_uiManager.Texts["AMMO"]->SetText(m_player->GetMunitionsString() + " / " + m_player->GetAllMunitionsString());
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
	}

	void GameState::m_DrawUIManager()
	{
		m_uiManager.Draw(m_data->window);
	}

	void GameState::End()
	{
		Player::DestroyInstance();
	}
}