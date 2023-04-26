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

	void UIManager::AddText(std::string name, float x, float y, float width, float height, sf::Font& font, std::string text, unsigned characterSize, sf::Color textColor, sf::Color containerColor, sf::Color outlineColor)
	{
		Texts[name] = new UIText(x, y, width, height, &font, text, characterSize, textColor, containerColor, outlineColor);
	}

	void UIManager::AddButton(std::string name, float x, float y, float width, float height, sf::Font& font, std::string text, unsigned characterSize, sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor, sf::Color containerIdleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor, short unsigned id)
	{
		Buttons[name] = new UIButton(x, y, width, height, &font, text, characterSize, textIdleColor, textHoverColor, textActiveColor, containerIdleColor, hoverColor, activeColor, outlineIdleColor, outlineHoverColor, outlineActiveColor);
	}

	void UIManager::AddCheckbox(std::string name, float x, float y, float width, float height, sf::Font& font, unsigned characterSize, sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor, sf::Color containerIdleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor, short unsigned id)
	{
		Checkboxs[name] = new UICheckbox(x, y, width, height, &font, characterSize, textIdleColor, textHoverColor, textActiveColor, containerIdleColor, hoverColor, activeColor, outlineIdleColor, outlineHoverColor, outlineActiveColor);
	}

	void UIManager::Update(sf::Vector2i mousePosition, float dt)
	{
		m_UpdateButtons(mousePosition, dt);
		m_UpdateCheckboxs(mousePosition, dt);
	}

	void UIManager::m_UpdateButtons(sf::Vector2i mousePosition, float dt)
	{
		for (auto& i : Buttons)
			i.second->Update(mousePosition, dt);
	}

	void UIManager::m_UpdateCheckboxs(sf::Vector2i mousePosition, float dt)
	{
		for (auto& i : Checkboxs)
			i.second->Update(mousePosition, dt);
	}

	void UIManager::Draw(sf::RenderTarget& target)
	{
		m_DrawTexts(target);
		m_DrawButtons(target);
		m_DrawCheckboxs(target);
	}

	void UIManager::m_DrawTexts(sf::RenderTarget& target)
	{
		for (auto& i : Texts)
			i.second->Draw(target);
	}

	void UIManager::m_DrawButtons(sf::RenderTarget& target)
	{
		for (auto& i : Buttons)
			i.second->Draw(target);
	}

	void UIManager::m_DrawCheckboxs(sf::RenderTarget& target)
	{
		for (auto& i : Checkboxs)
			i.second->Draw(target);
	}
}