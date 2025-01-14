#include "stdafx.h"
#include "SettingsState.h"
namespace Snail
{
	int SettingsState::m_id = -1;
	
	SettingsState::SettingsState(GameDataRef data) : m_data(data)
	{
		//m_opacity = 128;
		if (m_id == -1)
			m_id = ID;
		else
			ID = m_id;
		
		Name = "SettingsState";
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
		AssetManager::GetInstance()->LoadTexture("STATE_SETTINGS_BACKGROUND", BACKGROUND_DAWNMOUNTAIN_FILEPATH);
		m_background.setTexture(AssetManager::GetInstance()->GetTexture("STATE_SETTINGS_BACKGROUND"));
		m_background.setScale((float)m_data->window.getSize().x / (float)m_background.getTexture()->getSize().x, (float)m_data->window.getSize().y / (float)m_background.getTexture()->getSize().y);

		m_background.setColor(sf::Color(m_background.getColor().r, m_background.getColor().g, m_background.getColor().b, 128U));
	}

	void SettingsState::m_InitView()
	{
		m_view.setSize(sf::Vector2f((float)m_data->window.getSize().x, (float)m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f((float)m_data->window.getSize().x / 2.f, (float)m_data->window.getSize().y / 2.f));
		m_data->window.setView(m_view);
	}

	void SettingsState::m_InitUIManager()
	{
		m_InitUITexts();
		m_InitUIButtons();
	}

	void SettingsState::m_InitUITexts()
	{
		m_uiManager.AddText("TITLE", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 12.f, 0.f, 0.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Settings", 92, sf::Color::White, sf::Color::Transparent);
		m_uiManager.Texts["TITLE"]->SetOutlineColor(sf::Color::Black);
		m_uiManager.Texts["TITLE"]->SetOutlineThickness(2.f);
	}

	void SettingsState::m_InitUIButtons()
	{
		sf::Color textIdleColor(192U, 192U, 192U);
		sf::Color textHoverColor(255U, 255U, 255U, 255U);
		sf::Color textActiveColor(255U, 255U, 255U, 255U);

		sf::Color containerIdleColor(42U, 42U, 42U, 128U);
		sf::Color containerHoverColor(42U, 42U, 42U, 192U);
		sf::Color containerActiveColor(42U, 42U, 42U, 255U);
		
		m_uiManager.AddButton("RETURN", m_data->window.getSize().x / 4.f - 75.f, m_data->window.getSize().y / 1.25f, 150.f, 50.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Return", 40, textIdleColor, textHoverColor, textActiveColor, containerIdleColor, containerHoverColor, containerActiveColor);
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

	void SettingsState::Update()
	{
		m_UpdateUIManager();
	}

	void SettingsState::m_UpdateView()
	{
		
	}

	void SettingsState::m_UpdateUIManager()
	{
		m_uiManager.Update();

		if (m_uiManager.Buttons["RETURN"]->IsPressed())
		{
			m_data->stateManager.RemoveState();
			AssetManager::GetInstance()->LoadSoundBuffer("UI_BUTTON_BACK_PRESSED", AUDIO_UI_BACK_FILEPATH);
			AssetManager::GetInstance()->PlaySound("UI_BUTTON_BACK_PRESSED");
		}
	}

	void SettingsState::Draw()
	{
		m_data->window.draw(m_background);
	}

	void SettingsState::DrawUI()
	{
		m_DrawUIManager();
	}

	void SettingsState::End()
	{
	}

	void SettingsState::m_DrawUIManager()
	{
		m_uiManager.Draw();
	}
}