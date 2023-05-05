#include "stdafx.h"
#include "MainState.h"
#include "Game/State/List/Game/GameState.h"
#include "Game/State/List/Settings/SettingsState.h"

namespace Snail
{
	MainState::MainState(GameDataRef data) : m_data(data)
	{
		m_opacity = 128;
		m_isLoaded = false;
	}

	void MainState::Init()
	{
		m_InitBackground();
		m_InitView();
		m_InitUIManager();
	}

	void MainState::m_InitBackground()
	{
		AssetManager::GetInstance()->LoadTexture("STATE_MAIN_BACKGROUND", BACKGROUND_PINKDESERT_FILEPATH);
		m_background.setTexture(AssetManager::GetInstance()->GetTexture("STATE_MAIN_BACKGROUND"));
		m_background.setScale((float)m_data->window.getSize().x / (float)m_background.getTexture()->getSize().x, (float)m_data->window.getSize().y / (float)m_background.getTexture()->getSize().y);

		m_background.setColor(sf::Color(m_background.getColor().r, m_background.getColor().g, m_background.getColor().b, m_opacity));
	}

	void MainState::m_InitView()
	{
		m_view.setSize(sf::Vector2f((float)m_data->window.getSize().x, (float)m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f((float)m_data->window.getSize().x / 2.f, (float)m_data->window.getSize().y / 2.f));
		m_data->window.setView(m_view);
	}

	void MainState::m_InitUIManager()
	{
		m_InitUITexts();
		m_InitUIButtons();
	}

	void MainState::m_InitUITexts()
	{
		m_uiManager.AddText("TITLE", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 12.f, 0.f, 0.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Project Escargot", 92, sf::Color::White, sf::Color::Transparent);
		m_uiManager.Texts["TITLE"]->SetOutlineColor(sf::Color::Black);
		m_uiManager.Texts["TITLE"]->SetOutlineThickness(2.f);
	}

	void MainState::m_InitUIButtons()
	{
		m_uiManager.AddButton("PLAY", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 2.2f, 200.f, 75.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Play", 60, sf::Color(128, 128, 128), sf::Color::White, sf::Color::White, sf::Color(128, 128, 128, 128), sf::Color(128, 128, 128, 192), sf::Color(128, 128, 128));

		m_uiManager.AddButton("SETTINGS", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 1.70f, 200.f, 75.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Settings", 60, sf::Color(128, 128, 128), sf::Color::White, sf::Color::White, sf::Color(128, 128, 128, 128), sf::Color(128, 128, 128, 192), sf::Color(128, 128, 128));
		
		m_uiManager.AddButton("QUIT", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 1.25f, 150.f, 50.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Quit", 40, sf::Color(128, 128, 128), sf::Color::White, sf::Color::White, sf::Color(128, 128, 128, 128), sf::Color(128, 128, 128, 192), sf::Color(128, 128, 128));
	}

	void MainState::HandleInput()
	{
		sf::Event event;

		while (m_data->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_data->window.close();
				break;
			default:
				break;
			}
		}
	}

	void MainState::Update()
	{
		m_UpdateUIManager();
	}

	void MainState::m_UpdateView()
	{
		
	}

	void MainState::m_UpdateUIManager()
	{
		m_uiManager.Update((sf::Vector2i)InputManager::GetInstance(m_data->window)->GetMousePosition());

		if (m_uiManager.Buttons["PLAY"]->IsPressed())
			m_data->stateManager.AddState(StateRef(new GameState(m_data)));

		if (m_uiManager.Buttons["SETTINGS"]->IsPressed())
			m_data->stateManager.AddState(StateRef(new SettingsState(m_data)));

		if (m_uiManager.Buttons["QUIT"]->IsPressed())
			m_data->window.close();
	}

	void MainState::Draw()
	{
		m_data->window.draw(m_background);
	}

	void MainState::DrawUI()
	{
		m_DrawUIManager();
	}

	void MainState::End()
	{
	}

	void MainState::m_DrawUIManager()
	{
		m_uiManager.Draw(m_data->window);
	}
}