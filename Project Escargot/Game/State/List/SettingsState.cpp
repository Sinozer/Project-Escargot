#include "stdafx.h"

namespace Snail
{
	SettingsState::SettingsState(GameDataRef data) : m_data(data)
	{
		m_opacity = 0;
		m_isLoaded = false;
	}

	void SettingsState::Init()
	{
		m_InitBackground();
		m_InitView();
		m_InitUIManager();
	}

	void SettingsState::m_InitBackground()
	{
		m_data->assetManager.LoadTexture("STATE_JOIN_BACKGROUND", STATE_JOIN_BACKGROUND_FILEPATH);
		m_background.setTexture(m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND"));
		m_background.setScale((float)m_data->window.getSize().x / (float)m_background.getTexture()->getSize().x, (float)m_data->window.getSize().y / (float)m_background.getTexture()->getSize().y);

		m_background.setColor(sf::Color(m_background.getColor().r, m_background.getColor().g, m_background.getColor().b, m_opacity));
	}

	void SettingsState::m_InitView()
	{
		m_view.setSize(sf::Vector2f(m_data->window.getSize().x, m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f(m_data->window.getSize().x / 2, m_data->window.getSize().y / 2));
		m_data->window.setView(m_view);
	}

	void SettingsState::m_InitUIManager()
	{
		m_InitUITexts();
		m_InitUIButtons();
	}

	void SettingsState::m_InitUITexts()
	{
		m_uiManager.AddText("TITLE", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 12.f, 0.f, 0.f, m_data->assetManager.LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Settings", 92, sf::Color::White, sf::Color::Transparent);
	}

	void SettingsState::m_InitUIButtons()
	{
		m_uiManager.AddButton("RETURN", m_data->window.getSize().x / 4.f - 75.f, m_data->window.getSize().y / 1.25f, 150.f, 50.f, m_data->assetManager.LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Return", 40, sf::Color(128, 128, 128), sf::Color::White, sf::Color::White, sf::Color(128, 128, 128, 128), sf::Color(128, 128, 128, 192), sf::Color(128, 128, 128));
	}

	void SettingsState::HandleInput()
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

	void SettingsState::Update(float dt)
	{
		m_UpdateUIManager(dt);
	}

	void SettingsState::m_UpdateView()
	{
		
	}

	void SettingsState::m_UpdateUIManager(float dt)
	{
		m_uiManager.Update(m_data->inputManager.GetMousePosition(m_data->window), dt);

		if (m_uiManager.Buttons["RETURN"]->IsPressed())
			m_data->stateManager.RemoveState();
	}

	void SettingsState::Draw(float dt)
	{
		m_data->window.draw(m_background);

		m_DrawUIManager();
	}

	void SettingsState::m_DrawUIManager()
	{
		m_uiManager.Draw(m_data->window);
	}
}