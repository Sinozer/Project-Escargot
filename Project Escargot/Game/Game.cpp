#include "stdafx.h"

namespace Snail
{
	Game::Game(int width, int height, std::string title)
	{
		m_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		m_data->window.setFramerateLimit(WINDOW_SCREEN_FRAMERATE_MED);

		m_data->stateManager.AddState(StateRef(new JoinState(m_data)));

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

			m_data->window.display();
		}
		End();
	}

	void Game::End()
	{
		m_data->window.close();
	}
}