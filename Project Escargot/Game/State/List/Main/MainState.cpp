#include "stdafx.h"
#include "MainState.h"
#include "Game/State/List/Game/GameState.h"
#include "Game/State/List/Settings/SettingsState.h"

namespace Snail
{
	MainState::MainState(GameDataRef data) : m_data(data)
	{
		m_isLoaded = false;
	}

	void MainState::Init()
	{
		m_InitBackground();
		m_InitView();
		m_InitUIManager();

		AssetManager::GetInstance()->LoadMusic("STATE_MAIN_MUSIC", AUDIO_MUSIC_MENU_FILEPATH);
		AssetManager::GetInstance()->PlayMusic("STATE_MAIN_MUSIC");
	}

	void MainState::m_InitBackground()
	{
		AssetManager::GetInstance()->LoadTexture("STATE_MAIN_BACKGROUND", BACKGROUND_PINKDESERT_FILEPATH);
		m_background.setTexture(AssetManager::GetInstance()->GetTexture("STATE_MAIN_BACKGROUND"));
		m_background.setScale((float)m_data->window.getSize().x / (float)m_background.getTexture()->getSize().x, (float)m_data->window.getSize().y / (float)m_background.getTexture()->getSize().y);

		m_background.setColor(sf::Color(m_background.getColor().r, m_background.getColor().g, m_background.getColor().b, 255U));
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
		m_uiManager.AddText("TITLE", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 6.f, 0.f, 0.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Project Escargot", 92, sf::Color::White, sf::Color::Transparent);
		m_uiManager.Texts["TITLE"]->SetOutlineColor(sf::Color::Black);
		m_uiManager.Texts["TITLE"]->SetOutlineThickness(2.f);
	}

	void MainState::m_InitUIButtons()
	{
		sf::Color textIdleColor(192U, 192U, 192U);
		sf::Color textHoverColor(255U, 255U, 255U, 255U);
		sf::Color textActiveColor(255U, 255U, 255U, 255U);

		sf::Color containerIdleColor(42U, 42U, 42U, 128U);
		sf::Color containerHoverColor(42U, 42U, 42U, 192U);
		sf::Color containerActiveColor(42U, 42U, 42U, 255U);

		m_uiManager.AddButton("PLAY", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 2.2f, 200.f, 75.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Play", 60, textIdleColor, textHoverColor, textActiveColor, containerIdleColor, containerHoverColor, containerActiveColor);

		m_uiManager.AddButton("SETTINGS", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 1.70f, 200.f, 75.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Settings", 60, textIdleColor, textHoverColor, textActiveColor, containerIdleColor, containerHoverColor, containerActiveColor);
		
		m_uiManager.AddButton("QUIT", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 1.25f, 150.f, 50.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Quit", 40, textIdleColor, textHoverColor, textActiveColor, containerIdleColor, containerHoverColor, containerActiveColor);
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
		m_uiManager.Update();

		sf::Vector2f pos(m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 12.f);

		pos.y = static_cast<float>((m_data->window.getSize().y / 6.f) + Math::GetSineWaveValue(.15f, 20.f));

		m_uiManager.Texts["TITLE"]->SetPosition(pos);

		if (m_uiManager.Buttons["PLAY"]->IsPressed())
		{
			m_data->stateManager.AddState(StateRef(new GameState(m_data)));
			AssetManager::GetInstance()->LoadSoundBuffer("UI_BUTTON_PRESSED_ECHO", AUDIO_UI_CONFIRM_ECHO_FILEPATH);
			AssetManager::GetInstance()->PlaySound("UI_BUTTON_PRESSED_ECHO");
		}

		if (m_uiManager.Buttons["SETTINGS"]->IsPressed())
		{
			m_data->stateManager.AddState(StateRef(new SettingsState(m_data)));
			AssetManager::GetInstance()->LoadSoundBuffer("UI_BUTTON_PRESSED", AUDIO_UI_CONFIRM_FILEPATH);
			AssetManager::GetInstance()->PlaySound("UI_BUTTON_PRESSED");
		}

		if (m_uiManager.Buttons["QUIT"]->IsPressed())
		{
			m_data->window.close();
			AssetManager::GetInstance()->LoadSoundBuffer("UI_BUTTON_QUIT_PRESSED", AUDIO_UI_ERROR_FILEPATH);
			AssetManager::GetInstance()->PlaySound("UI_BUTTON_QUIT_PRESSED");
		}
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
		m_uiManager.Draw();
	}
}