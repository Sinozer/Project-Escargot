#include "stdafx.h"
#include "Game.h"
#include "State/List/Join/JoinState.h"
#include "Entity/LivingEntity/Player/Player.h"

namespace Snail
{
	GameDataRef Game::m_data;

	Game::Game(int width, int height, std::string title)
	{
		m_data = std::make_shared<GameData>();

		m_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen);
		m_data->window.setFramerateLimit(WINDOW_SCREEN_FRAMERATE_MED);

		// Debug text
		AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf");
		m_text = sf::Text("PROJECT SNAIL\nVERTICAL SLICE", AssetManager::GetInstance()->GetFont("ROBOTO_CONDENSED_ITALIC"), 30);
		m_text.setFillColor(sf::Color::White);
		m_text.setOutlineColor(sf::Color::Black);
		m_text.setOutlineThickness(2.f);
		m_text.setPosition(20.f, 0.f);

		m_data->stateManager.AddState(StateRef(new JoinState(m_data)));

		InputManager::GetInstance(m_data->window);

		Run();
	}

	void Game::m_UpdateDt()
	{
		m_dt = m_clock.restart().asSeconds();
		if (m_dt < 1.f)
			m_data->deltaTime = m_dt;
		else
			m_data->deltaTime = 0.f;
	}

	void Game::Run()
	{
		while (m_data->window.isOpen())
		{
			m_UpdateDt();

			m_data->stateManager.ProcessStateChanges();

			if (m_data->stateManager.IsEmpty()) break;

			m_data->stateManager.GetActiveState()->HandleInput();
			m_data->stateManager.GetActiveState()->Update();

			m_data->window.clear(sf::Color::Black);

			m_data->stateManager.GetActiveState()->Draw();
			m_data->window.setView(m_data->window.getDefaultView());
			m_data->window.draw(m_text);
			m_data->stateManager.GetActiveState()->DrawUI();

			m_data->window.display();
		}
		End();
	}

	void Game::End()
	{
		m_data->window.close();

		AssetManager::DestroyInstance();
	}
}