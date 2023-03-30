#include "stdafx.h"

namespace Snail
{
	Game::Game(int width, int height, std::string title)
	{
		m_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		m_data->window.setFramerateLimit(WINDOW_SCREEN_FRAMERATE_MED);

		// Debug text
		m_data->assetManager.LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf");
		m_text = sf::Text("PROJECT SNAIL\nPROTOTYPE", m_data->assetManager.GetFont("ROBOTO_CONDENSED_ITALIC"), 30);
		m_text.setFillColor(sf::Color::White);
		m_text.setOutlineColor(sf::Color::Black);
		m_text.setOutlineThickness(2);
		m_text.setPosition(20.f, 0.f);

		m_data->stateManager.AddState(StateRef(new JoinState(m_data)));

		// Init InputManager
		InputManager::GetInstance(m_data->window);

		Run();
	}

	void Game::m_UpdateDt()
	{
		m_dt = m_clock.restart().asSeconds();
	}

	void Game::Run()
	{
		while (m_data->window.isOpen())
		{
			m_UpdateDt();

			m_data->stateManager.ProcessStateChanges();

			if (m_data->stateManager.IsEmpty()) break;

			m_data->stateManager.GetActiveState()->HandleInput();
			m_data->stateManager.GetActiveState()->Update(m_dt);

			m_data->window.clear(sf::Color::Black);

			m_data->stateManager.GetActiveState()->Draw(m_dt);
			m_data->window.setView(m_data->window.getDefaultView());
			m_data->window.draw(m_text);

			m_data->window.display();
		}
		End();
	}

	void Game::End()
	{
		m_data->window.close();
	}
}