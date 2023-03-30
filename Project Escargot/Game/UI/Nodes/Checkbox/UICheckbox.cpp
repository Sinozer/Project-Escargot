#include "stdafx.h"

namespace Snail
{
	// #### Constructor | Destructor #### //
	UICheckbox::UICheckbox(float x, float y, float width, float height,
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
		m_falseStateText = "No";
		m_trueStateText = "Yes";
	}

	UICheckbox::~UICheckbox()
	{
		delete m_font;
	}
	// #### Constructor | Destructor #### //

	// #### Modifiers #### //
	void UICheckbox::SwitchState()
	{
		if (m_checked)
			m_text.setString(m_falseStateText);
		else
			m_text.setString(m_trueStateText);

		m_checked = !m_checked;
	}
	// #### Modifiers #### //

	// #### Accessors #### //
	const bool UICheckbox::IsChecked() const
	{
		return m_checked;
	}
	// #### Accessors #### //

	// #### Functions #### //

	// #### Functions #### //
}