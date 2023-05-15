#include "stdafx.h"
#include "GameEndState.h"
#include "Game/Entity/LivingEntity/Player/Player.h"
#include "Game/Spawner/SpawnerManager.h"

namespace Snail
{
	int GameEndState::m_id = -1;

	GameEndState::GameEndState(GameDataRef data) : m_data(data)
	{
		if (m_id == -1)
			m_id = ID;
		else
			ID = m_id;
		
		Name = "GameEndState";
		m_isLoaded = false;
	}

	void GameEndState::Init()
	{
		m_InitBackground();
		m_InitView();
		m_InitUIManager();
	}

	void GameEndState::m_InitBackground()
	{
		AssetManager::GetInstance()->LoadTexture("STATE_SETTINGS_BACKGROUND", BACKGROUND_DAWNMOUNTAIN_FILEPATH);
		m_background.setTexture(AssetManager::GetInstance()->GetTexture("STATE_SETTINGS_BACKGROUND"));
		m_background.setScale((float)m_data->window.getSize().x / (float)m_background.getTexture()->getSize().x, (float)m_data->window.getSize().y / (float)m_background.getTexture()->getSize().y);
	}

	void GameEndState::m_InitView()
	{
		m_view.setSize(sf::Vector2f((float)m_data->window.getSize().x, (float)m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f((float)m_data->window.getSize().x / 2.f, (float)m_data->window.getSize().y / 2.f));
		m_data->window.setView(m_view);
	}

	void GameEndState::m_InitUIManager()
	{
		m_InitUITexts();
		m_InitUIButtons();
	}

	void GameEndState::m_InitUITexts()
	{
		UIText* textTitle = m_uiManager.AddText("TITLE", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 12.f, 0.f, 0.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "WELL PLAYED !", 92, sf::Color::White, sf::Color::Transparent);
		textTitle->SetOutlineColor(sf::Color::Black);
		textTitle->SetOutlineThickness(2.f);

		sf::Vector2f pos = textTitle->GetPosition(BOT_MID);

		UIText* textTitleJoke = m_uiManager.AddText("TITLE_JOKE", pos.x, pos.y * 1.05f, 0.f, 0.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Loser..", 16, sf::Color::White, sf::Color::Transparent);
		textTitleJoke->SetOutlineColor(sf::Color::Black);
		textTitleJoke->SetOutlineThickness(2.f);

		UIText* textWave = m_uiManager.AddText("WAVE", m_data->window.getSize().x / 2.f, m_data->window.getSize().y / 2.f, 0.f, 0.f, AssetManager::GetInstance()->GetFont("ROBOTO_CONDENSED_ITALIC"), SpawnerManager::GetInstance()->GetWaveString() + " wave", 60, sf::Color::White, sf::Color::Transparent);
		textWave->SetOutlineColor(sf::Color::Black);
		textWave->SetOutlineThickness(2.f);

		pos = textWave->GetPosition(BOT_MID);

		UIText* textScore = m_uiManager.AddText("SCORE", pos.x, pos.y * 1.05f, 0.f, 0.f, AssetManager::GetInstance()->GetFont("ROBOTO_CONDENSED_ITALIC"), Player::GetInstance()->GetScoreString() + " pts", 60, sf::Color::White, sf::Color::Transparent);
		textScore->SetOrigin(TOP_MID);
		textScore->SetOutlineColor(sf::Color::Black);
		textScore->SetOutlineThickness(2.f);

		pos = textScore->GetPosition(BOT_MID);
		
		UIText* textKills = m_uiManager.AddText("KILL", pos.x, pos.y * 1.05f, 0.f, 0.f, AssetManager::GetInstance()->GetFont("ROBOTO_CONDENSED_ITALIC"), Player::GetInstance()->GetKillsString() + " kills", 60, sf::Color::White, sf::Color::Transparent);
		textKills->SetOrigin(TOP_MID);
		textKills->SetOutlineColor(sf::Color::Black);
		textKills->SetOutlineThickness(2.f);
	}

	void GameEndState::m_InitUIButtons()
	{
		sf::Color textIdleColor(192U, 192U, 192U);
		sf::Color textHoverColor(255U, 255U, 255U, 255U);
		sf::Color textActiveColor(255U, 255U, 255U, 255U);

		sf::Color containerIdleColor(42U, 42U, 42U, 128U);
		sf::Color containerHoverColor(42U, 42U, 42U, 192U);
		sf::Color containerActiveColor(42U, 42U, 42U, 255U);
		
		UIButton* buttonMenu = m_uiManager.AddButton("MENU", m_data->window.getSize().x / 2.f / 1.5f, m_data->window.getSize().y / 1.25f, 150.f, 50.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Menu", 40, textIdleColor, textHoverColor, textActiveColor, containerIdleColor, containerHoverColor, containerActiveColor);
		buttonMenu->SetOrigin(MID_MID);
		
		UIButton* buttonQuit = m_uiManager.AddButton("QUIT", m_data->window.getSize().x / 2.f * 1.5f, m_data->window.getSize().y / 1.25f, 150.f, 50.f, AssetManager::GetInstance()->LoadFont("ROBOTO_CONDENSED_ITALIC", "Resources/Fonts/Roboto/Roboto-CondensedItalic.ttf"), "Quit", 40, textIdleColor, textHoverColor, textActiveColor, containerIdleColor, containerHoverColor, containerActiveColor);
		buttonQuit->SetOrigin(MID_RIGHT);
	}

	void GameEndState::HandleInput()
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

	void GameEndState::Update()
	{
		m_UpdateUIManager();
	}

	void GameEndState::m_UpdateView()
	{

	}

	void GameEndState::m_UpdateUIManager()
	{
		m_uiManager.Update();

		if (m_uiManager.Buttons["MENU"]->IsPressed())
			m_data->stateManager.RemoveState();
		
		if (m_uiManager.Buttons["QUIT"]->IsPressed())
			m_data->window.close();
	}

	void GameEndState::Draw()
	{
		m_data->window.draw(m_background);
	}

	void GameEndState::DrawUI()
	{
		m_DrawUIManager();
	}

	void GameEndState::End()
	{
		if (m_data->stateManager.GetPreviousState()->Name == "GameState")
			m_data->stateManager.RemoveState();
	}

	void GameEndState::m_DrawUIManager()
	{
		m_uiManager.Draw();
	}
}