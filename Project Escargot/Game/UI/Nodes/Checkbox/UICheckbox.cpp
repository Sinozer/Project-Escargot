#include "stdafx.h"
#include "UICheckbox.h"

// #### Constructor | Destructor #### //
Snail::UI::UICheckbox::UICheckbox(float x, float y, float width, float height,
	sf::Font* font, unsigned characterSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color containerIdleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor,
	short unsigned id)
	: UIButton(x, y, width, height, font, "No", characterSize,
		textIdleColor, textHoverColor, textActiveColor,
		containerIdleColor, hoverColor, activeColor,
		outlineIdleColor, outlineHoverColor, outlineActiveColor, id)
{
	this->m_falseStateText = "No";
	this->m_trueStateText = "Yes";
}

Snail::UI::UICheckbox::~UICheckbox()
{
	delete this->m_font;
}
// #### Constructor | Destructor #### //

// #### Modifiers #### //
void Snail::UI::UICheckbox::SwitchState()
{
	if (this->m_checked)
		this->m_text.setString(this->m_falseStateText);
	else
		this->m_text.setString(this->m_trueStateText);

	this->m_checked = !this->m_checked;
}
// #### Modifiers #### //

// #### Accessors #### //
const bool Snail::UI::UICheckbox::IsChecked() const
{
	return this->m_checked;
}
// #### Accessors #### //

// #### Functions #### //

// #### Functions #### //