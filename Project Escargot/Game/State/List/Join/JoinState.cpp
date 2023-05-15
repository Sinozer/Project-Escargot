#include "stdafx.h"
#include "JoinState.h"
#include "Game/State/List/Main/MainState.h"

namespace Snail
{
	int JoinState::m_id = -1;

	JoinState::JoinState(GameDataRef data) : m_data(data)
	{
		if (m_id == -1)
			m_id = ID;
		else
			ID = m_id;
		
		Name = "JoinState";
		m_opacity = 0;
		m_isLoaded = false;
	}

	void JoinState::Init()
	{
		m_InitBackground();
		m_InitView();
		m_InitUIManager();
	}

	void JoinState::m_InitBackground()
	{
		AssetManager::GetInstance()->LoadTexture("STATE_JOIN_BACKGROUND", BACKGROUND_FOREST_FILEPATH);
		m_background.setTexture(AssetManager::GetInstance()->GetTexture("STATE_JOIN_BACKGROUND"));
		m_background.setScale((float)m_data->window.getSize().x / (float)m_background.getTexture()->getSize().x, (float)m_data->window.getSize().y / (float)m_background.getTexture()->getSize().y);

		m_background.setColor(sf::Color(m_background.getColor().r, m_background.getColor().g, m_background.getColor().b, m_opacity));
	}

	void JoinState::m_InitView()
	{
		m_view.setSize(sf::Vector2f((float)m_data->window.getSize().x, (float)m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f((float)m_data->window.getSize().x / 2.f, (float)m_data->window.getSize().y / 2.f));
		m_data->window.setView(m_view);
	}

	void JoinState::m_InitUIManager()
	{
		/*
			EMPTY
		*/
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

	void JoinState::Update()
	{
		if (InputManager::GetInstance(m_data->window)->IsSpriteLeftClicked(m_background))
		{
			m_AddMainState();
		}

		m_UpdateBackground();

		m_UpdateUIManager();
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
		/*
			EMPTY

			TODO: Remove / Transform view to camera
		*/
	}

	void JoinState::m_UpdateUIManager()
	{
		/*
			EMPTY
		*/
	}

	void JoinState::Draw()
	{
		m_data->window.draw(m_background);

		m_DrawUIManager();
	}

	void JoinState::DrawUI()
	{
	}

	void JoinState::End()
	{
	}

	void JoinState::m_DrawUIManager()
	{
		/*
			EMPTY
		*/
	}

	void JoinState::m_AddMainState()
	{
		m_data->stateManager.RemoveState();
		m_data->stateManager.AddState(StateRef(new MainState(m_data)));
	}
}