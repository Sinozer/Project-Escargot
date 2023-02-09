#include "stdafx.h"

namespace Snail
{
	JoinState::JoinState(GameDataRef data) : m_data(data)
	{
		m_opacity = 0;
		m_isLoaded = false;
	}

	void JoinState::Init()
	{
		m_InitBackground();
		m_InitView();
	}

	void JoinState::m_InitBackground()
	{
		m_data->assetManager.LoadTexture("STATE_JOIN_BACKGROUND", STATE_JOIN_BACKGROUND_FILEPATH);
		m_background.setTexture(m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND"));
		m_background.setScale((float)m_data->window.getSize().x / (float)m_background.getTexture()->getSize().x, (float)m_data->window.getSize().y / (float)m_background.getTexture()->getSize().y);

		m_background.setColor(sf::Color(m_background.getColor().r, m_background.getColor().g, m_background.getColor().b, m_opacity));
	}

	void JoinState::m_InitView()
	{
		m_view.setSize(sf::Vector2f(m_data->window.getSize().x, m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f(m_data->window.getSize().x / 2, m_data->window.getSize().y / 2));
		m_data->window.setView(m_view);
	}

	void JoinState::HandleInput()
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

	void JoinState::Update(float dt)
	{
		if (m_data->inputManager.IsSpriteLeftClicked(m_background, m_data->window))
		{
			m_AddMainState();
		}

		m_UpdateBackground();
	}

	void JoinState::m_UpdateBackground()
	{
		if (!m_isLoaded && m_opacity < 255)
		{
			m_opacity++;
		}
		else
		{
			m_opacity--;
		}

		m_background.setColor(sf::Color(m_background.getColor().r, m_background.getColor().g, m_background.getColor().b, m_opacity));

		switch (m_opacity)
		{
		case 255:
			m_isLoaded = true;
			break;
		case 0:
			m_AddMainState();
			break;
		default:
			break;
		}
	}

	void JoinState::m_UpdateView()
	{
		
	}

	void JoinState::Draw(float dt)
	{
		m_data->window.draw(m_background);
	}

	void JoinState::m_AddMainState()
	{
		m_data->stateManager.RemoveState();
		m_data->stateManager.AddState(StateRef(new MainState(m_data)));
	}
}