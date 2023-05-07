#include "stdafx.h"
#include "UIManager.h"
namespace Snail
{
	// #### Constructor | Destructor #### //
	UIManager::~UIManager()
	{
		for (auto& i : Texts)
			delete i.second;

		for (auto& i : Buttons)
			delete i.second;

		for (auto& i : Checkboxs)
			delete i.second;
	}
	// #### Constructor | Destructor #### //

	UIText* UIManager::AddText(std::string name, float x, float y, float width, float height, sf::Font& font, std::string text, unsigned characterSize, sf::Color textColor, sf::Color containerColor, sf::Color outlineColor)
	{
		Texts[name] = new UIText(x, y, width, height, &font, text, characterSize, textColor, containerColor, outlineColor);
		return Texts[name];
	}

	UIButton* UIManager::AddButton(std::string name, float x, float y, float width, float height, sf::Font& font, std::string text, unsigned characterSize, sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor, sf::Color containerIdleColor, sf::Color containerHoverColor, sf::Color containerActiveColor, sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor, short unsigned id)
	{
		Buttons[name] = new UIButton(x, y, width, height, &font, text, characterSize, textIdleColor, textHoverColor, textActiveColor, containerIdleColor, containerHoverColor, containerActiveColor, outlineIdleColor, outlineHoverColor, outlineActiveColor);
		return Buttons[name];
	}

	UICheckbox* UIManager::AddCheckbox(std::string name, float x, float y, float width, float height, sf::Font& font, unsigned characterSize, sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor, sf::Color containerIdleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor, short unsigned id)
	{
		Checkboxs[name] = new UICheckbox(x, y, width, height, &font, characterSize, textIdleColor, textHoverColor, textActiveColor, containerIdleColor, hoverColor, activeColor, outlineIdleColor, outlineHoverColor, outlineActiveColor);
		return Checkboxs[name];
	}

	void UIManager::Update()
	{
		m_UpdateButtons();
		m_UpdateCheckboxs();
	}

	void UIManager::m_UpdateButtons()
	{
		for (auto& i : Buttons)
			i.second->Update();
	}

	void UIManager::m_UpdateCheckboxs()
	{
		for (auto& i : Checkboxs)
			i.second->Update();
	}

	void UIManager::Draw()
	{
		m_DrawTexts();
		m_DrawButtons();
		m_DrawCheckboxs();
	}

	void UIManager::m_DrawTexts()
	{
		for (auto& i : Texts)
			i.second->Draw(Game::m_data->window);
	}

	void UIManager::m_DrawButtons()
	{
		for (auto& i : Buttons)
			i.second->Draw(Game::m_data->window);
	}

	void UIManager::m_DrawCheckboxs()
	{
		for (auto& i : Checkboxs)
			i.second->Draw(Game::m_data->window);
	}
}