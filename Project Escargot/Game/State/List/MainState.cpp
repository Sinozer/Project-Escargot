#include "stdafx.h"

namespace Snail
{
	MainState::MainState(GameDataRef data) : m_data(data)
	{
		m_opacity = 0;
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
		m_data->assetManager.LoadTexture("STATE_JOIN_BACKGROUND", STATE_JOIN_BACKGROUND_FILEPATH);
		m_background.setTexture(m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND"));
		m_background.setScale((float)m_data->window.getSize().x / (float)m_background.getTexture()->getSize().x, (float)m_data->window.getSize().y / (float)m_background.getTexture()->getSize().y);

		m_background.setColor(sf::Color(m_background.getColor().r, m_background.getColor().g, m_background.getColor().b, m_opacity));
	}

	void MainState::m_InitView()
	{
		m_view.setSize(sf::Vector2f(m_data->window.getSize().x, m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f(m_data->window.getSize().x / 2, m_data->window.getSize().y / 2));
		m_data->window.setView(m_view);
	}

	void MainState::m_InitUIManager()
	{
		m_uiManager.AddText("TITLE", 100.f, 100.f, 100.f, 100.f, m_data->assetManager.LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "ZIZI", 150, sf::Color::Yellow, sf::Color::Green);
		
		m_uiManager.AddButton("PLAY", 200.f, 100.f, 200.f, 75.f, m_data->assetManager.LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Play", 60, sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Red, sf::Color::Green, sf::Color::Blue);
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

	void MainState::Update(float dt)
	{
		m_UpdateUIManager(dt);
	}

	void MainState::m_UpdateView()
	{
		
	}

	void MainState::m_UpdateUIManager(float dt)
	{
		m_uiManager.Update(m_data->inputManager.GetMousePosition(m_data->window), dt);

		if (m_uiManager.Buttons["PLAY"]->IsPressed())
			m_AddGameState();
	}

	void MainState::Draw(float dt)
	{
		m_data->window.draw(m_background);

		m_DrawUIManager();
	}

	void MainState::m_DrawUIManager()
	{
		m_uiManager.Draw(m_data->window);
	}

	void MainState::m_AddGameState()
	{
		m_data->stateManager.AddState(StateRef(new GameState(m_data)));
	}
}