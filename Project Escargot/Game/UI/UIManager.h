#pragma once

#include "Nodes/Text/UIText.h"
#include "Nodes/Button/UIButton.h"
#include "Nodes/Checkbox/UICheckbox.h"

namespace Snail
{
	class UIManager
	{
	private:
		void m_UpdateButtons();
		void m_UpdateCheckboxs();

		void m_DrawTexts();
		void m_DrawButtons();
		void m_DrawCheckboxs();
	public:
		std::map<std::string, UIText*> Texts;
		std::map<std::string, UIButton*> Buttons;
		std::map<std::string, UICheckbox*> Checkboxs;
	public:
		// #### Constructor | Destructor #### //
		UIManager() {}
		~UIManager();
		// #### Constructor | Destructor #### //

		UIText* AddText(std::string name, float x, float y, float width, float height,
			sf::Font& font, std::string text, unsigned characterSize,
			sf::Color textColor = sf::Color::White,
			sf::Color containerColor = sf::Color::Transparent,
			sf::Color outlineColor = sf::Color::Transparent);

		UIButton* AddButton(std::string name, float x, float y, float width, float height,
			sf::Font& font, std::string text, unsigned characterSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color containerIdleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent,
			sf::Color outlineHoverColor = sf::Color::Transparent,
			sf::Color outlineActiveColor = sf::Color::Transparent,
			short unsigned id = 0);

		UICheckbox* AddCheckbox(std::string name, float x, float y, float width, float height,
			sf::Font& font, unsigned characterSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color containerIdleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent,
			sf::Color outlineHoverColor = sf::Color::Transparent,
			sf::Color outlineActiveColor = sf::Color::Transparent,
			short unsigned id = 0);

		void Update();
		void Draw();
	};
}